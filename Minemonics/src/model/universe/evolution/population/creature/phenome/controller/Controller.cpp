//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>

//# forward declarations
//# system headers
#include <vector>

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

Controller::Controller(ControllerType controllerType) :
		mType(controllerType) {

}

Controller::~Controller() {
}

void Controller::distributeOutput(const double output) {
	std::vector<ControlInput*>::iterator controlOutputIterator =
			mControlOutputs.begin();
	for (; controlOutputIterator != mControlOutputs.end();
			controlOutputIterator++) {
		(*controlOutputIterator)->setInputValue(output);
	}
}

void Controller::addControlInput(ControlOutput* const controlOutput) {
	mControlInputs.push_back(controlOutput);
}

void Controller::addControlOutput(ControlInput* const controlInput) {
	mControlOutputs.push_back(controlInput);
}

bool Controller::equals(const Controller& controller) const {
	if (mType != controller.mType) {
		return false;
	}

	/**The vector of control inputs.*/
	std::vector<ControlOutput*>::const_iterator it1 = mControlInputs.begin();
	std::vector<ControlOutput*>::const_iterator it2 =
			controller.mControlInputs.begin();
	for (; it1 != mControlInputs.end(), it2 != controller.mControlInputs.end();
			it1++, it2++) {
		if (!(*it1)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of joint models.*/
	std::vector<ControlInput*>::const_iterator it3 = mControlOutputs.begin();
	std::vector<ControlInput*>::const_iterator it4 =
			controller.mControlOutputs.begin();
	for (;
			it3 != mControlOutputs.end(), it4
					!= controller.mControlOutputs.end(); it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	return true;
}
