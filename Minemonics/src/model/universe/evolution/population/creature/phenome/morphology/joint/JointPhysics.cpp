//# corresponding header
#include <LinearMath/btVector3.h>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/effector/motor/SRBServoMotor.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers
//## utils headers

JointPhysics::JointPhysics() :
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointPitchEnabled(
		true), mJointRollEnabled(true), mJointYawEnabled(true), mJointMaxAngle(
		0, 0, 0), mJointMaxForces(0, 0, 0), mJointMaxSpeeds(0, 0, 0), mJointMinAngle(
		0, 0, 0), mJointPitchAxis(1, 0, 0) {
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

//	if (mJointPitchAxis != jointPhysics.mJointPitchAxis) {
//		return false;
//	}

	if (mJointPitchEnabled != jointPhysics.mJointPitchEnabled) {
		return false;
	}

//	if (mJointMinAngle != jointPhysics.mJointMinAngle) {
//		return false;
//	}
//
//	if (mJointMaxAngle != jointPhysics.mJointMaxAngle) {
//		return false;
//	}

	if (mJointMaxForces != jointPhysics.mJointMaxForces) {
		return false;
	}

	if (mJointMaxSpeeds != jointPhysics.mJointMaxSpeeds) {
		return false;
	}

	if (mJointRollEnabled != jointPhysics.mJointRollEnabled) {
		return false;
	}

	if (mJointYawEnabled != jointPhysics.mJointYawEnabled) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}
	return true;
}
