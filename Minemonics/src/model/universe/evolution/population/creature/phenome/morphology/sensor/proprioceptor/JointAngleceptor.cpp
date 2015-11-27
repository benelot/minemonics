//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//## view headers
//## utils headers

JointAngleceptor::JointAngleceptor() :
	mAngle(0) {
}

JointAngleceptor::JointAngleceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointModel, rotationalDOF), mAngle(0) {

}

JointAngleceptor::~JointAngleceptor() {

}

void JointAngleceptor::initialize() {
	JointProprioceptor::initialize();
}

void JointAngleceptor::update(double timeSinceLastTick) {
	setAngle(mJoint->getJointPos(mMotorIndex));
}
