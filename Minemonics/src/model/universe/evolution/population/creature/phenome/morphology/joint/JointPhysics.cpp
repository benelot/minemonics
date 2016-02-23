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
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointUpperLimits(
		0, 0, 0), mJointMaxForces(0, 0, 0), mJointLowerLimits(0, 0, 0), mJointPitchAxis(
		1, 0, 0), mJointYawAxis(0, 0, 1), mJointIndex(0), mLimbMassForceScalar(
		0),mInitialPosition(0),mInitialVelocity(0) {
}

JointPhysics::~JointPhysics() {
	//delete and clear the motor vector
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		delete (*motorIterator);
	}

	mMotors.clear();
}

void JointPhysics::storeControlIndices() {
	//TODO: Implement when needed
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

	//Double comparison
	if (mJointLowerLimits != jointPhysics.mJointLowerLimits) {
		return false;
	}
	//Double comparison
	if (mJointUpperLimits != jointPhysics.mJointUpperLimits) {
		return false;
	}

	if (mJointMaxForces != jointPhysics.mJointMaxForces) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}
	return true;
}

void JointPhysics::setControlInputs(std::vector<ControlOutput*> controlInputs) {
	//TODO: Implement when needed
}

void JointPhysics::setControlOutputs(
	std::vector<ControlInput*> controlOutputs) {
	//TODO: Implement when needed
}
