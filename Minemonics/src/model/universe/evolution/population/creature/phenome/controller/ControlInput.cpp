/*
 * ControlInput.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: leviathan
 */

#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>

ControlInput::ControlInput() :
		mReceivedInput(false), mValue(0) {
}

ControlInput::~ControlInput() {
//	mReceivedInput
//	mValue
}

bool ControlInput::equals(const ControlInput& controlInput) const {
	if (mReceivedInput != controlInput.mReceivedInput) {
		return false;
	}

	if (mValue != controlInput.mValue) {
		return false;
	}

	return true;
}
