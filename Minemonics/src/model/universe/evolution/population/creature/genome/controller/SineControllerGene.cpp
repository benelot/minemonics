//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>

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
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

SineControllerGene::SineControllerGene() :
	mXOffset(0), mYOffset(0), mAmplitude(0), mFrequency(0), ControllerGene(
		ControllerGene::SineControllerGene) {
}

SineControllerGene::SineControllerGene(const SineControllerGene& gene){
	mXOffset = gene.mXOffset;
	mYOffset = gene.mYOffset;
	mAmplitude = gene.mAmplitude;
	mFrequency = gene.mFrequency;
}

SineControllerGene::~SineControllerGene() {
}

void SineControllerGene::initialize() {

	mXOffset = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::JOINT_MIN_X_OFFSET,
		ControlConfiguration::JOINT_MAX_X_OFFSET);

	mYOffset = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::JOINT_MIN_Y_OFFSET,
		ControlConfiguration::JOINT_MAX_Y_OFFSET);
	mAmplitude = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::JOINT_MIN_AMPLITUDE,
		ControlConfiguration::JOINT_MAX_AMPLITUDE);
	mFrequency = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::JOINT_MIN_FREQUENCY,
		ControlConfiguration::JOINT_MAX_FREQUENCY);
}

bool SineControllerGene::equals(
	const SineControllerGene& sineControllerGene) const {

	if (!ControllerGene::equals((ControllerGene&) sineControllerGene)) {
		return false;
	}

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
	return new SineControllerGene(this);
}
