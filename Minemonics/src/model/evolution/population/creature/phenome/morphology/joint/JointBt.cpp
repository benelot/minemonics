/*
 * JointBt.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <model/evolution/population/creature/phenome/morphology/joint/JointBt.h>

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

JointBt::JointBt() :
		mG6DofJoint(NULL),mWorld(NULL) {
	// TODO Auto-generated constructor stub

}

JointBt::~JointBt() {
	// TODO Auto-generated destructor stub
}

void JointBt::initialize(btDynamicsWorld* world,btRigidBody* bodyA, btRigidBody* bodyB,
		btTransform& tframeInA, btTransform& tframeInB) {
	mWorld = world;
	mG6DofJoint = new btGeneric6DofSpringConstraint(*bodyA, *bodyB, tframeInA,
			tframeInB, true/*use fixed frame A for linear limits*/);
	mG6DofJoint->setLinearLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setLinearUpperLimit(btVector3(0, 0, 0));

	mG6DofJoint->setAngularLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setAngularUpperLimit(btVector3(0, 0, 0));

	mG6DofJoint->setEquilibriumPoint();

	//debug drawing
	mG6DofJoint->setDbgDrawSize(btScalar(5.f));
}

void JointBt::addToWorld() {
	mWorld->addConstraint((btTypedConstraint*) mG6DofJoint, true);
}

void JointBt::removeFromWorld() {
	mWorld->removeConstraint((btTypedConstraint*) mG6DofJoint);
}
