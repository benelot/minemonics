/*
 * SineControllerGene.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <boost/math/constants/constants.hpp>
#include <configuration/ControlConfiguration.hpp>
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>
#include <utils/Randomness.hpp>

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

