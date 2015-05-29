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

void Planet::initialize(SimulationManager* simulationManager,Environment::EnvironmentType type,
		OgreBtDebugDrawer* debugDrawer) {
	//create earth evolution
	mEvolution = new Evolution();
	mEvolution->initialize();

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
		((Plane*) mEnvironment)->initialize(simulationManager, NULL, debugDrawer);
		break;
	}
	}
	mPlanetModel.initialize();
	mPlanetModel.setEvolutionModel(&mEvolution->getEvolutionModel());
	mPlanetModel.setEnvironmentModel(mEnvironment->getEnvironmentModel());
}

void Planet::addPopulation(Population* population) {
	mEvolution->addPopulation(population);
}

void Planet::stepPhysics(double timeSinceLastFrame) {
	mPlanetModel.getEnvironmentModel()->getPhysicsController()->stepBulletPhysics(timeSinceLastFrame);
}

void Planet::update() {
	mEvolution->update();
	mEnvironment->update();
}

bool Planet::proceedEvaluation() {
	mPlanetModel.proceedEvaluation();
	return true;
}

void Planet::drawDebugWorld() {
	//draws the debug world if it is enabled
	mPlanetModel.getEnvironmentModel()->getPhysicsController()->getDynamicsWorld()->debugDrawWorld();

}
