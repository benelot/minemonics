//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//# forward declarations
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
		mIndexA(jointModel.mIndexA), mIndexB(jointModel.mIndexB) {
	mJointPhysics = jointModel.mJointPhysics->clone();
}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
}

void JointModel::initialize(btDynamicsWorld* const world,
		btRigidBody* const limbA, btRigidBody* const limbB,
		const btTransform localA, const btTransform localB, const int indexA,
		const int indexB, const int ownIndex) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mIndexA = indexA;
	mIndexB = indexB;

	mJointPhysics = new JointBt(world, limbA, limbB, localA, localB);
}

void JointModel::update(double timeSinceLastTick){
	mJointPhysics->update(timeSinceLastTick);
}

void JointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
		const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void JointModel::setAngularStiffness(const double jointPitchStiffness,
		const double jointYawStiffness, const double jointRollStiffness) {
	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
			jointRollStiffness);
}

void JointModel::setAngularDamping(const double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
			springYawDampingCoefficient, springRollDampingCoefficient);
}

bool JointModel::equals(const JointModel& jointModel) const {
	if (((JointBt*) mJointPhysics)->equals(
			(*(JointBt*) jointModel.mJointPhysics))) {
		return false;
	}

	if (mIndexA != jointModel.mIndexA) {
		return false;
	}

	if (mIndexB != jointModel.mIndexB) {
		return false;
	}

	if (mOwnIndex != jointModel.mOwnIndex) {
		return false;
	}

	if (mComponentType != jointModel.mComponentType) {
		return false;
	}

	return true;
}

void JointModel::reset(const Ogre::Vector3 position) {
	mJointPhysics->reset(position);
}

void JointModel::reposition(const Ogre::Vector3 position) {
	mJointPhysics->reposition(position);
}

JointModel* JointModel::clone() {
	return new JointModel(*this);
}

bool JointModel::isStrained() {
	return mJointPhysics->isStrained();
}

void JointModel::enableAngularMotor(const bool pitchEnable,
		const bool yawEnable, const bool rollEnable) {
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_PITCH,
			pitchEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_YAW,
			yawEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_ROLL,
			rollEnable);
}

void JointModel::initializeRotationalLimitMotors(const Ogre::Vector3 maxForces,
		const Ogre::Vector3 maxSpeeds) {
	((JointBt*) mJointPhysics)->initializeRotationalLimitMotors(
			OgreBulletUtils::convert(maxForces),
			OgreBulletUtils::convert(maxSpeeds));
}

