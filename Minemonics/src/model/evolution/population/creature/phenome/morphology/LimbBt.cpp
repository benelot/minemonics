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
//## controller headers
//## model headers
//## view headers
//## utils headers
#include "configuration/PhysicsConfiguration.h"

LimbBt::LimbBt() :
		mBody(NULL), mCollisionShape(NULL), mMotionState(NULL) {

}

LimbBt::~LimbBt() {
	// TODO Auto-generated destructor stub
}

void LimbBt::initialize(Limb::PrimitiveType type, btVector3 position,
		btQuaternion orientation, btVector3 size, btScalar mass) {
	btVector3 HalfExtents(size.x() * 0.5f, size.y() * 0.5f, size.z() * 0.5f);
	switch (type) {
	case Limb::BLOCK:
		mCollisionShape = new btBoxShape(HalfExtents);
		break;
	case Limb::CAPSULE:
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

