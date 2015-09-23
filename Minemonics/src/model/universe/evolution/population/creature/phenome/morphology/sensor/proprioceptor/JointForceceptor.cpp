//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/effector/motor/SRBServoMotor.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>

//## view headers
//## utils headers

JointForceceptor::JointForceceptor(
	std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointIndex, rotationalDOF), mForce(0) {

}

JointForceceptor::~JointForceceptor() {
}

void JointForceceptor::update(double timeSinceLastTick) {
//	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
	//TODO: This is not the correct force, but only the maximum force
	//http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=10759
//	setForce(motor->m_maxMotorForce);
}
