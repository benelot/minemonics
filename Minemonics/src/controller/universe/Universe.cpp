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

void Universe::addPlanet(Planet* planet) {
	mPlanets.push_back(planet);
	mUniverseModel.addPlanetModel(&planet->getPlanetModel());
}

void Universe::proceedEvaluation() {
	// if there are planets in the universe
	if (mPlanets.size() != 0) {
		// if the evaluation of the certain planet goes into the next generation, we go to the next planet.
		if (!mPlanets[mUniverseModel.getCurrentEvaluationPlanetIndex()]->proceedEvaluation()) {
			mUniverseModel.setCurrentEvaluationPlanetIndex(
					(mUniverseModel.getCurrentEvaluationPlanetIndex()
							< mPlanets.size()) ?
							mUniverseModel.getCurrentEvaluationPlanetIndex()
									+ 1 :
							0);
		}
	}
	mUniverseModel.proceedEvaluation();
}

void Universe::stepPhysics(double timeSinceLastFrame) {
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		(*pit)->stepPhysics(timeSinceLastFrame);
	}
}

void Universe::drawDebugWorld() {
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		(*pit)->drawDebugWorld();
	}
}

void Universe::update() {
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		(*pit)->update();
	}
}
