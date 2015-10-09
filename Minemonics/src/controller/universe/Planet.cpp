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
#include <controller/universe/environments/Plane.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
//## utils headers

BoostLogger Planet::mBoostLogger; /*<! initialize the boost logger*/
Planet::_Init Planet::_initializer;
Planet::Planet() :
	mEnvironment(NULL), mPlanetModel(NULL) {
	mPlanetModel = new PlanetModel();
}
Planet::Planet(const PhysicsController::PhysicsModelType physicsModelType,
	const EnvironmentModel::EnvironmentType environmentType,
	const int evaluationTime, EvolutionModel::EvaluationType evaluationType,
	int tournamentSize) :
	mEnvironment(NULL) {
	mPlanetModel = new PlanetModel(evaluationType, evaluationTime,
		tournamentSize,physicsModelType, environmentType);

	//the planet specification is complete, we can initialize it
	initialize();
}

Planet::Planet(PlanetModel* const planetModel) :
	mEnvironment(NULL), mPlanetModel(planetModel) {
}

void Planet::initialize() {
	mPlanetModel->initialize();

	//create earth evolution
	mEvolution.initialize(
		&SimulationManager::getSingleton()->getUniverse().getEvaluationController(),
		this, &mPlanetModel->getEvolutionModel());

	// set up environment
	switch (mPlanetModel->getEnvironmentModel()->getType()) {
	case EnvironmentModel::HILLS: {
		//		mEnvironment = new Hills();
		//		((Hills*) mEnvironment)->initialize(physicsModelType, light);
		break;
	}
	case EnvironmentModel::PLANE: {
		//create the terrain
		mEnvironment = new Plane();
		((Plane*) mEnvironment)->initialize(mPlanetModel->getEnvironmentModel(),
			SimulationManager::getSingleton()->getSun());
		break;
	}
	}
}

Planet::~Planet() {
//	~mEvolution()
	delete mPlanetModel;
	mPlanetModel = NULL;

	delete mEnvironment;
	mEnvironment = NULL;
}

void Planet::addPopulation(Population* const population) {
	mEvolution.addPopulation(population);
}

void Planet::stepPhysics(const double timeSinceLastFrame) {
	mPlanetModel->getEnvironmentModel()->getPhysicsController()->stepBulletPhysics(
		timeSinceLastFrame);
}

void Planet::update(double timeSinceLastTick) {
	mEnvironment->update(timeSinceLastTick);
	mEvolution.update(timeSinceLastTick);
}

bool Planet::proceedEvaluation() {

	//if the evolution can not proceed, then remove the environment model from the world.
	bool canNotProceed = !mEvolution.proceedEvaluation();
	if (canNotProceed) {
		mEnvironment->removeFromWorld();
	}

	//TODO: The return value says if we are at the planet's end because it ran out of epochs.
	mPlanetModel->proceedEvaluation();
	return canNotProceed;
}

void Planet::drawDebugWorld() {
	//draws the debug world if it is enabled
	mPlanetModel->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld()->debugDrawWorld();

}

void Planet::performEmbryogenesis() {
	mEvolution.performEmbryogenesis();
}

int Planet::getTotalCreatureQty() {
	return mEvolution.getTotalCreatureQty();
}

PhysicsController::PhysicsModelType Planet::getPhysicsModelType() {
	return mEnvironment->getEnvironmentModel()->getPhysicsController()->getPhysicsModelType();
}

void Planet::addEpoch(Epoch* epoch) {
	mPlanetModel->addEpoch(epoch);
}

void Planet::setSerializationPath(std::string serializationPath) {
	mPlanetModel->setSerializationPath(serializationPath);
}

std::string Planet::getSerializationPath() {
	return mPlanetModel->getSerializationPath();
}

void Planet::save() {
	mPlanetModel->save();
}

void Planet::load() {
	mPlanetModel->load();
	initialize();
}
