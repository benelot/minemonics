//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/ControlOutput.hpp>

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

ControlOutput::ControlOutput() :
		mValue(0) {
}

ControlOutput::~ControlOutput() {
}

bool ControlOutput::equals(const ControlOutput& controlOutput) const {
	if (mValue != controlOutput.mValue) {
		return false;
	}

	return true;
}
