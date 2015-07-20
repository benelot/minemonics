//# corresponding header
#include <controller/universe/Planet.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/Universe.hpp>
#include <controller/universe/evolution/Evolution.hpp>
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/environments/Plane.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

BoostLogger Planet::mBoostLogger; /*<! initialize the boost logger*/
Planet::_Init Planet::_initializer;
Planet::Planet(const Environment::EnvironmentType type,
		OgreBtDebugDrawer* const debugDrawer, const int evaluationTime) :
		mEnvironment(NULL) {
	mPlanetModel = new PlanetModel();

	//create earth evolution
	mEvolution.initialize(
			&SimulationManager::getSingleton()->getUniverse().getEvaluationController(),
			this, evaluationTime);

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
		((Plane*) mEnvironment)->initialize(NULL, debugDrawer);
		break;
	}
	}
	mPlanetModel->initialize(mEvolution.getEvolutionModel(),
			mEnvironment->getEnvironmentModel());
}

Planet::Planet(PlanetModel* const planetModel) :
		mEnvironment(NULL), mPlanetModel(planetModel) {
}

Planet::~Planet() {
//	~mEnvironment()
//	~mEvolution()
	delete mPlanetModel;
}

void Planet::addPopulation(Population* const population) {
	mEvolution.addPopulation(population);
}

void Planet::stepPhysics(const double timeSinceLastFrame) {
	mPlanetModel->getEnvironmentModel()->getPhysicsController()->stepBulletPhysics(
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

	mPlanetModel->proceedEvaluation();

	//if the evolution can not proceed, then remove the environment model from the world.
	if (!mEvolution.proceedEvaluation()) {
		mEnvironment->removeFromWorld();
		return false;
	}
	return true;
}

void Planet::drawDebugWorld() {
	//draws the debug world if it is enabled
	mPlanetModel->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld()->debugDrawWorld();

}

void Planet::performEmbryogenesis() {
	mEvolution.performEmbryogenesis();
}
