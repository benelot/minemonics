//# corresponding headers
#include <model/universe/evolution/juries/Jury.hpp>

//# forward declarations
//# system headers
#include <limits>

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

Jury::Jury(JuryType juryType, bool higherIsBetter, int weight) :
		mJuryType(juryType), mFitness(
				(higherIsBetter) ?
						std::numeric_limits<double>::min() :
						std::numeric_limits<double>::max()), mWeight(weight), mHigherIsBetter(
				higherIsBetter), mScore(0) {
}

Jury::~Jury() {

}

/**
 * Returns the weight associated with this jury component.
 * @return the weight
 */
double Jury::getWeight() {
	return mWeight;
}

/**
 * Returns the fitness value that this jury assigns.
 * @return the fitness value
 */
double Jury::getFitness() {
	return mFitness;
}

Jury::JuryType Jury::getJuryType() {
	return mJuryType;
}

bool Jury::equals(const Jury& jury) const {
	if (mJuryType != jury.mJuryType) {
		return false;
	}

	if (mWeight != jury.mWeight) {
		return false;
	}

	if (mFitness != jury.mFitness) {
		return false;
	}

	return true;
}
