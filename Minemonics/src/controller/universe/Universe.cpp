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
#include <configuration/ControlConfiguration.hpp>

//## controller headers
#include <model/universe/UniverseModel.hpp>
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger Universe::mBoostLogger; /*<! initialize the boost logger*/
Universe::_Init Universe::_initializer;
Universe::Universe() :
	mSimulationSpeed(pow(2, PhysicsConfiguration::SIMULATION_SPEED_01)) {
//	mEvaluationController();
	mPlanets.clear();
//	mUniverseModel();
}

Universe::~Universe() {
//	~mEvaluationController()

	teardown();

//	~mUniverseModel()
}

void Universe::teardown() {
	//delete the planets
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		delete (*pit);
	}

	mPlanets.clear();
}

void Universe::initialize(const int parallelEvaluationsQty) {
	mEvaluationController.initialize(this, parallelEvaluationsQty);
}

void Universe::addPlanet(Planet* const planet) {
	mPlanets.push_back(planet);
	mUniverseModel.addPlanetModel(planet->getPlanetModel());
}

bool Universe::proceedEvaluation() {
	// if there are planets in the universe
	if (mPlanets.size() != 0) {
		// if the evaluation of a planet continues to the next generation, we go to the next planet.
		if (!mPlanets[mUniverseModel.getCurrentEvaluationPlanetIndex()]->proceedEvaluation()) {
			mUniverseModel.setCurrentEvaluationPlanetIndex( // we go to the next planet in line or go back to the first
				(mUniverseModel.getCurrentEvaluationPlanetIndex() + 1
					< mPlanets.size()) ?
					mUniverseModel.getCurrentEvaluationPlanetIndex() + 1 : 0);
		}
	} else {
		return false;
	}
	mUniverseModel.proceedEvaluation();
	return true;
}

void Universe::setSimulationSpeed(double simulationSpeed) {
	mSimulationSpeed = simulationSpeed;
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		(*pit)->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->setSimulationSpeed(
			simulationSpeed);
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

void Universe::update(const double timeStep) {
	double speed = pow(2, /**!< calculate the speed of the simulation */
	PhysicsConfiguration::SIMULATION_SPEEDS[mSimulationSpeed]);

	int subSteps = floor( /**!< Increase the time step we take by the speed we want the simulation to run.*/
	speed * timeStep / PhysicsConfiguration::FIXED_STEP_SIZE_SEC);

	for (int i = 0; i < subSteps; i++) {
		stepPhysics(PhysicsConfiguration::FIXED_STEP_SIZE_SEC);
		mEvaluationController.update(PhysicsConfiguration::FIXED_STEP_SIZE_SEC);
	}
}

int Universe::getTotalCreatureQty() {
	int totalCreatureQty = 0;
	std::vector<Planet*>::iterator pit = mPlanets.begin();
	for (; pit != mPlanets.end(); pit++) {
		totalCreatureQty += (*pit)->getTotalCreatureQty();
	}
	return totalCreatureQty;
}
