//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
//# forward declarations
//# system headers
#include <stddef.h>
#include <iostream>

//## controller headers
//## model headers
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers

LimbBt::LimbBt() :
		LimbPhysics(), mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(
		NULL), mType(LimbModel::UNKNOWN) {
}

LimbBt::LimbBt(const LimbBt& limbBt) {
	btTransform startTransform = limbBt.mBody->getWorldTransform();
	initialize(limbBt.mWorld, limbBt.mCollisionShape->getUserPointer(),
			limbBt.mType, startTransform.getOrigin(),
			startTransform.getRotation(),
			btVector3(limbBt.mInitialRelativeXPosition,
					limbBt.mInitialRelativeYPosition,
					limbBt.mInitialRelativeZPosition),
			btQuaternion(limbBt.mInitialXOrientation,
					limbBt.mInitialYOrientation, limbBt.mInitialZOrientation,
					limbBt.mInitialWOrientation), limbBt.mDimensions,
			limbBt.mMass, limbBt.mRestitution, limbBt.mFriction);

	mInWorld = limbBt.mInWorld;
}

LimbBt::~LimbBt() {
	delete mBody;
}

void LimbBt::initialize(btDynamicsWorld* const world, void* const limbModel,
		const LimbModel::PrimitiveType type, const btVector3 position,
		const btQuaternion orientation, const btVector3 initialRelativePosition,
		const btQuaternion initialOrientation, const btVector3 dimensions,
		const btScalar mass, const btScalar restitution,
		const btScalar friction) {
	mWorld = world;
	mDimensions = dimensions;
	mMass = mass;
	mType = type;
	btVector3 HalfExtents(dimensions.x() * 0.5f, dimensions.y() * 0.5f,
			dimensions.z() * 0.5f);
	switch (type) {
	case LimbModel::BLOCK:
		mCollisionShape = new btBoxShape(HalfExtents);
		break;
	case LimbModel::CAPSULE:
		mCollisionShape = new btCapsuleShape(btScalar(dimensions.x() * 0.5f),
				btScalar(dimensions.y()));
		break;
	case LimbModel::UNKNOWN:
		std::cout << "##########################################\n"
				<< " LimbBt received 'Unknown' as a limb type.\n"
				<< "##########################################\n";
		exit(-1);
	}

	btVector3 localInertia(0, 0, 0);

	mCollisionShape->calculateLocalInertia(mass, localInertia);

	// position the limb in the world
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(position);
	startTransform.setRotation(orientation);

	mMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mMotionState,
			mCollisionShape, localInertia);
	mBody = new btRigidBody(rbInfo);
	mBody->setDeactivationTime(PhysicsConfiguration::BULLET_DEACTIVATION_TIME);
	mBody->setSleepingThresholds(
			PhysicsConfiguration::BULLET_LINEAR_SLEEPING_TIME,
			PhysicsConfiguration::BULLET_ANGULAR_SLEEPING_TIME);
	mBody->setActivationState(DISABLE_DEACTIVATION);

	//Set the friction and restitution/elasticity of the rigid body
	mBody->setFriction(friction);
	mBody->setRollingFriction(friction);
	mBody->setRestitution(restitution);
	mBody->setAnisotropicFriction(
			mCollisionShape->getAnisotropicRollingFrictionDirection(),
			btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);

	//Set user pointer for proper return of creature/limb information etc..
	mBody->setUserPointer(limbModel);
	//add the limbModel pointer to the collision shape to get it back if we raycast for this object.
	mCollisionShape->setUserPointer(limbModel);

	mInitialRelativeXPosition = initialRelativePosition.getX();
	mInitialRelativeYPosition = initialRelativePosition.getY();
	mInitialRelativeZPosition = initialRelativePosition.getZ();

	mInitialWOrientation = initialOrientation.getW();
	mInitialXOrientation = initialOrientation.getX();
	mInitialYOrientation = initialOrientation.getY();
	mInitialZOrientation = initialOrientation.getZ();
}

btVector3 LimbBt::getIntersection(btVector3 origin, btVector3 direction) {
	return getPreciseIntersection(origin, direction);
}

btVector3 LimbBt::getPreciseIntersection(const btVector3 origin,
		const btVector3 direction) {
	// the ray caster currently only finds the intersection
	// when hitting the forward face of a triangle therefore,
	//the ray has to come from the outside of the shape
	btVector3 rayStart = origin + direction.normalized() * 100.0f;
	btVector3 rayEnd = origin;

//	btVector3 rayStart = origin;
//  btVector3 rayEnd = origin + direction.normalized() * 100.0f;

	//TODO: Debug output, draw test ray
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(rayStart,
			rayEnd, btVector3(1, 1, 0));

	btVector3 hitPosition = origin;

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayStart, rayEnd);

