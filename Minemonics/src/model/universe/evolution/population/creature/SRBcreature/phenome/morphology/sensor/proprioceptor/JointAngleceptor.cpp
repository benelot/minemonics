//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/effector/motor/SRBServoMotor.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>

//## view headers
//## utils headers

JointAngleceptor::JointAngleceptor(
	std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointIndex, rotationalDOF), mAngle(0) {

}

JointAngleceptor::~JointAngleceptor() {

}

void JointAngleceptor::update(double timeSinceLastTick) {
//	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
//	setAngle(
//			(motor->m_currentPosition
//					/ (motor->m_hiLimit - motor->m_loLimit)) * M_PI);
}
