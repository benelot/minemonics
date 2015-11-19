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
	NULL), mLowerLimit(0), mUpperLimit(0), mJointIndex(0), mJoint(NULL), mPositionControlled(
		true) {
}

ServoMotor::ServoMotor(
	const JointPhysics::RotationalDegreeOfFreedom jointMotorIndex,
	const double maxForce, double lowerLimit, double upperLimit) :
	Motor(Motor::SERVO_MOTOR), mPositionControlled(true) {

	mJointMotorIndex = jointMotorIndex;
	mMaxForce = maxForce;
	mLowerLimit = lowerLimit;
	mUpperLimit = upperLimit;

//#ifndef EXCLUDE_FROM_TEST
////	mMotorBt = motorBt;
//
////#ifdef USE_6DOF2
////	constraint->enableMotor(mJointMotorIndex, true);
////	constraint->setTargetVelocity(mJointMotorIndex, maxSpeed);
////	constraint->setMaxMotorForce(mJointMotorIndex, mMaxForce);
////	constraint->setServo(mJointMotorIndex, true);
////#else
////	mMotorBt->m_enableMotor = true;
////	mMotorBt->m_maxMotorForce = mMaxForce;
//	//servo motor is not implemented in 6dofspring constraint
//#endif
//#endif
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
	mJoint = servoMotor.mJoint;
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = JointPhysics::RDOF_PITCH;
	mMotorBt = NULL;
}

void ServoMotor::initialize() {

}
