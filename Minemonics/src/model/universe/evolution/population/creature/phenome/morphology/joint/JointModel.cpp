//# corresponding header

#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/joint/SRBJointBt.hpp>
#include <configuration/Definitions.hpp>
#include <LinearMath/btTransform.h>
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/joint/SRBJointModel.hpp>

//## view headers
//## utils headers

JointModel::JointModel() :
	mJointPhysics(NULL), mParentIndex(-1), mChildIndex(-1), mOwnIndex(-1) {

}

JointModel::JointModel(const JointModel& jointModel) :
	mParentIndex(jointModel.mParentIndex), mChildIndex(jointModel.mChildIndex), mOwnIndex(
		jointModel.mOwnIndex) {
	mJointPhysics = jointModel.mJointPhysics->clone();
}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
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
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void JointModel::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
//	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
//			jointRollStiffness);
}

void JointModel::setAngularDamping(const double springPitchDampingCoefficient,
	double springYawDampingCoefficient, double springRollDampingCoefficient) {
//	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
//			springYawDampingCoefficient, springRollDampingCoefficient);
}

bool JointModel::equals(const JointModel& jointModel) const {
	if (!ComponentModel::equals(jointModel)) {
		return false;
	}

	if (!mJointPhysics->equals(*jointModel.mJointPhysics)) {
		return false;
	}

	if (mParentIndex != jointModel.mParentIndex) {
		return false;
	}

	if (mChildIndex != jointModel.mChildIndex) {
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

//bool JointModel::isStrained() {
//	return mJointPhysics->isStrained();
//}

void JointModel::generateMotors(const Ogre::Vector3 maxForces,
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits) {
	mJointPhysics->generateMotors(OgreBulletUtils::convert(maxForces),
		OgreBulletUtils::convert(lowerLimits),
		OgreBulletUtils::convert(upperLimits));
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

