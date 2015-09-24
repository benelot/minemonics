//# corresponding header
#include <model/universe/evolution/population/creature/FScreature/phenome/morphology/effector/motor/FSServoMotor.hpp>
#include <configuration/Definitions.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <iomanip>
#include <string>

//## controller headers
//## model headers
#include <BulletDynamics/Featherstone/btMultiBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointMotor.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/ogre3D/Euler.hpp>

FSServoMotor::FSServoMotor() :
	mJointIndex(0), mMultiBody(NULL) {
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
	mMultiBody = servoMotor.mMultiBody;
}

FSServoMotor::~FSServoMotor() {
	mJointMotorIndex = JointPhysics::RDOF_PITCH;
}

void FSServoMotor::initialize(
	const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
	const double maxForce, double lowerLimit, double upperLimit) {

	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;
}

void FSServoMotor::instantiate(btMultiBody* multiBody, const int jointIndex) {
	mMultiBody = multiBody;
	mJointIndex = jointIndex;
}

void FSServoMotor::apply(double timeSinceLastTick) {

	//clamp the input value to [0;1] because otherwise the motor does not work anymore.
	btScalar clampedInputValue =
		(getInputValue() > 1.0f) ? 1.0f :
		(getInputValue() < 0.0f) ? 0.0f : getInputValue();

	//calculate the target angle of the motor
	btScalar targetAngle = mLowerLimit
		+ clampedInputValue * (mUpperLimit - mLowerLimit);

	//calculate the angle error
	btScalar angleError = targetAngle - mMultiBody->getJointPos(mJointIndex);

	float kP = 10000000;
	//simple p(roportional) controller
	//calculate the target force and clamp it with the maximum force
	mMultiBody->addJointTorque(mJointIndex,
		btScalar(
			(kP * angleError > mMaxForce) ? mMaxForce :
			(kP * angleError < -mMaxForce) ? -mMaxForce : kP * angleError));
}

FSServoMotor* FSServoMotor::clone() {
	return new FSServoMotor(*this);
}
