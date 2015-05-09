//# corresponding header
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
#include <LinearMath/btVector3.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/physics/PhysicsController.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp>

//## utils headers

#ifndef NULL
#define NULL 0
#endif

Joint::Joint() :
		mJointGraphics(NULL), mJointModel(NULL) {
}

Joint::~Joint() {
	delete mJointGraphics;
	delete mJointModel;
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
	mJointModel = new JointModel();
	mJointModel->initialize(
			simulationManager->getPhysicsController().getDynamicsWorld(),
			limbA->getLimbPhysics()->getRigidBody(),
			limbB->getLimbPhysics()->getRigidBody(), localA, localB);

	// Update the state of the joint.
	update();
}

void Joint::initializeRotationalLimitMotors(btVector3 maxForces,
		btVector3 maxSpeeds) {
	((JointBt*) mJointModel->getJointPhysics())->initializeRotationalLimitMotors(
			maxForces, maxSpeeds);
}

void Joint::update() {
	mJointModel->getJointPhysics()->update();
	mJointGraphics->update();
}

/**
 * Add the joint to the world.
 */
void Joint::addToWorld() {
	mJointGraphics->addToWorld();
	mJointModel->getJointPhysics()->addToWorld();
}

/**
 * Remove the joint from the world.
 */
void Joint::removeFromWorld() {
	mJointGraphics->removeFromWorld();
	mJointModel->getJointPhysics()->removeFromWorld();
}

void Joint::setAngularLimits(Ogre::Vector3 angularLowerLimit,
		Ogre::Vector3 angularUpperLimit) {
	mJointModel->getJointPhysics()->setAngularLimits(angularLowerLimit,
			angularUpperLimit);
}

void Joint::setAngularStiffness(double jointPitchStiffness,
		double jointYawStiffness, double jointRollStiffness) {
	mJointModel->getJointPhysics()->setAngularStiffness(jointPitchStiffness,
			jointYawStiffness, jointRollStiffness);
}

void Joint::setAngularDamping(double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
	mJointModel->getJointPhysics()->setAngularDamping(
			springPitchDampingCoefficient, springYawDampingCoefficient,
			springRollDampingCoefficient);
}

void Joint::enableAngularMotor(bool pitchEnable, bool yawEnable,
		bool rollEnable) {
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(0,
			pitchEnable);
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(1,
			yawEnable);
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(2,
			rollEnable);
}
