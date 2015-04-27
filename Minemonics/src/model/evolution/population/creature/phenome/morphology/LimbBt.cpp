/*
 * LimbBt.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "LimbBt.h"

//# forward declarations
//# system headers
#include <iostream>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/PhysicsConfiguration.h"
#include "configuration/MorphologyConfiguration.h"

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

void LimbBt::initialize(btDynamicsWorld* world,
		MorphologyConfiguration::PrimitiveType type, btVector3 position,
		btQuaternion orientation, btVector3 size, btScalar mass) {
	mWorld = world;
	mSize = size;
	btVector3 HalfExtents(size.x() * 0.5f, size.y() * 0.5f, size.z() * 0.5f);
	switch (type) {
	case MorphologyConfiguration::BLOCK:
		mCollisionShape = new btBoxShape(HalfExtents);
		break;
	case MorphologyConfiguration::CAPSULE:
		mCollisionShape = new btCapsuleShape(btScalar(size.x() * 0.5f),
				btScalar(size.y()));
		break;
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
	//TODO: Set user pointer for proper return of creature/limb information etc..
	//mBody->setUserPointer(NULL);
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
				<< "hit an object!\n" << origin.x() << ",\t" << origin.y() << ",\t"
				<< origin.z() << "\t::Origin\n" << hitPosition.x() << ",\t"
				<< hitPosition.y() << ",\t" << hitPosition.z() << "\t::hit\n"
				<< rayEnd.x() << ",\t" << rayEnd.y() << ",\t" << rayEnd.z()
				<< "\t::rayEnd\n"
				<< "############################################################\n\n";

		//return hit
		return hitPosition;
	}
	std::cout
			<< "############################################################\n"
			<< "no hit!\n" << origin.x() << ",\t" << origin.y() << ",\t"
			<< origin.z() << "\t::Origin\n" << rayEnd.x() << ",\t"
			<< rayEnd.y() << ",\t" << rayEnd.z() << "\t::rayEnd\n"
			<< "############################################################\n\n";
	//no hit
	return origin;
}

btVector3 LimbBt::getLocalFakeIntersection(btVector3 origin, btVector3 direction) {
	return mSize.length()/2.0f*direction.normalized();
}

btVector3 LimbBt::getLocalIntersection(btVector3 origin, btVector3 direction) {
	// for the moment we fake the local intersection point until the real intersection can be calculated
	return getLocalFakeIntersection(origin, direction) ;
	//return getLocalPreciseIntersection(origin, direction);
}

btVector3 LimbBt::getLocalPreciseIntersection(btVector3 origin,
		btVector3 direction) {
	return getPreciseIntersection(origin, direction) - origin;

}

void LimbBt::addToWorld() {
	mWorld->addRigidBody(mBody);
}

void LimbBt::removeFromWorld() {
	mWorld->removeRigidBody(mBody);
}

