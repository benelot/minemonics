//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/proprioceptor/JointProprioceptor.hpp>

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

JointProprioceptor::JointProprioceptor(
	std::vector<CONSTRAINT_TYPE*>::size_type jointIndex,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	mJointIndex(jointIndex), mMotorIndex(rotationalDOF), mJoint(NULL) {
}

JointProprioceptor::~JointProprioceptor() {
}
