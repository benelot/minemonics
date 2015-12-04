//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>

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

Controller::Controller(ControllerType controllerType) :
	mType(controllerType) {

}

Controller::~Controller() {
}

void Controller::distributeOutput(const double output) {
	for (std::vector<ControlInput*>::iterator controlOutputIterator =
		mControlOutputs.begin(); controlOutputIterator != mControlOutputs.end();
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

void Controller::setControlInputs(std::vector<ControlOutput*> controlInputs) {
	for(std::vector<int>::iterator iit = mControlInputIndices.begin();iit != mControlInputIndices.end();iit++){
		addControlInput(controlInputs[*iit]);
	}
}

void Controller::setControlOutputs(std::vector<ControlInput*> controlOutputs) {
	for(std::vector<int>::iterator iit = mControlOutputIndices.begin();iit != mControlOutputIndices.end();iit++){
		addControlOutput(controlOutputs[*iit]);
	}
}

void Controller::storeControlIndices() {
	mControlInputIndices.clear();
	for(std::vector<ControlInput*>::iterator cit = mControlOutputs.begin();cit != mControlOutputs.end();cit++){
		mControlOutputIndices.push_back((*cit)->getOwnControlInputIndex());
	}

	mControlOutputIndices.clear();
	for(std::vector<ControlOutput*>::iterator cit = mControlInputs.begin();cit != mControlInputs.end();cit++){
		mControlInputIndices.push_back((*cit)->getOwnControlOutputIndex());
	}
}

bool Controller::equals(const Controller& controller) const {
	if (mType != controller.mType) {
		return false;
	}

	/**The vector of control inputs.*/
	if (mControlInputs.size() != controller.mControlInputs.size()) {
		return false;
	}
	std::vector<ControlOutput*>::const_iterator it1 = mControlInputs.begin();
	std::vector<ControlOutput*>::const_iterator it2 =
		controller.mControlInputs.begin();
	for (; it1 != mControlInputs.end(), it2 != controller.mControlInputs.end();
		it1++, it2++) {
		if (!(*it1)->equals(**(it2))) {
			return false;
		}
	}

	/**The vector of control outputs.*/
	if (mControlOutputs.size() != controller.mControlOutputs.size()) {
		return false;
	}
	std::vector<ControlInput*>::const_iterator it3 = mControlOutputs.begin();
	std::vector<ControlInput*>::const_iterator it4 =
		controller.mControlOutputs.begin();
	for (;
		it3 != mControlOutputs.end(), it4 != controller.mControlOutputs.end();
		it3++, it4++) {
		if (!(*it3)->equals(**(it4))) {
			return false;
		}
	}

	return true;
}
