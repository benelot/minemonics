//# corresponding header
#include <controller/universe/Universe.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif /*NULL*/

//# system headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <model/universe/UniverseModel.hpp>

//## model headers
//## view headers
//## utils headers

Universe::Universe() {
}

Universe::~Universe() {
	//delete the planets
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		Planet* planet = (*pit);
		delete planet;
		pit = mPlanets.erase(pit);
	}
}

void Universe::initialize() {
}
