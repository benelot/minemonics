/*
 * ServoMotor.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

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
	// TODO Auto-generated destructor stub
}

ServoMotor::~ServoMotor() {
	// TODO Auto-generated constructor stub
}

void ServoMotor::initialize(int jointMotorIndex,
		btRotationalLimitMotor* motorBt) {
	mJointMotorIndex = jointMotorIndex;
	mMotorBt = motorBt;
}
