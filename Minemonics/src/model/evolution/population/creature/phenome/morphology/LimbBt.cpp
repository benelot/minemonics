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
}

btVector3 LimbBt::getLocalIntersection(btVector3 origin, btVector3 direction) {
	return getLocalPreciseIntersection(origin,direction);
}

btVector3 LimbBt::getLocalPreciseIntersection(btVector3 origin, btVector3 direction) {
	direction = direction * 1000.0f;

	btVector3 hitPosition;

	btCollisionWorld::ClosestRayResultCallback RayCallback(
			origin,
			direction);
	mWorld->rayTest(btVector3(origin),
			btVector3(direction),
			RayCallback);

	if (RayCallback.hasHit()) {
		hitPosition = RayCallback.m_hitPointWorld;
		//Normal = RayCallback.m_hitNormalWorld;
	}
	return hitPosition;

}

void LimbBt::addToWorld() {
	mWorld->addRigidBody(mBody);
}

void LimbBt::removeFromWorld() {
	mWorld->removeRigidBody(mBody);
}

