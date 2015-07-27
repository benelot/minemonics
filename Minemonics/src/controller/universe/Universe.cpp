//# corresponding header
#include <controller/universe/Universe.hpp>

//# forward declarations
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
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger Universe::mBoostLogger; /*<! initialize the boost logger*/
Universe::_Init Universe::_initializer;
Universe::Universe() {
//	mEvaluationController();
	mPlanets.clear();
//	mUniverseModel();
}

Universe::~Universe() {
//	~mEvaluationController()

	//delete the planets
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end();) {
		Planet* planet = (*pit);
		delete planet;
		pit = mPlanets.erase(pit);
	}

//	~mUniverseModel()
}

void Universe::initialize(const int parallelEvaluationsQty) {
	mEvaluationController.initialize(this, parallelEvaluationsQty);
}

void Universe::addPlanet(Planet* const planet) {
	mPlanets.push_back(planet);
	mUniverseModel.addPlanetModel(planet->getPlanetModel());
}

void Universe::proceedEvaluation() {
	// if there are planets in the universe
	if (mPlanets.size() != 0) {
		// if the evaluation of the certain planet goes into the next generation, we go to the next planet.
		if (!mPlanets[mUniverseModel.getCurrentEvaluationPlanetIndex()]->proceedEvaluation()) {
			mUniverseModel.setCurrentEvaluationPlanetIndex(
					(mUniverseModel.getCurrentEvaluationPlanetIndex() + 1
							< mPlanets.size()) ?
							mUniverseModel.getCurrentEvaluationPlanetIndex()
									+ 1 :
							0);
		}
	}
	mUniverseModel.proceedEvaluation();
}

void Universe::setSimulationSpeed(double simulationSpeed){
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		(*pit)->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->setSimulationSpeed(simulationSpeed);
	}
}

void Universe::stepPhysics(const double timeSinceLastFrame) {
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

void Universe::update(const double timeSinceLastTick) {
	mEvaluationController.update(timeSinceLastTick);
}
