/*
 * SineController.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 *
 *      This controller returns nothing else than a sine wave output to control a joint position or torque.
 */

//# corresponding headers
#include <model/evolution/population/creature/phenome/controller/sine/SineController.hpp>

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
		Controller(SINE_CONTROLLER), mAmplitude(0), mFrequency(0), mShift(0), mTime(
				0) {
}

SineController::~SineController() {
}

void SineController::initialize(double amplitude, double frequency,
		double shift) {
	mAmplitude = amplitude;
	mFrequency = frequency;
}

void SineController::perform(double time) {
	double input = 0;
	if (mControlInputs.size() != 0) {
		std::cout << "Why is there sine control input?";
		//input = mControlInput->getControlInput();
	} else {
		input = time;
	}
	double output = mAmplitude * sin(mFrequency * input);

	// distribute the output to the adjacent controllers or endpoints
	distributeOutput(output);
}

void SineController::collectInputs()
{
	//TODO::keep the inputs as they are
}
