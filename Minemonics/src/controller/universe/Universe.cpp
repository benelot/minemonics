//# corresponding header
#include <controller/universe/Universe.hpp>

//# forward declarations
//# system headers
#include <cmath>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/ControlConfiguration.hpp>
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
#include <controller/universe/Universe.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger Universe::mBoostLogger; /*<! initialize the boost logger*/
Universe::_Init Universe::_initializer;
Universe::Universe() :
	mSimulationSpeed(pow(2, PhysicsConfiguration::SIMULATION_SPEED_03)) {

	mEvaluationController.setPaused(true); // start in paused mode
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

	for (std::vector<Planet*>::iterator pit = mPlanets.begin();
		pit != mPlanets.end(); pit++) { //delete all planets
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
	if (mPlanets.size() != 0) { /**!< if there are planets in the universe */

		if (!mPlanets[mUniverseModel.getEvaluatingPlanetIndex()]->proceedEvaluation()) { /**!< if the evaluation of a planet continues to the next generation, we go to the next planet. */
			mUniverseModel.setEvaluatingPlanetIndex(
				(mUniverseModel.getEvaluatingPlanetIndex() + 1 < mPlanets.size()) ?
					mUniverseModel.getEvaluatingPlanetIndex() + 1 : 0); /**!< we go to the next planet in line or go back to the first */
		}
		mUniverseModel.proceedEvaluation(); /**!< Proceed the evaluation */
		return true;
	} else {
		return false;
	}
}

void Universe::setSimulationSpeed(double simulationSpeed) {
	mSimulationSpeed = simulationSpeed;
	for (std::vector<Planet*>::iterator pit = mPlanets.begin();
		pit != mPlanets.end(); pit++) { /**!< For all planets */
		(*pit)->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->setSimulationSpeed(
			simulationSpeed); /**!< Set the simulation speed */
	}
}

void Universe::stepPhysics(const double timeSinceLastFrame) {
	for (std::vector<Planet*>::iterator pit = mPlanets.begin();
		pit != mPlanets.end(); pit++) { /**!< For all planets */
		(*pit)->stepPhysics(timeSinceLastFrame); /**!< perform the physics forward step */
	}
}

void Universe::drawDebugWorld() {
	for (std::vector<Planet*>::iterator pit = mPlanets.begin();
		pit != mPlanets.end(); pit++) { /**!< For all planets */
		(*pit)->drawDebugWorld(); /**!< Draw the debug worlds */
	}
}

void Universe::update(const double timeStep) {
	int subSteps = round(timeStep / PhysicsConfiguration::FIXED_STEP_SIZE_SEC); /**!< Calculate the number of full normal time steps we can take */

	if (!mEvaluationController.isPaused()) {
		for (int i = 0; i < subSteps; i++) { /**!< Perform the number of substeps to reach the timestep*/
			stepPhysics(PhysicsConfiguration::FIXED_STEP_SIZE_SEC);
			mEvaluationController.update(
				PhysicsConfiguration::FIXED_STEP_SIZE_SEC);
		}
	}
}

int Universe::getTotalCreatureQty() {
	int totalCreatureQty = 0;
	for (std::vector<Planet*>::iterator pit = mPlanets.begin();
		pit != mPlanets.end(); pit++) { /**!< For all planets*/
		totalCreatureQty += (*pit)->getTotalCreatureQty(); /**!< Sum the creature quantities */
	}
	return totalCreatureQty;
}
