//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlInput.hpp>

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

ControlInput::ControlInput() :
	mReceivedInput(false), mInputValue(0), mOwnInputIndex(0) {
}

ControlInput::ControlInput(int inputIndex) :
	mReceivedInput(false), mInputValue(0), mOwnInputIndex(inputIndex) {
}

ControlInput::~ControlInput() {
//	mReceivedInput
//	mInputValue
}

bool ControlInput::equals(const ControlInput& controlInput) const {
	if (mReceivedInput != controlInput.mReceivedInput) {
		return false;
	}

	if (mInputValue != controlInput.mInputValue) {
		return false;
	}

	return true;
}
