//# corresponding header
#include <controller/universe/Planet.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/environments/Plane.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/universe/Universe.hpp>

//## model headers
#include <model/Serializable.hpp>

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
		tournamentSize, physicsModelType, environmentType);

	initialize(); /**!< the planet specification is complete, we can initialize it */
}

Planet::Planet(PlanetModel* const planetModel) :
	mEnvironment(NULL), mPlanetModel(planetModel) {
}

Planet::~Planet() {
//	~mEvolution()
	delete mPlanetModel;
	mPlanetModel = NULL;

	delete mEnvironment;
	mEnvironment = NULL;
}

void Planet::initialize() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup planet...";
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
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup planet...done.";
}

void Planet::addPopulation(Population* const population) {
	mEvolution.addPopulation(population);
}

void Planet::stepPhysics(const double timeStep) {
	mPlanetModel->getEnvironmentModel()->getPhysicsController()->stepBulletPhysics(
		timeStep);
}

void Planet::update(double timeSinceLastTick) {
	mEnvironment->update(timeSinceLastTick);
	mEvolution.update(timeSinceLastTick);
}

bool Planet::proceedEvaluation() {

	bool canProceed = false;
	if (mPlanetModel->proceedEvaluation()) {

		canProceed = mEvolution.proceedEvaluation(); //if the evolution can not proceed, then remove the environment model from the world.
		if (!canProceed) {
			mEnvironment->removeFromWorld();
		}

	} else {
		return false;
	}

	return canProceed;
}

void Planet::drawDebugWorld() {
	mPlanetModel->drawDebugWorld();

}

void Planet::performEmbryogenesis() {
	mEvolution.performEmbryogenesis();
}

int Planet::getTotalCreatureQty() {
	return mEvolution.getTotalCreatureQty();
}

void Planet::perturbPopulations(){
	mPlanetModel->perturbPopulations();
}

PhysicsController::PhysicsModelType Planet::getPhysicsModelType() {
	return mPlanetModel->getPhysicsModelType();
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
