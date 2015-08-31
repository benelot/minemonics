//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

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

JointPhysics::JointPhysics() :
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointPitchAxisX(1), mJointPitchAxisY(
		0), mJointPitchAxisZ(0), mJointPitchEnabled(true), mJointPitchMaxAngle(
		0), mJointPitchMinAngle(0), mJointRollEnabled(true), mJointRollMaxAngle(
		0), mJointRollMinAngle(0), mJointYawEnabled(true), mJointYawMaxAngle(0), mJointYawMinAngle(
		0) {
}

JointPhysics::~JointPhysics() {
}

