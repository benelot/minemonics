//# corresponding headers
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
#include <controller/StateHandler.hpp>
#include <controller/Evaluation.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/universe/environments/Environment.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

BoostLogger Evaluation::mBoostLogger; /*<! initialize the boost logger*/
Evaluation::_Init Evaluation::_initializer;
Evaluation::Evaluation() :
	mPlanet(NULL), mStart(0), mHasFailed(false), mOnce(true) {
}

Evaluation::~Evaluation() {
	mPlanet = NULL;
	mPopulations.clear();
}

void Evaluation::initialize(Planet* const planet, const double evaluationTime) {
	mPlanet = planet;
	mEvaluationModel.initialize(planet->getPlanetModel(), evaluationTime);
}

void Evaluation::addPopulation(Population* const population) {
	mPopulations.push_back(population);
	mEvaluationModel.addPopulationModel(population->getPopulationModel());
}

void Evaluation::setup() {
	SimulationManager::getSingleton()->getViewController().addPlanetToView(
		mPlanet);
	SimulationManager::getSingleton()->getViewController().setSelectedPlanet(
		mPlanet);
	//add environment to the world
	//TODO: Must be a separate copy for parallel evaluations(you can not use the same reference for multiple worlds), but must update (possibly in parallel)
	// the main environment to stay the same for all evaluations
	int limbQty = 0;
	switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
	case StateHandler::SIMULATION: {

		//add competing populations to the world
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {
			(*pit)->reset();
			limbQty += (*pit)->addToWorld();
		}

		mPlanet->getEnvironment()->addToWorld();
		break;
	}
	case StateHandler::HEADLESS_SIMULATION: {

		//add competing populations to the world
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {
			(*pit)->reset();
			limbQty += (*pit)->addToPhysicsWorld();
		}

		mPlanet->getEnvironment()->addToPhysicsWorld();
		break;
	}
	default: {
		break;
	}
	}

	if (limbQty == 0 || limbQty == 1) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "Creature discarded because it had no body or just one limb.";
		mHasFailed = true;
		teardown();
	} else {
		mEvaluationModel.setEvaluating(true);
	}

	mStart = SimulationManager::getSingleton()->getRuntime();
}

void Evaluation::process() {
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->process();
	}
}

void Evaluation::teardown() {
	SimulationManager::getSingleton()->getViewController().removePlanetFromView(
		mPlanet);
	SimulationManager::getSingleton()->getViewController().setSelectedPlanet(
		NULL);

	if (!mHasFailed) {
		process();
	} else {
		// remove competing populations from the world
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {
			(*pit)->markCull();
		}
	}

	SimulationManager::getSingleton()->getDebugDrawer().clear();
	//remove the environment from the world
	mPlanet->getEnvironment()->removeFromWorld();

	// remove competing populations from the world
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->removeFromWorld();
	}

	mEvaluationModel.setEvaluating(false);
	mEvaluationModel.setTornDown(true);

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
		<< mEvaluationModel.getTimePassed() << " seconds simulated in "
		<< ((float) (SimulationManager::getSingleton()->getRuntime() - mStart))
			/ 1000.0f << " seconds/ Speedup = "
		<< mEvaluationModel.getTimePassed()
			/ (((float) (SimulationManager::getSingleton()->getRuntime()
				- mStart)) / 1000.0f) << std::endl;
}

void Evaluation::update(const double timeSinceLastTick) {

	//update the planet's environment shared with other evaluation
	mPlanet->getEnvironment()->update(timeSinceLastTick);

	//update the competing populations
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->update(timeSinceLastTick);
	}

	if (mEvaluationModel.getTimePassed()
		> PhysicsConfiguration::DISCARDING_STARTS) {
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {
//			if (mOnce) {
//				//TODO: Enable to calm forces from numerical resolving.
//				(*pit)->calm();
//			}
			if ((*pit)->hasInterpenetrations()) {
				//TODO: Review this decision again in the case of a whole population
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
					<< "Creature discarded because of unsolvable interpenetrations.";
				mHasFailed = true;
				teardown();
				break;
			}
		}
//		mOnce = false;
	}

	//update the time passed
	mEvaluationModel.addTimePassed(timeSinceLastTick);

	//terminate if the time passed is higher than the evaluation time
	if (mEvaluationModel.getTimePassed()
		> mEvaluationModel.getEvaluationTime()) {

		teardown();
	}
}
