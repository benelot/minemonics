//# corresponding header
#include <model/universe/Epoch.hpp>

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

Epoch::Epoch() :
	mEndingAtFitness(0), mFitnessEnabled(false), mGenerationsEnabled(false), mCurrentGeneration(
		0), mCurrentFitness(0), mEndingAtGeneration(0) {
}

Epoch::~Epoch() {

}

bool Epoch::isEndOfEpoch() {
	if (mGenerationsEnabled && isEndingGenerationReached()) {
		return true;
	}

	if (mFitnessEnabled && isFitnessReached()) {
		return true;
	}
	return false;
}

