//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.hpp>

#include <iostream>
#include <iomanip>
#include <string>

//## controller headers
//## model headers
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h>
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/ogre3D/Euler.hpp>

BoostLogger SRBServoMotor::mBoostLogger; /*<! initialize the boost logger*/
SRBServoMotor::_Init SRBServoMotor::_initializer;
SRBServoMotor::SRBServoMotor() :
	mMotorBt(NULL), mLastPosition(0) {
}

SRBServoMotor::SRBServoMotor(
	const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
	const double maxForce, double lowerLimit, double upperLimit) :
	mMotorBt(NULL), mLastPosition(0) {
	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;
}

SRBServoMotor::SRBServoMotor(const SRBServoMotor& SRBServoMotor) {
	mEnabled = SRBServoMotor.mEnabled;
	mIndex = SRBServoMotor.mIndex;
	mJointMotorIndex = SRBServoMotor.mJointMotorIndex;
	mMaxForce = SRBServoMotor.mMaxForce;
	mMotorType = SRBServoMotor.mMotorType;
	mPositionControlled = SRBServoMotor.mPositionControlled;
	mLowerLimit = SRBServoMotor.mLowerLimit;
	mUpperLimit = SRBServoMotor.mUpperLimit;
	mMotorBt = SRBServoMotor.mMotorBt;
	mLastPosition = SRBServoMotor.mLastPosition;
}

SRBServoMotor::~SRBServoMotor() {
	mJointMotorIndex = JointPhysics::RDOF_PITCH;
	mMotorBt = NULL;
}

void SRBServoMotor::initialize(MOTOR_TYPE* const motorBt) {

	mMotorBt = motorBt;

	if (mMotorBt) {
		mMotorBt->m_hiLimit = mUpperLimit;
		mMotorBt->m_loLimit = mLowerLimit;
		mLastPosition = mMotorBt->m_currentPosition;
	}

//#ifdef USE_6DOF2
//	constraint->enableMotor(mJointMotorIndex, true);
//	constraint->setTargetVelocity(mJointMotorIndex, 0);
//	constraint->setMaxMotorForce(mJointMotorIndex, mMaxForce);
//	constraint->setServo(mJointMotorIndex, true);
//#else
//	if (mMotorBt) {
//	mMotorBt->m_enableMotor = true;
//	mMotorBt->m_maxMotorForce = 0;
//	//servo motor is not implemented in 6dofspring constraint
//#endif



}

void SRBServoMotor::instantiate(JointPhysics* jointPhysics,
	const int jointIndex) {
	mJoint = jointPhysics;
	mJointIndex = jointIndex;
}

void SRBServoMotor::apply(double timeSinceLastTick) {

	//clamp the input value to [0;1] because otherwise the motor does not work anymore.
	btScalar clampedInputValue =
		(getInputValue() > 1.0f) ? 1.0f :
		(getInputValue() < 0.0f) ? 0.0f : getInputValue();

	//calculate the target angle of the motor
	btScalar targetAngle = mLowerLimit
		+ clampedInputValue * (mUpperLimit - mLowerLimit);
	//calculate the angle error
	btScalar angleError = targetAngle - mMotorBt->m_currentPosition;
	btScalar velocityError = 0 - mLastPosition + mMotorBt->m_currentPosition;
	mLastPosition = mMotorBt->m_currentPosition;

#ifdef USE_6DOF2
	mConstraint->setServoTarget(mJointMotorIndex, targetAngle);
#else

	//simple p(roportional) controller
	//calculate the target force and clamp it with the maximum force
	float kP = 200000000;
	float kD = 2000;
	double correction = kP * angleError + kD * velocityError;
	mJoint->applyJointTorque(0,
		btScalar(
			(correction > mMaxForce) ? mMaxForce :
			(correction < -mMaxForce) ? -mMaxForce : correction));

#endif
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< mMotorBt->m_currentPosition << "," << targetAngle;
}

SRBServoMotor* SRBServoMotor::clone() {
	return new SRBServoMotor(*this);
}
