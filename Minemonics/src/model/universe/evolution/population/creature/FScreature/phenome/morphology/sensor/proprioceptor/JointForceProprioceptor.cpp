//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>

//## view headers
//## utils headers

JointForceProprioceptor::JointForceProprioceptor(std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
		FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
		JointProprioceptor(jointIndex, rotationalDOF), mForce(0) {

}

JointForceProprioceptor::~JointForceProprioceptor() {
}

void JointForceProprioceptor::update(double timeSinceLastTick) {
//	MOTOR_TYPE* motor = mG6DofJoint->getRotationalLimitMotor(mMotorIndex);
	//TODO: This is not the correct force, but only the maximum force
	//http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?f=9&t=10759
//	setForce(motor->m_maxMotorForce);
}
