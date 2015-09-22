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
mJointIndex(0), mMotorIndex(FSJointPhysics::RDOF_PITCH) {
}

JointProprioceptor::JointProprioceptor(std::vector<int*>::size_type jointIndex,
FSJointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
mJointIndex(jointIndex), mMotorIndex(rotationalDOF) {
}

JointProprioceptor::~JointProprioceptor() {
}
