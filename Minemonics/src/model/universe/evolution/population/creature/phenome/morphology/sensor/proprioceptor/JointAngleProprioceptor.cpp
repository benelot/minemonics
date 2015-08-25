//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleProprioceptor.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//## view headers
//## utils headers

JointAngleProprioceptor::JointAngleProprioceptor(std::vector<int*>::size_type jointIndex,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
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
