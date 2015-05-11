//# corresponding header
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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

LimbBt::LimbBt() :
		mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(NULL) {
}

LimbBt::~LimbBt() {
	delete mBody;
}

void LimbBt::initialize(btDynamicsWorld* world,void* limb,
		LimbModel::PrimitiveType type, btVector3 position,
		btQuaternion orientation, btVector3 dimensions, btScalar mass) {
	mWorld = world;
	mDimensions = dimensions;
	btVector3 HalfExtents(dimensions.x() * 0.5f, dimensions.y() * 0.5f, dimensions.z() * 0.5f);
	switch (type) {
	case LimbModel::BLOCK:
		mCollisionShape = new btBoxShape(HalfExtents);
		break;
	case LimbModel::CAPSULE:
		mCollisionShape = new btCapsuleShape(btScalar(dimensions.x() * 0.5f),
				btScalar(dimensions.y()));
		break;
	case LimbModel::UNKNOWN:
		std::cout << "#################################################################\n LimbBt received 'Unknown' as a limb type.\n#################################################################";
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

	//Set user pointer for proper return of creature/limb information etc..
	mBody->setUserPointer(limb);
	//add the limb pointer to the collision shape to get it back if we raycast for this object.
	mCollisionShape->setUserPointer(limb);
}

btVector3 LimbBt::getIntersection(btVector3 origin, btVector3 direction) {
	return getPreciseIntersection(origin, direction);
}

btVector3 LimbBt::getPreciseIntersection(btVector3 origin,
		btVector3 direction) {
	//TODO: Fix raytesting with bullet to get the precise intersection point
	direction.normalize();
	direction *= 10000.f;
	btVector3 rayEnd = origin + direction;

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

btVector3 LimbBt::getLocalFakeIntersection(btVector3 origin,
		btVector3 direction) {
	return mDimensions.length() / 2.0f * direction.normalized();
}

btVector3 LimbBt::getLocalIntersection(btVector3 origin, btVector3 direction) {
	// for the moment we fake the local intersection point until the real intersection can be calculated
	return getLocalFakeIntersection(origin, direction);
	//return getLocalPreciseIntersection(origin, direction);
}

btVector3 LimbBt::getLocalPreciseIntersection(btVector3 origin,
		btVector3 direction) {
	return getPreciseIntersection(origin, direction) - origin;

}

void LimbBt::addToWorld() {
	if (!isInWorld()) {
		mWorld->addRigidBody(mBody);
		setInWorld(true);
	}
}

void LimbBt::removeFromWorld() {
	if (isInWorld()) {
		mWorld->removeRigidBody(mBody);
		setInWorld(false);
	}
}

