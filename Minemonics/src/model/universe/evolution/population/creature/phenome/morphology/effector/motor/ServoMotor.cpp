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
	mMotorBt->m_maxMotorForce = 10.0f;
}

void ServoMotor::apply() {

	//simple p(roportional) controller
	mMotorBt->m_enableMotor = mEnabled;

	//clamp the input value to [0;1] because otherwise the motor does not work anymore.
	btScalar clampedInputValue = (getInputValue() > 1) ? 1 :
									(getInputValue() < 0) ? 0 : getInputValue();

	//calculate the target angle of the motor
	btScalar targetAngle = mMotorBt->m_loLimit
			+ getInputValue() * (mMotorBt->m_hiLimit - mMotorBt->m_loLimit);

	//calculate the angle error
	btScalar angleError = targetAngle - mMotorBt->m_currentPosition;

	//calculate the target velocity and clamp it with the maximum speed
	mMotorBt->m_targetVelocity =
			(500.f * angleError > mMaxSpeed) ? mMaxSpeed :
			(500.f * angleError < -mMaxSpeed) ? -mMaxSpeed : 500.f * angleError;

	//print some values TODO: Print them to the logger only
	std::cout << mMotorBt << "::Input Value:   " << getInputValue()
			<< "\t/MotorPosition(error):  " << mMotorBt->m_currentPosition
			<< "/" << angleError << "\t/targetVelocity: "
			<< mMotorBt->m_targetVelocity << std::endl;
}

ServoMotor* ServoMotor::clone() {
	return new ServoMotor(*this);
}
