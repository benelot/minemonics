//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbBt.hpp>

//# forward declarations
//# system headers
#include <cstdlib>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btScalar.h>

#include <OgreQuaternion.h>
#include <OgreVector3.h>

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
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

SRBLimbBt::SRBLimbBt() :
	LimbPhysics(), mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(
		NULL), mInertia(0, 0, 0),mLimbModel(NULL) {
}

SRBLimbBt::SRBLimbBt(btDynamicsWorld* const world,  LimbModel* const limbModel,
	const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding):
	mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(world), mInertia(
		0, 0, 0) {

	mDimensions = dimensions;
	mMass = mass;
	mType = type;
	mFriction = friction;
	mRestitution = restitution;
	mIntraBodyColliding = isIntraBodyColliding;

	mPosition = position;
	mInitialRelativeXPosition = initialRelativePosition.x;
	mInitialRelativeYPosition = initialRelativePosition.y;
	mInitialRelativeZPosition = initialRelativePosition.z;

	mInitialWOrientation = initialOrientation.w;
	mInitialXOrientation = initialOrientation.x;
	mInitialYOrientation = initialOrientation.y;
	mInitialZOrientation = initialOrientation.z;
	mColor = color;
	mIntraBodyColliding = isIntraBodyColliding;
	mLimbModel = limbModel;
}

SRBLimbBt::SRBLimbBt(const SRBLimbBt& limbBt) {
	btTransform startTransform = limbBt.mBody->getWorldTransform();
	SRBLimbBt(limbBt.mWorld, (LimbModel*)limbBt.mCollisionShape->getUserPointer(),
		limbBt.mType, OgreBulletUtils::convert(startTransform.getOrigin()),
		OgreBulletUtils::convert(startTransform.getRotation()),
		Ogre::Vector3(limbBt.mInitialRelativeXPosition,
			limbBt.mInitialRelativeYPosition,
			limbBt.mInitialRelativeZPosition),
		Ogre::Quaternion(limbBt.mInitialWOrientation,
			limbBt.mInitialXOrientation, limbBt.mInitialYOrientation,
			limbBt.mInitialZOrientation), limbBt.mDimensions,
			limbBt.mMass, limbBt.mRestitution, limbBt.mFriction,
			limbBt.mColor, limbBt.mIntraBodyColliding);

	mInWorld = limbBt.mInWorld;
	mInertia = limbBt.mInertia;
	mWorld = limbBt.mWorld;
	mBody = limbBt.mBody;
	mCollisionShape = limbBt.mCollisionShape;
	mLimbModel = limbBt.mLimbModel;
	mMotionState = limbBt.mMotionState;
}

SRBLimbBt::~SRBLimbBt() {
	delete mBody;
	mBody = NULL;

	delete mCollisionShape;
	mCollisionShape = NULL;

	delete mMotionState;
	mMotionState = NULL;

	mWorld = NULL;
}

void SRBLimbBt::initialize() {
	if (!mCollisionShape) {
		btVector3 halfExtents(mDimensions.x * 0.5f, mDimensions.y * 0.5f,
			mDimensions.z * 0.5f);
		switch (mType) {
		case LimbPhysics::BLOCK:
			mCollisionShape = new btBoxShape(halfExtents);
			break;
		case LimbPhysics::CAPSULE:
			mCollisionShape = new btCapsuleShape(btScalar(mDimensions.x * 0.5f),
				btScalar(mDimensions.y));
			break;
		case LimbPhysics::UNKNOWN:
			std::cout << "##########################################\n"
				<< " LimbBt received 'Unknown' as a limb type.\n"
				<< "##########################################\n";
			exit(-1);
		}

		mCollisionShape->calculateLocalInertia(btScalar(mMass), mInertia);

		// position the limb in the world
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(
			OgreBulletUtils::convert(mPosition));
		startTransform.setRotation(
			btQuaternion(mInitialXOrientation, mInitialYOrientation,
				mInitialZOrientation, mInitialWOrientation));

		mMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(btScalar(mMass),
			mMotionState, mCollisionShape, mInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setDeactivationTime(
			PhysicsConfiguration::BULLET_DEACTIVATION_TIME);
		mBody->setSleepingThresholds(
			PhysicsConfiguration::BULLET_LINEAR_SLEEPING_TIME,
			PhysicsConfiguration::BULLET_ANGULAR_SLEEPING_TIME);
		mBody->setActivationState(DISABLE_DEACTIVATION);

		//to get custom collision callbacks in collisionhandler
		mBody->setCollisionFlags(
			mBody->getCollisionFlags()
				| btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		//Set the friction and restitution/elasticity of the rigid body
		mBody->setFriction(btScalar(mFriction));
		mBody->setRollingFriction(btScalar(mFriction));
		mBody->setRestitution(btScalar(mRestitution));
		mBody->setAnisotropicFriction(
			mCollisionShape->getAnisotropicRollingFrictionDirection(),
			btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);

//		calm();

		//Set user pointer for proper return of creature/limb information etc..
		mBody->setUserPointer(mLimbModel);
		//add the creature model pointer to the collision shape to get it back if we raycast for this object.
		mCollisionShape->setUserPointer(mLimbModel);
	}
}

btTransform SRBLimbBt::getIntersection(btVector3 origin, btVector3 direction) {
	return getPreciseIntersection(origin, direction);
}

btTransform SRBLimbBt::getPreciseIntersection(const btVector3 origin,
	const btVector3 direction) {
	// the ray caster currently only finds the intersection
	// when hitting the forward face of a triangle therefore,
	//the ray has to come from the outside of the shape
	btVector3 rayStart = origin + direction.normalized() * 100.0f;
	btVector3 rayEnd = origin;

#ifndef EXCLUDE_FROM_TEST
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(rayStart,
		rayEnd, btVector3(1, 1, 0));
#endif

	btVector3 hitPosition = origin;
	btVector3 hitNormal = btVector3(1, 0, 0);

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayStart, rayEnd);

	//kF_UseGjkConvexRaytest flag is now enabled by default, use the faster but more approximate algorithm
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	rayCallback.m_flags &= ~btTriangleRaycastCallback::kF_FilterBackfaces;
	rayCallback.m_collisionFilterGroup =
		PhysicsConfiguration::COL_CREATURE_TESTRAY;
	rayCallback.m_collisionFilterMask =
		PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH;

	mWorld->rayTest(rayStart, rayEnd, rayCallback);

	if (rayCallback.hasHit()) {
		hitPosition = rayStart.lerp(rayEnd, rayCallback.m_closestHitFraction);
		hitNormal = rayCallback.m_hitNormalWorld;
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
			hitPosition, 1, btVector3(1, 0, 0));
		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
			hitPosition, hitPosition + rayCallback.m_hitNormalWorld,
			btVector3(1, 0, 0));
#endif
	} else {
		//no hit
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(rayStart,
			1, btVector3(1, 0, 0));
#endif
	}

	btTransform hitTransform;
	hitTransform.setIdentity();
	hitTransform.setOrigin(hitPosition);
	Ogre::Euler euler(0, 0, 0);
	euler.direction(OgreBulletUtils::convert(hitNormal));
	hitTransform.setRotation(OgreBulletUtils::convert(euler.toQuaternion()));
	return hitTransform;
}

