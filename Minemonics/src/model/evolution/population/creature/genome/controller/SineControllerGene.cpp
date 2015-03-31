/*
 * SineControllerGene.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "SineControllerGene.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/ControlConfiguration.h"

//## controller headers
//## model headers
//## view headers
//## utils headers
#include "utils/Randomness.h"

SineControllerGene::SineControllerGene() :
		mInitialValue(0), mAmplitude(0), mFrequency(0) {
	mControllerGeneType = ControllerGene::SineControllerGene;

}

SineControllerGene::~SineControllerGene() {
}

void SineControllerGene::initialize() {

	Randomness randomness;
	mInitialValue = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mAmplitude = randomness.nextDouble(0,
			ControlConfiguration::CPG_SINE_INITIAL_MAX_AMPLITUDE);
	mFrequency = randomness.nextDouble(0,
			ControlConfiguration::CPG_SINE_INITIAL_MAX_FREQUENCY);
}

bool SineControllerGene::equals(
		const SineControllerGene& sineControllerGene) const {

	ControllerGene::equals((ControllerGene&) sineControllerGene);

	if (mInitialValue != sineControllerGene.mInitialValue)
		return false;

	if (mAmplitude != sineControllerGene.mAmplitude)
		return false;

	if (mFrequency != sineControllerGene.mFrequency)
		return false;

	return true;
}

