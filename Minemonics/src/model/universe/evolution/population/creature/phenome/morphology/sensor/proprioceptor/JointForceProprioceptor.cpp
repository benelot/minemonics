//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceProprioceptor.hpp>

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

JointForceProprioceptor::JointForceProprioceptor(CONSTRAINT_TYPE* g6DofJoint,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
		JointProprioceptor(g6DofJoint, rotationalDOF), mForce(0) {

}

JointForceProprioceptor::~JointForceProprioceptor() {
}

void JointForceProprioceptor::update(double timeSinceLastTick) {
	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
	//TODO: This is not the correct force, but only the maximum force
	//http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=10759
	setForce(motor->m_maxMotorForce);
}
