/*
 * Joint.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include <controller/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <model/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
#include <model/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <SimulationManager.hpp>
#include <view/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp>

//## configuration headers
//## controller headers

//## model headers

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
	((JointO3D*) mJointGraphics)->initialize(simulationManager, limbA, limbB,
			localA, localB);

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
	mJointGraphics->update();
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

void Joint::setAngularStiffness(double jointPitchStiffness,
		double jointYawStiffness, double jointRollStiffness) {
	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
			jointRollStiffness);
}

void Joint::setAngularDamping(double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
			springYawDampingCoefficient, springRollDampingCoefficient);
}
