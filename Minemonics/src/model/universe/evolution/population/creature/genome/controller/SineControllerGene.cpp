/*
 * SineControllerGene.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <configuration/ControlConfiguration.hpp>

//## model headers
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

SineControllerGene::SineControllerGene() :
		mXOffset(0), mYOffset(0), mAmplitude(0), mFrequency(0) {
	mControllerGeneType = ControllerGene::SineControllerGene;

}

SineControllerGene::~SineControllerGene() {
}

void SineControllerGene::initialize() {

	Randomness randomness;
	mXOffset = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());

	mYOffset = randomness.nextUnifDouble(-1, 1);
	mAmplitude = randomness.nextUnifDouble(0,
			ControlConfiguration::CPG_SINE_INITIAL_MAX_AMPLITUDE);
	mFrequency = randomness.nextUnifDouble(0,
			ControlConfiguration::CPG_SINE_INITIAL_MAX_FREQUENCY);
}

bool SineControllerGene::equals(
		const SineControllerGene& sineControllerGene) const {

	ControllerGene::equals((ControllerGene&) sineControllerGene);

	if (mXOffset != sineControllerGene.mXOffset)
		return false;

	if (mYOffset != sineControllerGene.mYOffset)
		return false;

	if (mAmplitude != sineControllerGene.mAmplitude)
		return false;

	if (mFrequency != sineControllerGene.mFrequency)
		return false;

	return true;
}

SineControllerGene* SineControllerGene::clone() {
	SineControllerGene* sineControllerGene = new SineControllerGene();
	sineControllerGene->setControllerGeneType(mControllerGeneType);
	sineControllerGene->setFrequency(mFrequency);
	sineControllerGene->setAmplitude(mAmplitude);
	sineControllerGene->setXOffset(mXOffset);
	sineControllerGene->setYOffset(mYOffset);

	return sineControllerGene;
}
