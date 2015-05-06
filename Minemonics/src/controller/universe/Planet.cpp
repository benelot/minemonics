//# corresponding header
//# forward declarations
#ifndef NULL
#define NULL 0
#endif /*NULL*/

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

Planet::Planet() :
		mEnvironment(NULL), mEvolution(NULL) {
}

Planet::~Planet() {
	mEnvironment = NULL;
	mEvolution = NULL;
}

void Planet::initialize(Evolution* evolution, Environment* environment) {
	mEvolution = evolution;
	mEnvironment = environment;
}
