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
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/ogre3D/Euler.hpp>

BoostLogger ServoMotor::mBoostLogger; /*<! initialize the boost logger*/
ServoMotor::_Init ServoMotor::_initializer;
ServoMotor::ServoMotor() :
	Motor(SERVO_MOTOR), mJointMotorIndex(JointPhysics::RDOF_PITCH), mMotorBt(
	NULL), mLowerLimit(0), mUpperLimit(0), mJointIndex(0) {
}

ServoMotor::ServoMotor(const ServoMotor& servoMotor) :
	Motor(SERVO_MOTOR) {
	mEnabled = servoMotor.mEnabled;
	mIndex = servoMotor.mIndex;
	mJointMotorIndex = servoMotor.mJointMotorIndex;
	mMaxForce = servoMotor.mMaxForce;
	mMotorType = servoMotor.mMotorType;
	mPositionControlled = servoMotor.mPositionControlled;
	mLowerLimit = servoMotor.mLowerLimit;
	mUpperLimit = servoMotor.mUpperLimit;
	mMotorBt = servoMotor.mMotorBt;
	mJointIndex = servoMotor.mJointIndex;
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = JointPhysics::RDOF_PITCH;
	mMotorBt = NULL;
}

void ServoMotor::initialize(
	const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
	MOTOR_TYPE* const motorBt, const double maxForce, double lowerLimit,
	double upperLimit) {

	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;

#ifndef EXCLUDE_FROM_TEST
	mMotorBt = motorBt;

#ifdef USE_6DOF2
	constraint->enableMotor(mJointMotorIndex, true);
	constraint->setTargetVelocity(mJointMotorIndex, maxSpeed);
	constraint->setMaxMotorForce(mJointMotorIndex, mMaxForce);
	constraint->setServo(mJointMotorIndex, true);
#else
	mMotorBt->m_enableMotor = true;
	mMotorBt->m_maxMotorForce = mMaxForce;
	//servo motor is not implemented in 6dofspring constraint
#endif
#endif

}

void ServoMotor::apply(double timeSinceLastTick) {

	//clamp the input value to [0;1] because otherwise the motor does not work anymore.
	btScalar clampedInputValue =
		(getInputValue() > 1.0f) ? 1.0f :
		(getInputValue() < 0.0f) ? 0.0f : getInputValue();

	//calculate the target angle of the motor
	btScalar targetAngle = mLowerLimit
		+ clampedInputValue * (mUpperLimit - mLowerLimit);
	//calculate the angle error
	btScalar angleError = targetAngle - mMotorBt->m_currentPosition;

#ifdef USE_6DOF2
//		mMotorBt->m_targetVelocity =
//		(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
//		(500.f * angleError < -mMaxSpeed) ? -mMaxSpeed : 500.f * angleError;
	mConstraint->setServoTarget(mJointMotorIndex, targetAngle);
#else

	float kP = 500.0f;
	float mMaxSpeed = 10000.0f;
	//simple p(roportional) controller
	//calculate the target velocity and clamp it with the maximum speed
	mMotorBt->m_targetVelocity =
		(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
		(500.f * angleError < -mMaxSpeed) ? -mMaxSpeed : kP * angleError;
#endif
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << mMotorBt << "("
	<< timeSinceLastTick << ")::Input Value:   " << getInputValue()
	<< "\t/MotorPosition(error):  "
	<< mMotorBt->m_currentPosition << "/" << targetAngle << "/" << angleError << "\t/targetVelocity: "
	<< mMotorBt->m_targetVelocity;
}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
