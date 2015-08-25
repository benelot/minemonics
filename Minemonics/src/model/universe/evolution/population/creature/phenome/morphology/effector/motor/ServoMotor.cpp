//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <iomanip>
#include <string>

//## controller headers
//## model headers
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

ServoMotor::ServoMotor() :
		Motor(SERVO_MOTOR), mJointMotorIndex(JointPhysics::RDOF_PITCH), mJointMotor(
		NULL),mLowerLimit(0),mUpperLimit(0) {
}

ServoMotor::ServoMotor(const ServoMotor& servoMotor) :
		Motor(SERVO_MOTOR) {
	mEnabled = servoMotor.mEnabled;
	mIndex = servoMotor.mIndex;
	mJointMotorIndex = servoMotor.mJointMotorIndex;
	mMaxForce = servoMotor.mMaxForce;
	mMaxSpeed = servoMotor.mMaxSpeed;
	mMotorType = servoMotor.mMotorType;
	mPositionControlled = servoMotor.mPositionControlled;
	mJointMotor = servoMotor.mJointMotor;
	mLowerLimit = servoMotor.mLowerLimit;
	mUpperLimit = servoMotor.mUpperLimit;
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = JointPhysics::RDOF_PITCH;
}

void ServoMotor::initialize(
		const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
		const double maxForce, const double maxSpeed,double lowerLimit, double upperLimit) {
	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mMaxSpeed = maxSpeed;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;
}

void ServoMotor::apply(double timeSinceLastTick) {
//		mMotorBt->m_enableMotor = mEnabled;
	//clamp the input value to [0;1] because otherwise the motor does not work anymore.
	btScalar clampedInputValue =
			(getInputValue() > 1.0f) ? 1.0f :
			(getInputValue() < 0.0f) ? 0.0f : getInputValue();

	//calculate the target angle of the motor
	btScalar targetAngle = mLowerLimit
			+ clampedInputValue * (mUpperLimit - mLowerLimit);

	//calculate the angle error
	btScalar angleError = targetAngle - mJointMotor->getPosition(mJointMotorIndex);

	//simple p(roportional) controller
	//calculate the target velocity and clamp it with the maximum speed
	mJointMotor->setVelocityTarget(
			(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
			(500.f * angleError < -mMaxSpeed) ?
					-mMaxSpeed : 500.f * angleError);

//TODO: Print to logger only
//		std::cout << std::setw(10) << std::right << mMotorBt << "("
//				<< timeSinceLastTick << ")::Input Value:   " << getInputValue()
//				<< "\t/MotorPosition(error):  " << std::setw(10) << std::right
//				<< mMotorBt->m_currentPosition << "/" << std::setw(10)
//				<< std::right << targetAngle << "/" << std::setw(10)
//				<< std::right << angleError << "\t/targetVelocity: "
//				<< mMotorBt->m_targetVelocity << std::endl;

}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
