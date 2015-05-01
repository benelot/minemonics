//# corresponding header
#include <model/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

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

ServoMotor::ServoMotor() :
		mJointMotorIndex(-1), mMotorBt(NULL) {
}

ServoMotor::~ServoMotor() {
	mJointMotorIndex = -1;
	mMotorBt = 0;
}

void ServoMotor::initialize(int jointMotorIndex,
		btRotationalLimitMotor* motorBt) {
	mJointMotorIndex = jointMotorIndex;
	mMotorBt = motorBt;
}
