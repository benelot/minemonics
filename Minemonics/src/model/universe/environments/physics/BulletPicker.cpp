//# corresponding headers
#include <model/universe/environments/physics/BulletPicker.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyLinkCollider.h>
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

BulletPicker::BulletPicker() :
	mHitPos(), mOldPickingDist(), mPickedBody(NULL), mPicking(false), mPickingMultiBodyPoint2Point(
	NULL), mPickedConstraint(NULL), mPrevCanSleep(false), mMultibodyworld(
	NULL), mWorld(NULL) {
}

BulletPicker::~BulletPicker() {
	mPickedBody = NULL;
	if (mPickingMultiBodyPoint2Point) {
		delete mPickingMultiBodyPoint2Point;
		mPickingMultiBodyPoint2Point = NULL;
	}
	mPickedConstraint = NULL;
	mMultibodyworld = NULL;
	mWorld = NULL;
}

btVector3 BulletPicker::pickBody(btDynamicsWorld* world,
	const btVector3& rayFromWorld, const btVector3& rayToWorld) {
	mWorld = world;
	// the ray caster currently only finds the intersection
	// when hitting the forward face of a triangle therefore,
	//the ray has to come from the outside of the shape
#ifndef EXCLUDE_FROM_TEST
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(rayFromWorld,
		rayToWorld, btVector3(1, 1, 0));
#endif

	btVector3 hitPosition = rayFromWorld;

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayFromWorld,
		rayToWorld);

	//kF_UseGjkConvexRaytest flag is now enabled by default, use the faster but more approximate algorithm
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	rayCallback.m_flags &= ~btTriangleRaycastCallback::kF_FilterBackfaces;

	rayCallback.m_collisionFilterGroup =
		PhysicsConfiguration::COL_CREATURE_TESTRAY;
	rayCallback.m_collisionFilterMask =
		PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH;

	world->rayTest(rayFromWorld, rayToWorld, rayCallback);

	if (rayCallback.hasHit()) {
		mPicking = true;
		btVector3 p = rayFromWorld.lerp(rayToWorld,
			rayCallback.m_closestHitFraction);
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(p, 1,
			btVector3(1, 0, 0));
		SimulationManager::getSingleton()->getDebugDrawer().drawLine(p,
			p + rayCallback.m_hitNormalWorld, btVector3(1, 0, 0));
#endif
		hitPosition = p;

		btVector3 pickPos = rayCallback.m_hitPointWorld;
		btRigidBody* body = (btRigidBody*) btRigidBody::upcast(
			rayCallback.m_collisionObject);
		if (body) {
			//other exclusions?
			if (!(body->isStaticObject() || body->isKinematicObject())) {
				mPickedBody = body;
				mPickedBody->setActivationState(DISABLE_DEACTIVATION);
				//printf("pickPos=%f,%f,%f\n",pickPos.getX(),pickPos.getY(),pickPos.getZ());
				btVector3 localPivot =
					body->getCenterOfMassTransform().inverse() * pickPos;
				btPoint2PointConstraint* p2p = new btPoint2PointConstraint(
					*body, localPivot);
				mWorld->addConstraint(p2p, true);

				if (mPickedConstraint) {
					world->removeConstraint(mPickedConstraint);
					delete mPickedConstraint;
					mPickedConstraint = NULL;
				}

				mPickedConstraint = p2p;
				p2p->m_setting.m_impulseClamp = btScalar(
					PhysicsConfiguration::BULLET_PICKER_FORCE);
				p2p->m_setting.m_tau = 1.0f;
			}
		} else {
			btMultiBodyLinkCollider* multiCol =
				(btMultiBodyLinkCollider*) btMultiBodyLinkCollider::upcast(
					rayCallback.m_collisionObject);
			if (multiCol && multiCol->m_multiBody) {
				mPrevCanSleep = multiCol->m_multiBody->getCanSleep();
				multiCol->m_multiBody->setCanSleep(false);

				btVector3 pivotInA = multiCol->m_multiBody->worldPosToLocal(
					multiCol->m_link, pickPos);

				btMultiBodyPoint2Point* p2p = new btMultiBodyPoint2Point(
					multiCol->m_multiBody, multiCol->m_link, 0, pivotInA,
					pickPos);
				//if you add too much energy to the system, causing high angular velocities, simulation 'explodes'
				//see also http://www.bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=4&t=949
				//so we try to avoid it by clamping the maximum impulse (force) that the mouse pick can apply
				//it is not satisfying, hopefully we find a better solution (higher order integrator, using joint friction using a zero-velocity target motor with limited force etc?)
				p2p->setMaxAppliedImpulse(
					btScalar(PhysicsConfiguration::BULLET_PICKER_FORCE));

				btMultiBodyDynamicsWorld* multibodyworld =
					(btMultiBodyDynamicsWorld*) mWorld;
				multibodyworld->addMultiBodyConstraint(p2p);

				if (mPickingMultiBodyPoint2Point) {
					multibodyworld->removeMultiBodyConstraint(
						mPickingMultiBodyPoint2Point);
					delete mPickingMultiBodyPoint2Point;
					mPickingMultiBodyPoint2Point = NULL;
				}

				mPickingMultiBodyPoint2Point = p2p;
				mMultibodyworld = multibodyworld;
			}
		}

		mOldPickingPos = rayToWorld;
		mHitPos = pickPos;
		mOldPickingDist = (pickPos - rayFromWorld).length();
	} else {
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
			rayFromWorld, 1, btVector3(1, 0, 0));
#endif
		//no hit
	}
	return hitPosition;
}

bool BulletPicker::movePickedBody(const btVector3& rayFromWorld,
	const btVector3& rayToWorld) {
	//keep it at the same picking distance

	btVector3 dir = rayToWorld - rayFromWorld;
	dir.normalize();
	dir *= mOldPickingDist;

	btVector3 newPivotB = rayFromWorld + dir;

#ifndef EXCLUDE_FROM_TEST
	SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
		newPivotB, 1.0, btVector3(0, 1, 0));
#endif

	if (mPickedBody && mPickedConstraint) {

		btPoint2PointConstraint* pickCon =
			static_cast<btPoint2PointConstraint*>(mPickedConstraint);

		if (pickCon) {
			pickCon->setPivotB(newPivotB);
		}
	}

	if (mPickingMultiBodyPoint2Point) {
		mPickingMultiBodyPoint2Point->setPivotInB(newPivotB);
	}

	return false;
}

void BulletPicker::setPicking(bool picking) {
	mPicking = picking;
	if (!mPicking) {
		if (mPickedConstraint) {
			mWorld->removeConstraint(mPickedConstraint);
			delete mPickedConstraint;
			mPickedConstraint = NULL;
			mWorld = NULL;
		}
		if (mPickingMultiBodyPoint2Point) {
			mMultibodyworld->removeMultiBodyConstraint(
				mPickingMultiBodyPoint2Point);
			delete mPickingMultiBodyPoint2Point;
			mPickingMultiBodyPoint2Point = NULL;
			mMultibodyworld = NULL;
		}
	}
}
