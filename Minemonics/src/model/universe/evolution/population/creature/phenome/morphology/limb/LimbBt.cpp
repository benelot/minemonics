//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
//# forward declarations
//# system headers
#include <stddef.h>
#include <iostream>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <LinearMath/btDefaultMotionState.h>
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
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

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(position);
	startTransform.setRotation(orientation);

	mMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mMotionState,
			mCollisionShape, localInertia);
	mBody = new btRigidBody(rbInfo);

	//Set the friction and restitution/elasticity of the rigid body
	mBody->setFriction(friction);
	mBody->setRestitution(restitution);

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
	//TODO: Fix raytesting with bullet to get the precise intersection point
	btVector3 nDirection = direction;
	nDirection.normalize();
	nDirection *= 10000.f;
	btVector3 rayEnd = origin + nDirection;

	btVector3 hitPosition(0, 0, 0);

	btCollisionWorld::ClosestRayResultCallback rayCallback(origin, rayEnd);
	mWorld->rayTest(origin, rayEnd, rayCallback);

	if (rayCallback.hasHit()) {
		hitPosition = rayCallback.m_hitPointWorld;
		//Normal = RayCallback.m_hitNormalWorld;
		std::cout
				<< "############################################################\n"
				<< "hit an object!\n" << origin.x() << ",\t" << origin.y()
				<< ",\t" << origin.z() << "\t::Origin\n" << hitPosition.x()
				<< ",\t" << hitPosition.y() << ",\t" << hitPosition.z()
				<< "\t::hit\n" << rayEnd.x() << ",\t" << rayEnd.y() << ",\t"
				<< rayEnd.z() << "\t::rayEnd\n"
				<< "############################################################\n\n";

		//return hit
		return hitPosition;
	}
	std::cout
			<< "############################################################\n"
			<< "no hit!\n" << origin.x() << ",\t" << origin.y() << ",\t"
			<< origin.z() << "\t::Origin\n" << rayEnd.x() << ",\t" << rayEnd.y()
			<< ",\t" << rayEnd.z() << "\t::rayEnd\n"
			<< "############################################################\n\n";
	//no hit
	return origin;
}

btVector3 LimbBt::getLocalFakeIntersection(const btVector3 origin,
		const btVector3 direction) {
	return mDimensions.length() / 2.0f * direction.normalized() * 5.0f;
}

btVector3 LimbBt::getLocalIntersection(const btVector3 origin,
		const btVector3 direction) {
	// for the moment we fake the local intersection point until the real intersection can be calculated
	return getLocalFakeIntersection(origin, direction);
	//return getLocalPreciseIntersection(origin, direction);
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
		mWorld->addRigidBody(mBody);
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
