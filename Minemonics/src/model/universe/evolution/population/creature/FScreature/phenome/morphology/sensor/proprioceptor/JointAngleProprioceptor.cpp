//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>

//## view headers
//## utils headers

JointAngleProprioceptor::JointAngleProprioceptor(std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
		FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
		JointProprioceptor(jointIndex, rotationalDOF), mAngle(0) {

}

JointAngleProprioceptor::~JointAngleProprioceptor() {

}

void JointAngleProprioceptor::update(double timeSinceLastTick) {
//	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
//	setAngle(
//			(motor->m_currentPosition
//					/ (motor->m_hiLimit - motor->m_loLimit)) * M_PI);
}
