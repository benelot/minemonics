//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp>

#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
//## view headers
//## utils headers

JointVelocityceptor::JointVelocityceptor() :
	mVelocity(0) {
}

JointVelocityceptor::JointVelocityceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointModel, rotationalDOF), mVelocity(0) {

}

JointVelocityceptor::~JointVelocityceptor() {

}

void JointVelocityceptor::initialize() {
	JointProprioceptor::initialize();
}

void JointVelocityceptor::update(double timeSinceLastTick) {
	setVelocity(mJoint->getJointVel(mMotorIndex));
}
