//# corresponding header
#include <model/universe/evolution/CreatureFitnessScoreComparator.hpp>

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

bool CreatureFitnessScoreComparator::mHigherIsBetter = true;
CreatureFitnessScoreComparator::CreatureFitnessScoreComparator(
		bool higherIsBetter) {
	mHigherIsBetter = higherIsBetter;
}

CreatureFitnessScoreComparator::~CreatureFitnessScoreComparator() {
}

