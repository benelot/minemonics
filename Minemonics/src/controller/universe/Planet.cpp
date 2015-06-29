//# corresponding header
#include <controller/universe/Planet.hpp>

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
#include <controller/universe/evolution/Evolution.hpp>
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/environments/Plane.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>

//## view headers
//## utils headers

Planet::Planet() :
		mEnvironment(NULL), mEvolution(NULL) {
}

Planet::~Planet() {
	mEnvironment = NULL;
	mEvolution = NULL;
}

void Planet::initialize(SimulationManager* simulationManager,
		Environment::EnvironmentType type, OgreBtDebugDrawer* debugDrawer,
		int evaluationTime) {
	//create earth evolution
	mEvolution = new Evolution();
	mEvolution->initialize(
			&simulationManager->getUniverse().getEvaluationController(), this,
			evaluationTime);

	// set up environment
	switch (type) {
	case Environment::HILLS: {
//		mEnvironment = new Hills();
//		((Hills*) mEnvironment)->initialize(this, NULL,debugDrawer);
		break;
	}
	case Environment::PLANE: {
		//create the terrain
		mEnvironment = new Plane();
		((Plane*) mEnvironment)->initialize(simulationManager, NULL,
				debugDrawer);
		break;
	}
	}
	mPlanetModel.initialize(&mEvolution->getEvolutionModel(),
			mEnvironment->getEnvironmentModel());
}

void Planet::addPopulation(Population* population) {
	mEvolution->addPopulation(population);
}

void Planet::stepPhysics(double timeSinceLastFrame) {
	mPlanetModel.getEnvironmentModel()->getPhysicsController()->stepBulletPhysics(
			timeSinceLastFrame);
}

void Planet::update() {
	//TODO: This would update the creatures on the planet several times. Find out if this is good in the long run to comment this.
	//mEvolution->update();
	mEnvironment->update();
}

bool Planet::proceedEvaluation() {
	// add the environment model to the world if it is not yet added.
	if (!mEnvironment->isInWorld()) {
		mEnvironment->addToWorld();
	}

	//if the evolution can no proceed, then remove the environment model from the world.
	if (!mEvolution->proceedEvaluation()) {
		mEnvironment->removeFromWorld();
		return false;
	}
	mPlanetModel.proceedEvaluation();
	return true;
}

void Planet::drawDebugWorld() {
	//draws the debug world if it is enabled
	mPlanetModel.getEnvironmentModel()->getPhysicsController()->getDynamicsWorld()->debugDrawWorld();

}
