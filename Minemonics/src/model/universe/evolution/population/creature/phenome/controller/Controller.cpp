//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
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
		mControllerType(controllerType) {

}

Controller::~Controller() {
}


void Controller::distributeOutput(double output) {
	std::vector<ControlInput*>::iterator controlOutputIterator =
			mControlOutputs.begin();
	for (; controlOutputIterator != mControlOutputs.end();
			controlOutputIterator++) {
		(*controlOutputIterator)->setValue(output);
	}
}



void Controller::addControlInput(ControlOutput* controlOutput)
{
		mControlInputs.push_back(controlOutput);
}

void Controller::addControlOutput(ControlInput* controlInput)
{
		mControlOutputs.push_back(controlInput);
}
