//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <iomanip>
#include <string>

//## controller headers
//## model headers
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//## utils headers

ServoMotor::ServoMotor() :
		Motor(SERVO_MOTOR), mJointMotorIndex(-1), mMotorBt(NULL), mConstraint(
		NULL) {
}

ServoMotor::ServoMotor(const ServoMotor& servoMotor) :
		Motor(SERVO_MOTOR) {
	mEnabled = servoMotor.mEnabled;
	mIndex = servoMotor.mIndex;
	mJointMotorIndex = servoMotor.mJointMotorIndex;
	mMaxForce = servoMotor.mMaxForce;
	mMaxSpeed = servoMotor.mMaxSpeed;
	mConstraint = servoMotor.mConstraint;
	mMotorBt = servoMotor.mMotorBt;
	mMotorType = servoMotor.mMotorType;
	mPositionControlled = servoMotor.mPositionControlled;
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = -1;
	mMotorBt = NULL;
}

void ServoMotor::initialize(const int jointMotorIndex,
CONSTRAINT_TYPE* constraint,
MOTOR_TYPE* const motorBt, const double maxForce, const double maxSpeed) {
	mJointMotorIndex = jointMotorIndex;
	mConstraint = constraint;
	mMotorBt = motorBt;
	mMaxForce = maxForce;
	mMaxSpeed = maxSpeed;

#ifdef USE_6DOF2
	constraint->enableMotor(mJointMotorIndex, true);
	constraint->setTargetVelocity(mJointMotorIndex, maxSpeed);
	constraint->setMaxMotorForce(mJointMotorIndex, mMaxForce);
	constraint->setServo(mJointMotorIndex, true);
#else
	mMotorBt->m_enableMotor = true;
	mMotorBt->m_targetVelocity = maxSpeed;
	mMotorBt->m_maxMotorForce = mMaxForce;
	//servo motor is not implemented in 6dofspring constraint
#endif

}

void ServoMotor::apply(double timeSinceLastTick) {
	if (mMotorBt->m_hiLimit - mMotorBt->m_loLimit != 0) {
//		mMotorBt->m_enableMotor = mEnabled;
		//clamp the input value to [0;1] because otherwise the motor does not work anymore.
		btScalar clampedInputValue =
				(getInputValue() > 1.0f) ? 1.0f :
				(getInputValue() < 0.0f) ? 0.0f : getInputValue();

		//calculate the target angle of the motor
		btScalar targetAngle = mMotorBt->m_loLimit
				+ clampedInputValue
						* (mMotorBt->m_hiLimit - mMotorBt->m_loLimit);

		//calculate the angle error
		btScalar angleError = targetAngle - mMotorBt->m_currentPosition;

#ifdef USE_6DOF2
//		mMotorBt->m_targetVelocity =
//		(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
//		(500.f * angleError < -mMaxSpeed) ? -mMaxSpeed : 500.f * angleError;
		mConstraint->setServoTarget(mJointMotorIndex, targetAngle);
#else
		//simple p(roportional) controller
		//calculate the target velocity and clamp it with the maximum speed
		mMotorBt->m_targetVelocity =
		(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
		(500.f * angleError < -mMaxSpeed) ? -mMaxSpeed : 500.f * angleError;
#endif
//TODO: Print to logger only
//		std::cout << std::setw(10) << std::right << mMotorBt << "("
//				<< timeSinceLastTick << ")::Input Value:   " << getInputValue()
//				<< "\t/MotorPosition(error):  " << std::setw(10) << std::right
//				<< mMotorBt->m_currentPosition << "/" << std::setw(10)
//				<< std::right << targetAngle << "/" << std::setw(10)
//				<< std::right << angleError << "\t/targetVelocity: "
//				<< mMotorBt->m_targetVelocity << std::endl;
	}
}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
