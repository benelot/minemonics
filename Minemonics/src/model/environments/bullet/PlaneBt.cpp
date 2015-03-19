/*
 * PlaneBt.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#include "PlaneBt.h"

PlaneBt::PlaneBt() :
		mGroundBody(NULL), mGroundMotionState(NULL), mGroundShape(NULL) {

}

PlaneBt::~PlaneBt() {
	// TODO Auto-generated destructor stub
}

void PlaneBt::initialize() {
	/* Another primitive collision shape, an infinite plane.
	 To create a plane you have to pass both the plane's
	 normal vector (Vec3(nx, ny, nz)) and the plane constant
	 (d, which is the distance of the plane's origin.
	 Planes can only be used for static objects.
	 */
	mGroundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 50);

	btScalar mass = 0; //rigidbody is static if mass is zero, otherwise dynamic
	btVector3 localInertia(0, 0, 0);

	mGroundShape->calculateLocalInertia(mass, localInertia);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -50, 0));

	mGroundMotionState = new btDefaultMotionState(groundTransform); //motionstate provides interpolation capabilities, and only synchronizes 'active' objects
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, mGroundMotionState,
			mGroundShape, localInertia);
	mGroundBody = new btRigidBody(rbInfo);

	// disable debug visualization
	mGroundBody->setCollisionFlags(mGroundBody->getCollisionFlags() | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
}

