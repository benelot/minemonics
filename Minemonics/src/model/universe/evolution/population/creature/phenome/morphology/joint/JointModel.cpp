//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
//## controller headers
//## model headers
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers

JointModel::JointModel() :
		mJointPhysics(NULL), mIndexA(-1), mIndexB(-1) {

}

JointModel::JointModel(const JointModel& jointModel) :
		mIndexA(-1), mIndexB(-1) {
	mJointPhysics = jointModel.mJointPhysics->clone();
}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
}

void JointModel::initialize(btDynamicsWorld* world, btRigidBody* limbA,
		btRigidBody* limbB, btTransform localA, btTransform localB, int indexA,
		int indexB, int ownIndex) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mIndexA = indexA;
	mIndexB = indexB;

	mJointPhysics = new JointBt();
	((JointBt*) mJointPhysics)->initialize(world, limbA, limbB, localA, localB);
}

void JointModel::setAngularLimits(Ogre::Vector3 angularLowerLimit,
		Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void JointModel::setAngularStiffness(double jointPitchStiffness,
		double jointYawStiffness, double jointRollStiffness) {
	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
			jointRollStiffness);
}

void JointModel::setAngularDamping(double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
			springYawDampingCoefficient, springRollDampingCoefficient);
}

bool JointModel::equals(const JointModel& jointModel) const {
	//TODO: Implement joint model equals
//	if(mJointPhysics->equals(*jointModel.mJointPhysics))
//	{
//		return false;
//	}

	return true;
}

void JointModel::reset(Ogre::Vector3 position) {
	mJointPhysics->reset(position);
}

void JointModel::reposition(Ogre::Vector3 position) {
	mJointPhysics->reposition(position);
}

JointModel* JointModel::clone() {
	return new JointModel(*this);
}

bool JointModel::isStrained() {
	return mJointPhysics->isStrained();
}

void JointModel::enableAngularMotor(bool pitchEnable, bool yawEnable,
		bool rollEnable) {
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_PITCH,
			pitchEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_YAW,
			yawEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_ROLL,
			rollEnable);
}

void JointModel::initializeRotationalLimitMotors(Ogre::Vector3 maxForces,
		Ogre::Vector3 maxSpeeds) {
	((JointBt*) mJointPhysics)->initializeRotationalLimitMotors(
			OgreBulletUtils::convert(maxForces),
			OgreBulletUtils::convert(maxSpeeds));
}

