//# corresponding header
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp>
#include <model/universe/PlanetModel.hpp>

//##view headers
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointO3D.hpp>

//## utils headers

BoostLogger Joint::mBoostLogger; /*<! initialize the boost logger*/
Joint::_Init Joint::_initializer;
Joint::Joint(Creature* const creature, Limb* const limbA, Limb* const limbB,
	const Ogre::Vector3 pivotInW, const int indexA, const int indexB,
	const int ownIndex, JointPhysics::JointType jointType,
	Ogre::Vector3 jointPitchAxis, Ogre::Vector3 jointYawAxis,
	Ogre::Vector3 jointLowerLimits, Ogre::Vector3 jointUpperLimits) {
	// initialize the model of the joint
	switch (creature->getPhysicsModelType()) {
	case PhysicsController::RigidbodyModel:
		mJointModel =
			new SRBJointModel(
				creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				((SRBLimbBt*) limbA->getLimbPhysics())->getRigidBody(),
				((SRBLimbBt*) limbB->getLimbPhysics())->getRigidBody(),
				pivotInW, indexA, indexB, ownIndex, jointType, jointPitchAxis,
				jointYawAxis, jointLowerLimits, jointUpperLimits);

		break;
	case PhysicsController::FeatherstoneModel:
		mJointModel =
			new FSJointModel(
				creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
				(FSLimbModel*) limbA->getLimbModel(),
				(FSLimbModel*) limbB->getLimbModel(), pivotInW, indexA, indexB,
				ownIndex, jointType, jointPitchAxis, jointYawAxis,
				jointLowerLimits, jointUpperLimits);
		break;
	default:
		break;
	}
	mJointModel->initialize();

	// Define the new component as a limb
	Component::initialize(mJointModel);

	// initialize the graphics part of the joint
	mJointGraphics = new JointO3D(mJointModel);
	((JointO3D*) mJointGraphics)->initialize();

	// Update the state of the joint.
	update(0);
}

Joint::Joint(const Joint& joint) :
	mJointModel(joint.mJointModel) {
	mJointGraphics = joint.mJointGraphics->clone();
}

Joint::Joint(const JointModel& jointModel) :
	mJointModel(NULL) {
	mJointGraphics = new JointO3D(mJointModel);
}

Joint::Joint(JointModel* const jointModel) :
	mJointModel(jointModel) {
	mJointGraphics = new JointO3D(jointModel);
}

Joint::~Joint() {
	delete mJointGraphics;
	mJointGraphics = NULL;

	mJointModel = NULL;
}

void Joint::initialize(Creature* const creature, Limb* const limbA,
	Limb* const limbB, const btTransform localA, const btTransform localB,
	const int indexA, const int indexB, const int ownIndex) {

}

void Joint::generateMotors(const Ogre::Vector3 maxForces,
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits,
	bool positionControlled) {
	mJointModel->generateMotors(maxForces, lowerLimits, upperLimits,
		positionControlled);
}

void Joint::update(double timeSinceLastTick) {
	mJointGraphics->update(timeSinceLastTick);
	mJointModel->update(timeSinceLastTick);
}

/**
 * Add the joint to the physics world.
 */
void Joint::addToPhysicsWorld() {
	if (!getJointPhysics()->isInWorld()) {
		getJointPhysics()->addToWorld();
	}
}

/**
 * Add the joint to the world.
 */
void Joint::addToWorld() {
	if (!mJointGraphics->isInWorld()) {
		mJointGraphics->addToWorld();
	}

	if (!getJointPhysics()->isInWorld()) {
		getJointPhysics()->addToWorld();
	}
}

/**
 * Remove the joint from the world.
 */
void Joint::removeFromWorld() {
	if (mJointGraphics->isInWorld()) {
		mJointGraphics->removeFromWorld();
	}

	if (getJointPhysics()->isInWorld()) {
		getJointPhysics()->removeFromWorld();
	}
}

void Joint::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
	const Ogre::Vector3 angularUpperLimit) {
	mJointModel->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void Joint::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
	mJointModel->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
		jointRollStiffness);
}

void Joint::setAngularDamping(const double springPitchDampingCoefficient,
	const double springYawDampingCoefficient,
	const double springRollDampingCoefficient) {
	mJointModel->setAngularDamping(springPitchDampingCoefficient,
		springYawDampingCoefficient, springRollDampingCoefficient);
}

void Joint::reset(const Ogre::Vector3 position) {
	mJointModel->reset(position);
}

void Joint::reposition(const Ogre::Vector3 position) {
	mJointModel->reposition(position);
}

Joint* Joint::clone() {
	return new Joint(*this);
}

JointPhysics* const Joint::getJointPhysics() const {
	return mJointModel->getJointPhysics();
}

/**
 * Get the motors of this joint.
 * @return The motors of this joint.
 */
const std::vector<Motor*>& Joint::getMotors() const {
	return mJointModel->getJointPhysics()->getMotors();
}
