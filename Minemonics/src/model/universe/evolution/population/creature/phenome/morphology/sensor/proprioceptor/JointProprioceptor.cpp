//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

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

JointProprioceptor::JointProprioceptor() :
	mJoint(NULL), mMotorIndex(JointPhysics::RDOF_PITCH) {
}

JointProprioceptor::JointProprioceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	mMotorIndex(rotationalDOF), mJoint(jointModel) {
}

JointProprioceptor::~JointProprioceptor() {
}

void JointProprioceptor::initialize() {

}
