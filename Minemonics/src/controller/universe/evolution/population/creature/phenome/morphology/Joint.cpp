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

BoostLogger Joint::mBoostLogger; /*<! initialize the boost logger*/
Joint::_Init Joint::_initializer;
Joint::Joint() :
		mJointGraphics(NULL), mJointModel(NULL) {
}

Joint::Joint(const Joint& joint) :
		mJointModel(joint.mJointModel) {
	mJointGraphics = joint.mJointGraphics->clone();
}

Joint::Joint(const JointModel& jointModel) {
	mJointModel = new JointModel(jointModel);
	mJointGraphics = new JointO3D();
	((JointO3D*) mJointGraphics)->initialize();
}

Joint::Joint(JointModel* const jointModel) {
	mJointModel = jointModel;
	mJointGraphics = new JointO3D();
	((JointO3D*) mJointGraphics)->initialize();
}

Joint::~Joint() {
	delete mJointGraphics;
	mJointGraphics = NULL;

	delete mJointModel;
	mJointModel = NULL;
}

void Joint::initialize(Creature* const creature, Limb* const limbA,
		Limb* const limbB, const btTransform localA, const btTransform localB,
		const int indexA, const int indexB, const int ownIndex) {

	// initialize the physics model of the joint
	mJointModel = new JointModel();
	mJointModel->initialize(
			creature->getPlanet()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			limbA->getLimbPhysics()->getRigidBody(),
			limbB->getLimbPhysics()->getRigidBody(), localA, localB, indexA,
			indexB, ownIndex);

	// Define the new component as a limb
	Component::initialize(mJointModel);

	// initialize the graphics part of the joint
	mJointGraphics = new JointO3D();
	((JointO3D*) mJointGraphics)->initialize();

	// Update the state of the joint.
	update();
}

void Joint::initializeRotationalLimitMotors(const Ogre::Vector3 maxForces,
		const Ogre::Vector3 maxSpeeds) {
	mJointModel->initializeRotationalLimitMotors(maxForces, maxSpeeds);
}

void Joint::update() {
	mJointGraphics->update();
	getJointPhysics()->update();
}

/**
 * Add the joint to the world.
 */
void Joint::addToWorld() {
	mJointGraphics->addToWorld();
	getJointPhysics()->addToWorld();
}

/**
 * Remove the joint from the world.
 */
void Joint::removeFromWorld() {
	mJointGraphics->removeFromWorld();
	getJointPhysics()->removeFromWorld();
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

void Joint::enableAngularMotor(const bool pitchEnable, const bool yawEnable,
		const bool rollEnable) {
	getJointPhysics()->setRotationalLimitMotorEnabled(JointPhysics::RDOF_PITCH,
			pitchEnable);
	getJointPhysics()->setRotationalLimitMotorEnabled(JointPhysics::RDOF_YAW,
			yawEnable);
	getJointPhysics()->setRotationalLimitMotorEnabled(JointPhysics::RDOF_ROLL,
			rollEnable);
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
