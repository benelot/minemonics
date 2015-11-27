//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>

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

JointForceceptor::JointForceceptor() :
	mForce(0) {
}

JointForceceptor::JointForceceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointModel, rotationalDOF), mForce(0) {

}

JointForceceptor::~JointForceceptor() {
}

void JointForceceptor::initialize() {
	JointProprioceptor::initialize();
}

void JointForceceptor::update(double timeSinceLastTick) {
	//TODO: Add getForce
//	setForce(mJoint->getForce(mMotorIndex));
}
