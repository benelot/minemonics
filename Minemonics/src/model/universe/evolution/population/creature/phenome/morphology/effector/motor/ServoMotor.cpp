//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
//## controller headers
//## model headers
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

ServoMotor::ServoMotor() :
		Motor(SERVO_MOTOR), mJointMotorIndex(-1), mMotorBt(NULL) {
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = -1;
	mMotorBt = 0;
}

void ServoMotor::initialize(int jointMotorIndex,
		btRotationalLimitMotor* motorBt, double maxForce, double maxSpeed) {
	mJointMotorIndex = jointMotorIndex;
	mMotorBt = motorBt;
	mMaxForce = maxForce;
	mMaxSpeed = maxSpeed;
	mMotorBt->m_maxMotorForce = mMaxForce;
	//TODO:: Check if this is the right velocity
	mMotorBt->m_targetVelocity = mMaxSpeed;
}

void ServoMotor::apply() {
	mMotorBt->m_currentPosition = mMotorBt->m_loLimit + getValue()*(mMotorBt->m_hiLimit-mMotorBt->m_loLimit);
}
