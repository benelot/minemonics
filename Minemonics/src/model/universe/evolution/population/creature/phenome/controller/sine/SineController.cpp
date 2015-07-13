//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
#include <cmath>
#include <iostream>
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

SineController::SineController() :
		Controller(SINE_CONTROLLER), mAmplitude(0.5f), mFrequency(1), mXShift(
				0), mYShift(1), mTime(0) {
}

SineController::~SineController() {
}

void SineController::initialize(const double amplitude,const double frequency,
		const double xShift,const double yShift) {
	mAmplitude = amplitude;
	mFrequency = frequency;
	mXShift = xShift;
	mYShift = yShift;
}

void SineController::perform(const double timeSinceLastFrame) {
	double input = 0;
	if (mControlInputs.size() != 0) {
		std::cout << "Why is there sine control input?";
		//input = mControlInput->getControlInput();
	} else {
		mTime += timeSinceLastFrame;
	}
	double output = mAmplitude * sin(mFrequency * mTime + mXShift) + mYShift;
	//clamp output to [0;1]
	output = (output > 1) ? 1 : (output < 0) ? 0 : output;

	// distribute the output to the adjacent controllers or endpoints
	distributeOutput(output);
}

SineController::SineController(const SineController& sineController) :
		Controller(SINE_CONTROLLER) {
	mAmplitude = sineController.mAmplitude;
	mFrequency = sineController.mFrequency;
	mTime = sineController.mTime;
	mType = sineController.mType;
	mXShift = sineController.mXShift;
	mYShift = sineController.mYShift;

	//TODO: How to clone control inputs/outputs
}

SineController* SineController::clone() {
	return new SineController(*this);
}

void SineController::collectInputs() {
	//TODO::keep the inputs as they are
}