btVector3 SRBLimbBt::getLocalFakeIntersection(const btVector3 origin,
	const btVector3 direction) {
	return mDimensions.length() / 2.0f * direction.normalized();
}

btTransform SRBLimbBt::getLocalIntersection(const btVector3 origin,
	const btVector3 direction) {
	btTransform intersection = getLocalPreciseIntersection(origin, direction);
	if (intersection.getOrigin().isZero()) {
		intersection.setOrigin(getLocalFakeIntersection(origin, direction));
	}
	return intersection;
}

void SRBLimbBt::reset(const Ogre::Vector3 position) {
	btTransform initialTransform;

	btVector3 initialRelativePosition;
	initialRelativePosition.setValue(getInitialRelativeXPosition(),
		getInitialRelativeYPosition(), getInitialRelativeZPosition());

	btQuaternion initialOrientation;
	initialOrientation.setValue(getInitialXOrientation(),
		getInitialYOrientation(), getInitialZOrientation(),
		getInitialWOrientation());

	initialTransform.setOrigin(
		OgreBulletUtils::convert(position) + initialRelativePosition);
	initialTransform.setRotation(initialOrientation);

	mBody->setWorldTransform(initialTransform);
	mMotionState->setWorldTransform(initialTransform);
}

void SRBLimbBt::reposition(const Ogre::Vector3 position) {
	btTransform initialTransform;

	btVector3 initialRelativePosition;
	initialRelativePosition.setValue(getInitialRelativeXPosition(),
		getInitialRelativeYPosition(), getInitialRelativeZPosition());

	btQuaternion initialOrientation;
	initialOrientation.setValue(getInitialXOrientation(),
		getInitialYOrientation(), getInitialZOrientation(),
		getInitialWOrientation());

	initialTransform.setOrigin(
		OgreBulletUtils::convert(position) + initialRelativePosition);
	initialTransform.setRotation(initialOrientation);

	mBody->setWorldTransform(initialTransform);
	mMotionState->setWorldTransform(initialTransform);
}

btTransform SRBLimbBt::getLocalPreciseIntersection(const btVector3 origin,
	const btVector3 direction) {
	btTransform transform = getPreciseIntersection(origin, direction);
	transform.setOrigin(transform.getOrigin() - origin);
	return transform;
}

void SRBLimbBt::addToWorld() {
	if (!isInWorld()) {
		if (!mIntraBodyColliding) {
			mWorld->addRigidBody(mBody, PhysicsConfiguration::COL_CREATURE,
				PhysicsConfiguration::CREATURE_COLLIDES_WITH);
		} else {
			mWorld->addRigidBody(mBody);
		}
		LimbPhysics::addToWorld();
	}
}

void SRBLimbBt::removeFromWorld() {
	if (isInWorld()) {
		mWorld->removeRigidBody(mBody);
		LimbPhysics::removeFromWorld();
	}
}

SRBLimbBt* SRBLimbBt::clone() {
	return new SRBLimbBt(*this);
}

void SRBLimbBt::calm() {
	mBody->clearForces();
	btVector3 zeroVector(0, 0, 0);
	mBody->setLinearVelocity(zeroVector);
	mBody->setAngularVelocity(zeroVector);
}

bool SRBLimbBt::equals(const SRBLimbBt& SRBLimbBt) const {
	if (!LimbPhysics::equals(SRBLimbBt)) {
		return false;
	}
	return true;
}

const Ogre::Vector3 SRBLimbBt::getVelocities() const {
	return OgreBulletUtils::convert(mBody->getLinearVelocity());
}
