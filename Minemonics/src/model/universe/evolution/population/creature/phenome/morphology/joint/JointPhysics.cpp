//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

JointPhysics::JointPhysics() :
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointPitchEnabled(
		true), mJointRollEnabled(true), mJointYawEnabled(true), mJointMaxAngle(
		0, 0, 0), mJointMaxForces(0, 0, 0), mJointMaxSpeeds(0, 0, 0), mJointMinAngle(
		0, 0, 0), mJointPitchAxis(1, 0, 0),mJointIndex(0) {
}

JointPhysics::~JointPhysics() {
	//delete and clear the motor vector
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		delete (*motorIterator);
	}

	mMotors.clear();
}

bool JointPhysics::equals(const JointPhysics& jointPhysics) const {
	if (mInWorld != jointPhysics.mInWorld) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}

	//Double comparison
	if (mJointPitchAxis != jointPhysics.mJointPitchAxis) {
		return false;
	}

	if (mJointPitchEnabled != jointPhysics.mJointPitchEnabled) {
		return false;
	}
	//Double comparison
	if (mJointMinAngle != jointPhysics.mJointMinAngle) {
		return false;
	}
	//Double comparison
	if (mJointMaxAngle != jointPhysics.mJointMaxAngle) {
		return false;
	}

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
