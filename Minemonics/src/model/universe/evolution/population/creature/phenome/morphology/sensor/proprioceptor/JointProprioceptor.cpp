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

JointProprioceptor::JointProprioceptor(CONSTRAINT_TYPE* g6DofJoint,
		JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
		mG6DofJoint(g6DofJoint), mMotorIndex(rotationalDOF) {
}

JointProprioceptor::~JointProprioceptor() {
	mG6DofJoint = NULL;
}
