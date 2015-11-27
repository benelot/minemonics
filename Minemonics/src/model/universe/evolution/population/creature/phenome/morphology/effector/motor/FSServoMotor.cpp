//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/FSServoMotor.hpp>

//## controller headers
//## model headers
#include <LinearMath/btScalar.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>

//## view headers
//## utils headers

FSServoMotor::FSServoMotor() {
}

FSServoMotor::FSServoMotor(
	const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
	const double maxForce, double lowerLimit, double upperLimit,
	bool positionControlled) {
	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;
	mPositionControlled = positionControlled;
}

FSServoMotor::FSServoMotor(const FSServoMotor& servoMotor) {
	mEnabled = servoMotor.mEnabled;
	mIndex = servoMotor.mIndex;
	mJointIndex = servoMotor.mJointIndex;
	mJointMotorIndex = servoMotor.mJointMotorIndex;
	mMaxForce = servoMotor.mMaxForce;
	mMotorType = servoMotor.mMotorType;
	mPositionControlled = servoMotor.mPositionControlled;
	mLowerLimit = servoMotor.mLowerLimit;
	mUpperLimit = servoMotor.mUpperLimit;
	mJoint = servoMotor.mJoint;
}

FSServoMotor::~FSServoMotor() {
	mJoint = NULL;
}

void FSServoMotor::initialize() {

}

void FSServoMotor::instantiate(JointPhysics* jointPhysics,
	const int jointIndex) {
	mJoint = jointPhysics;
	mJointIndex = jointIndex;
}

void FSServoMotor::apply(double timeSinceLastTick) {

	if (mPositionControlled) {
		//clamp the input value to [0;1] because otherwise the motor does not work anymore.
		btScalar clampedInputValue =
			(getInputValue() > 1.0f) ? 1.0f :
			(getInputValue() < 0.0f) ? 0.0f : getInputValue();

		//calculate the target angle of the motor
		btScalar targetAngle = mLowerLimit
			+ clampedInputValue * (mUpperLimit - mLowerLimit);

		//calculate the angle error
		btScalar angleError = targetAngle - mJoint->getJointPos(0);
		btScalar velocityError = 0 - mJoint->getJointVel(0);

		//simple p(roportional) controller
		//calculate the target force and clamp it with the maximum force
		float kP = 200000000;
		float kD = 2000;
		double correction = kP * angleError + kD * velocityError;
		mJoint->applyJointTorque(mJointMotorIndex,
			btScalar(
				(correction > mMaxForce) ? mMaxForce :
				(correction < -mMaxForce) ? -mMaxForce : correction));
	} else {
		//clamp the input value to [0;1] because otherwise the motor does not work anymore.
		btScalar clampedInputValue =
			(getInputValue() > 1.0f) ? 1.0f :
			(getInputValue() < -1.0f) ? -1.0f : getInputValue();
		mJoint->applyJointTorque(0, btScalar(clampedInputValue*mMaxForce));
	}
}

FSServoMotor* FSServoMotor::clone() {
	return new FSServoMotor(*this);
}
