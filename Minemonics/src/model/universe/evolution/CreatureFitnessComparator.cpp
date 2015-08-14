//# corresponding header
#include <model/universe/evolution/CreatureFitnessComparator.hpp>

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

int CreatureFitnessComparator::mCriterium = 0;
CreatureFitnessComparator::CreatureFitnessComparator(int criterium){
	mCriterium = criterium;
}

CreatureFitnessComparator::~CreatureFitnessComparator() {
	// TODO Auto-generated destructor stub
}

