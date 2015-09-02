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
		mEndingAtFitness(0), mFitnessEnabled(false), mGenerationsEnabled(false), mLastingGenerations(
				0), mCurrentFitness(0), mLastingGenerationsLimit(0) {
}

Epoch::~Epoch() {
	
}

bool Epoch::isEndOfEpoch() {
	if (mGenerationsEnabled && isLastingGenerationsReached()) {
		return true;
	}

	if (mFitnessEnabled && isFitnessReached()) {
		return true;
	}
	return false;
}

