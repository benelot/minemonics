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
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>

//##view headers
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp>

//## utils headers

#ifndef NULL
#define NULL 0
#endif

Joint::Joint() :
		mJointGraphics(NULL), mJointModel(NULL) {
}

Joint::Joint(const Joint& joint) {
	mJointGraphics = joint.mJointGraphics->clone();
	mJointModel = joint.mJointModel->clone();
}

Joint::~Joint() {
	delete mJointGraphics;
	delete mJointModel;
}

void Joint::initialize(Creature* creature, Limb* limbA, Limb* limbB,
		btTransform localA, btTransform localB, int indexA, int indexB,
		int ownIndex) {

	// initialize the physics model of the joint
	mJointModel = new JointModel();
	mJointModel->initialize(
			creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			limbA->getLimbPhysics()->getRigidBody(),
			limbB->getLimbPhysics()->getRigidBody(), localA, localB, indexA,
			indexB, ownIndex);

	buildFrom(mJointModel);
}

void Joint::initializeRotationalLimitMotors(Ogre::Vector3 maxForces,
		Ogre::Vector3 maxSpeeds) {
	mJointModel->initializeRotationalLimitMotors(maxForces, maxSpeeds);
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
	mJointModel->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void Joint::setAngularStiffness(double jointPitchStiffness,
		double jointYawStiffness, double jointRollStiffness) {
	mJointModel->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
			jointRollStiffness);
}

void Joint::setAngularDamping(double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
	mJointModel->setAngularDamping(springPitchDampingCoefficient,
			springYawDampingCoefficient, springRollDampingCoefficient);
}

void Joint::enableAngularMotor(bool pitchEnable, bool yawEnable,
		bool rollEnable) {
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(
			JointPhysics::RDOF_PITCH, pitchEnable);
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(
			JointPhysics::RDOF_YAW, yawEnable);
	mJointModel->getJointPhysics()->setRotationalLimitMotorEnabled(
			JointPhysics::RDOF_ROLL, rollEnable);
}

void Joint::buildFrom(JointModel* jointModel) {
	// Define the new component as a limb
	Component::initialize(ComponentModel::JointComponent, jointModel);

	// initialize the graphics part of the joint
	mJointGraphics = new JointO3D();
	((JointO3D*) mJointGraphics)->initialize();

	if (mJointModel == NULL) {
		mJointModel = jointModel;
	}
	// Update the state of the joint.
	update();
}

void Joint::reset(Ogre::Vector3 position) {
	mJointModel->reset(position);
}

void Joint::reposition(Ogre::Vector3 position) {
	mJointModel->reposition(position);
}

Joint* Joint::clone() {
	return new Joint(*this);
}
