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

JointAngleProprioceptor::JointAngleProprioceptor(CONSTRAINT_TYPE* g6DofJoint,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
		JointProprioceptor(g6DofJoint, rotationalDOF), mAngle(0) {

}

JointAngleProprioceptor::~JointAngleProprioceptor() {

}

void JointAngleProprioceptor::update(double timeSinceLastTick) {
	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
	setAngle(
			(motor->m_currentPosition
					/ (motor->m_hiLimit - motor->m_loLimit)) * M_PI);
}
