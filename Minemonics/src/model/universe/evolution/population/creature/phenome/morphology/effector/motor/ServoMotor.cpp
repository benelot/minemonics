//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
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

ServoMotor::ServoMotor(const ServoMotor& servoMotor) :
		Motor(SERVO_MOTOR) {
	mEnabled = servoMotor.mEnabled;
	mIndex = servoMotor.mIndex;
	mJointMotorIndex = servoMotor.mJointMotorIndex;
	mMaxForce = servoMotor.mMaxForce;
	mMaxSpeed = servoMotor.mMaxSpeed;
	mMotorBt = servoMotor.mMotorBt;
	mMotorType = servoMotor.mMotorType;
	mPositionControlled = servoMotor.mPositionControlled;
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = -1;
	mMotorBt = NULL;
}

void ServoMotor::initialize(const int jointMotorIndex,
		btRotationalLimitMotor* const motorBt, const double maxForce,
		const double maxSpeed) {
	mJointMotorIndex = jointMotorIndex;
	mMotorBt = motorBt;
	mMaxForce = maxForce;
	mMaxSpeed = maxSpeed;
	mMotorBt->m_maxMotorForce = mMaxForce;
	//TODO:: Check if this is the right velocity (it is not)
	//mMotorBt->m_targetVelocity = mMaxSpeed;
}

void ServoMotor::apply() {
	mMotorBt->m_enableMotor = true;
	mMotorBt->m_maxMotorForce = 1000000000.0f;
	btScalar targetLimitAngle = mMotorBt->m_loLimit
			+ getInputValue() * (mMotorBt->m_hiLimit - mMotorBt->m_loLimit);
	btScalar angleError = targetLimitAngle - mMotorBt->m_currentPosition;
	mMotorBt->m_targetVelocity = 1000000.f * angleError;
	std::cout << mMotorBt << "::Input Value:   " << getInputValue() << "\t/MotorPosition:  "
			<< mMotorBt->m_currentPosition << "\t/AngleError: " << angleError
			<< std::endl;
}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
