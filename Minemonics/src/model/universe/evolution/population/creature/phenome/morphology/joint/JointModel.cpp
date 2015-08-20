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
		const btTransform localA, const btTransform localB,
		const std::vector<LimbModel*>::size_type indexA,
		const std::vector<LimbModel*>::size_type indexB,
		const std::vector<LimbModel*>::size_type ownIndex) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mIndexA = indexA;
	mIndexB = indexB;
	mOwnIndex = ownIndex;

	mJointPhysics = new JointBt(world, limbA, limbB, localA, localB);

	//TODO: proof of concept, make better.
//	JointAngleProprioceptor* angleceptor = new JointAngleProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH);
//	mSensors.push_back(angleceptor);
//	mAngleceptors.push_back(angleceptor);
//
//	JointForceProprioceptor* forceceptor = new JointForceProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH);
//	mSensors.push_back(forceceptor);
//	mForceceptors.push_back(forceceptor);
//
//	JointLimitProprioceptor* limitceptor = new JointLimitProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH, JointLimitProprioceptor::BOTH_LIMITS);
//	mSensors.push_back(limitceptor);
//	mLimitceptors.push_back(limitceptor);
}

void JointModel::update(double timeSinceLastTick) {
	mJointPhysics->update(timeSinceLastTick);

	for (std::vector<Sensor*>::iterator sit = mSensors.begin();
			sit != mSensors.end(); sit++) {
		(*sit)->update(timeSinceLastTick);
	}

//	std::cout << std::endl << "AngleSensors:";
//	for (std::vector<JointAngleProprioceptor*>::iterator tit = mAngleceptors.begin();
//			tit != mAngleceptors.end(); tit++) {
//		std::cout << (*tit)->getAngle() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "ForceSensors:";
//	for (std::vector<JointForceProprioceptor*>::iterator tit = mForceceptors.begin();
//			tit != mForceceptors.end(); tit++) {
//		std::cout << (*tit)->getForce() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "LimitSensors:";
//	for (std::vector<JointLimitProprioceptor*>::iterator tit = mLimitceptors.begin();
//			tit != mLimitceptors.end(); tit++) {
//		std::cout << (*tit)->getLimitError() << "|";
//	}
//	std::cout << std::endl;
}

void JointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
		const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setLimits(angularUpperLimit);
}

void JointModel::setAngularStiffness(const double jointPitchStiffness,
		const double jointYawStiffness, const double jointRollStiffness) {
//	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
//			jointRollStiffness);
}

void JointModel::setAngularDamping(const double springPitchDampingCoefficient,
		double springYawDampingCoefficient,
		double springRollDampingCoefficient) {
//	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
//			springYawDampingCoefficient, springRollDampingCoefficient);
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

