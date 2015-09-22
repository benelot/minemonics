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
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/ogre3D/Euler.hpp>

ServoMotor::ServoMotor() :
	Motor(SERVO_MOTOR), mJointMotorIndex(JointPhysics::RDOF_PITCH), mMotorBt(
		NULL), mLowerLimit(0), mUpperLimit(0) {
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
//TODO: Print to logger only
//		std::cout << std::setw(10) << std::right << mMotorBt << "("
//				<< timeSinceLastTick << ")::Input Value:   " << getInputValue()
//				<< "\t/MotorPosition(error):  " << std::setw(10) << std::right
//				<< mMotorBt->m_currentPosition << "/" << std::setw(10)
//				<< std::right << targetAngle << "/" << std::setw(10)
//				<< std::right << angleError << "\t/targetVelocity: "
//				<< mMotorBt->m_targetVelocity << std::endl;
//}
}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
