//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

JointPhysics::JointPhysics() :
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointPitchAxisX(1), mJointPitchAxisY(
		0), mJointPitchAxisZ(0), mJointPitchEnabled(true), mJointPitchMaxAngle(
		0), mJointPitchMinAngle(0), mJointRollEnabled(true), mJointRollMaxAngle(
		0), mJointRollMinAngle(0), mJointYawEnabled(true), mJointYawMaxAngle(0), mJointYawMinAngle(
		0) {
}

JointPhysics::~JointPhysics() {
}

bool JointPhysics::equals(const JointPhysics& jointPhysics) const {
	if (mInWorld != jointPhysics.mInWorld) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}

	if (mJointPitchAxisX != jointPhysics.mJointPitchAxisX) {
		return false;
	}

	if (mJointPitchAxisY != jointPhysics.mJointPitchAxisY) {
		return false;
	}

	if (mJointPitchEnabled != jointPhysics.mJointPitchEnabled) {
		return false;
	}

	if (mJointPitchMaxAngle != jointPhysics.mJointPitchMaxAngle) {
		return false;
	}

	if (mJointPitchMinAngle != jointPhysics.mJointPitchMinAngle) {
		return false;
	}

	if (mJointRollEnabled != jointPhysics.mJointRollEnabled) {
		return false;
	}

	if (mJointRollMaxAngle != jointPhysics.mJointRollMaxAngle) {
		return false;
	}

	if (mJointRollMinAngle != jointPhysics.mJointRollMinAngle) {
		return false;
	}

	if (mJointYawEnabled != jointPhysics.mJointYawEnabled) {
		return false;
	}

	if (mJointYawMaxAngle != jointPhysics.mJointYawMaxAngle) {
		return false;
	}

	if (mJointYawMinAngle != jointPhysics.mJointYawMinAngle) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}
	return true;
}
