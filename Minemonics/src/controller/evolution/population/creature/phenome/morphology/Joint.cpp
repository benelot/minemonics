/*
 * Joint.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Joint.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"
#include "model/evolution/population/creature/phenome/morphology/JointBt.h"

//## view headers
#include "view/ogre3D/evolution/population/creature/phenome/morphology/JointO3D.h"

//## utils headers

#ifndef NULL
#define NULL 0
#endif

Joint::Joint() :
		mJointGraphics(NULL), mJointPhysics(NULL) {
}

Joint::~Joint() {
	delete mJointGraphics;
	delete mJointPhysics;
}

void Joint::initialize(SimulationManager* simulationManager, Limb* limbA,
		Limb* limbB, btTransform localA, btTransform localB) {
	// Define the new component as a limb
	Component::initialize(Component::JointComponent);

	// initialize the graphics part of the joint
	mJointGraphics = new JointO3D();
	((JointO3D*) mJointGraphics)->initialize(simulationManager);

	// initialize the physics model of the joint
	mJointPhysics = new JointBt();
	((JointBt*) mJointPhysics)->initialize(
			simulationManager->getPhysicsController().getDynamicsWorld(),
			limbA->getLimbPhysics()->getRigidBody(),
			limbB->getLimbPhysics()->getRigidBody(), localA, localB);

	// Update the state of the joint.
	update();
}

void Joint::update() {

}

/**
 * Add the joint to the world.
 */
void Joint::addToWorld() {
	mJointGraphics->addToWorld();
	mJointPhysics->addToWorld();
}

/**
 * Remove the joint from the world.
 */
void Joint::removeFromWorld() {
	mJointGraphics->removeFromWorld();
	mJointPhysics->removeFromWorld();
}

void Joint::setAngularLimits(Ogre::Vector3 angularLowerLimit,
		Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}