//	btCollisionWorld::AllHitsRayResultCallback rayCallback(rayStart, rayEnd);
//	allResults.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	//kF_UseGjkConvexRaytest flag is now enabled by default, use the faster but more approximate algorithm
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	rayCallback.m_flags &= !btTriangleRaycastCallback::kF_FilterBackfaces;
	rayCallback.m_collisionFilterGroup =
			PhysicsConfiguration::COL_CREATURE_TESTRAY;
	rayCallback.m_collisionFilterMask =
			PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH;

//	std::cout << "Worldhandle:" << mWorld << std::endl;
	mWorld->rayTest(rayStart, rayEnd, rayCallback);

//	for (int i = 0; i < rayCallback.m_hitFractions.size(); i++) {
//		btVector3 p = origin.lerp(rayEnd, rayCallback.m_hitFractions[i]);
//		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(p, 1,
//				btVector3(1, 0, 0));
//		SimulationManager::getSingleton()->getDebugDrawer().drawLine(p,
//				p + rayCallback.m_hitNormalWorld[i], btVector3(1, 0, 0));
//		return p;
//	}

	if (rayCallback.hasHit()) {
		btVector3 p = rayStart.lerp(rayEnd, rayCallback.m_closestHitFraction);
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(p, 1,
				btVector3(1, 0, 0));
		SimulationManager::getSingleton()->getDebugDrawer().drawLine(p,
				p + rayCallback.m_hitNormalWorld, btVector3(1, 0, 0));
		hitPosition = p;
//		std::cout
//				<< "############################################################\n"
//				<< "hit an object!\n" << rayStart.x() << ",\t" << rayStart.y()
//				<< ",\t" << rayStart.z() << "\t::rayStart\n" << hitPosition.x()
//				<< ",\t" << hitPosition.y() << ",\t" << hitPosition.z()
//				<< "\t::hitPosition\n" << rayEnd.x() << ",\t" << rayEnd.y()
//				<< ",\t" << rayEnd.z() << "\t::rayEnd\n"
//				<< "############################################################\n\n";

	} else {
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(rayStart,
				1, btVector3(1, 0, 0));
//		std::cout
//				<< "############################################################\n"
//				<< "no hit!\n" << rayStart.x() << ",\t" << rayStart.y() << ",\t"
//				<< rayStart.z() << "\t::rayStart\n" << rayEnd.x() << ",\t"
//				<< rayEnd.y() << ",\t" << rayEnd.z() << "\t::rayEnd\n"
//				<< "############################################################\n\n";
		//no hit
	}

	return hitPosition;
}

btVector3 LimbBt::getLocalFakeIntersection(const btVector3 origin,
		const btVector3 direction) {
	return mDimensions.length() / 2.0f * direction.normalized();
}

btVector3 LimbBt::getLocalIntersection(const btVector3 origin,
		const btVector3 direction) {
	// for the moment we fake the local intersection point until the real intersection can be calculated
	btVector3 intersection = getLocalPreciseIntersection(origin, direction);
	if (intersection.isZero()) {
		return getLocalFakeIntersection(origin, direction);
	} else {
		return intersection;
	}
}

void LimbBt::reset(const Ogre::Vector3 position) {
	btTransform initialTransform;
	mMotionState->getWorldTransform(initialTransform);

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

void LimbBt::reposition(const Ogre::Vector3 position) {
//	TODO: Implement repositioning limbs.
	btTransform initialTransform;
	mMotionState->getWorldTransform(initialTransform);

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

btVector3 LimbBt::getLocalPreciseIntersection(const btVector3 origin,
		const btVector3 direction) {
	return getPreciseIntersection(origin, direction) - origin;
}

void LimbBt::addToWorld() {
	if (!isInWorld()) {
		//TODO:Make all limbs collide as soon as the body creation works
		mWorld->addRigidBody(mBody, PhysicsConfiguration::COL_CREATURE,
				PhysicsConfiguration::CREATURE_COLLIDES_WITH);
//		mWorld->addRigidBody(mBody);
		LimbPhysics::addToWorld();
	}
}

void LimbBt::removeFromWorld() {
	if (isInWorld()) {
		mWorld->removeRigidBody(mBody);
		LimbPhysics::removeFromWorld();
	}
}

LimbBt* LimbBt::clone() {
	return new LimbBt(*this);
}
