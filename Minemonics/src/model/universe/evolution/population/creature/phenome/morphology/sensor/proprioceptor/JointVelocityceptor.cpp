//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp>

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

JointVelocityceptor::JointVelocityceptor() :
	mVelocity(0), mLastPosition(0) {
}

JointVelocityceptor::JointVelocityceptor(JointModel* jointModel,
	JointPhysics::RotationalDegreeOfFreedom rotationalDOF) :
	JointProprioceptor(jointModel, rotationalDOF), mVelocity(0), mLastPosition(
		0) {

}

JointVelocityceptor::~JointVelocityceptor() {

}

void JointVelocityceptor::initialize() {
	JointProprioceptor::initialize();
}

void JointVelocityceptor::update(double timeSinceLastTick) {
	setVelocity(
		mJoint->getJointVel(mMotorIndex, timeSinceLastTick, mLastPosition));
	mLastPosition = mJoint->getJointPos(mMotorIndex);
}
