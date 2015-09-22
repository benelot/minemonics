//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>

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
//## view headers
//## utils headers

JointAngleceptor::JointAngleceptor() :
mAngle(0) {
}

JointAngleceptor::JointAngleceptor(std::vector<int*>::size_type jointIndex,
FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
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
