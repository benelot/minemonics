//# corresponding headers
#include <controller/Evaluation.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/ControlConfiguration.hpp>

//## controller headers
#include <controller/StateHandler.hpp>
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
#include <model/universe/evolution/EvolutionModel.hpp>
#include <model/universe/PlanetModel.hpp>

//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

BoostLogger Evaluation::mBoostLogger; /*<! initialize the boost logger*/
Evaluation::_Init Evaluation::_initializer;
Evaluation::Evaluation() :
	mPlanet(NULL), mStart(0), mHasFailed(false),mMarked(false) {
}

Evaluation::Evaluation(Planet* const planet, const double evaluationTime) :
	mPlanet(planet), mStart(0), mHasFailed(false), mEvaluationModel(
		planet->getPlanetModel(), evaluationTime),mMarked(false) {
}

Evaluation::~Evaluation() {
	mPlanet = NULL;

	//remove populations but do not delete the creatures
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit = mPopulations.erase(pit)) {

		// clear the creature vectors to avoid deleting them in case population would try to delete it.
		(*pit)->getCreatures().clear();
		(*pit)->getPopulationModel()->getCreatureModels().clear();
		delete *pit;
	}
}

void Evaluation::initialize() {
	mGenerationSerializationPath =
		mPlanet->getPlanetModel()->getEvolutionModel().getPopulationModels()[mPlanet->getPlanetModel()->getEvolutionModel().getCurrentPopulationIndex()]->getGenerationSerializationPath();
	mEvaluationModel.initialize();
}

void Evaluation::addPopulation(Population* const population) {
	mPopulations.push_back(population);
	mEvaluationModel.addPopulationModel(population->getPopulationModel());
}

void Evaluation::setup() {
	SimulationManager::getSingleton()->getViewController().addPlanetToView(
		mPlanet);
	SimulationManager::getSingleton()->getStateHandler().setCurrentlySelectedPlanet(
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

			if (ControlConfiguration::RANDOM_PERTURBATION) {
				(*pit)->perturbCreatureControllers();
			}
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
	mStart = SimulationManager::getSingleton()->getRuntime();

	if (limbQty == 0 || limbQty == 1) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature discarded because it had no body or just one limb.";
		mHasFailed = true;
		teardown();
	} else {
		mEvaluationModel.setEvaluating(true);
	}
}

void Evaluation::process() {
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->process();
	}
}

void Evaluation::teardown() {
	SimulationManager::getSingleton()->getViewController().setEvaluationInView(
	NULL);

	SimulationManager::getSingleton()->getViewController().removePlanetFromView(
		mPlanet);
	SimulationManager::getSingleton()->getStateHandler().setCurrentlySelectedPlanet(
	NULL);
	SimulationManager::getSingleton()->getMousePicker().setPicking(false);

	if (!mHasFailed) {
		// save creatures of evaluated populations
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {
			for (std::vector<Creature*>::iterator cit =
				(*pit)->getCreatures().begin();
				cit != (*pit)->getCreatures().end(); cit++) {
				if(mMarked){
					(*cit)->setMarked(true);
				}
				(*cit)->save(mGenerationSerializationPath);
			}
		}

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

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< mEvaluationModel.getTimePassed() << " seconds simulated in "
	<< ((float) (SimulationManager::getSingleton()->getRuntime() - mStart))
	/ 1000.0f << " seconds/ Speedup = "
	<< mEvaluationModel.getTimePassed()
	/ (((float) (SimulationManager::getSingleton()->getRuntime()
				- mStart)) / 1000.0f);
}

void Evaluation::update(const double timeSinceLastTick) {

	//update the planet's environment shared with other evaluation
	mPlanet->getEnvironment()->update(timeSinceLastTick);

	//update the competing populations
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->update(timeSinceLastTick);
	}

//	if (mEvaluationModel.getTimePassed()
//		> PhysicsConfiguration::DISCARDING_STARTS) {
//		for (std::vector<Population*>::iterator pit = mPopulations.begin();
//			pit != mPopulations.end(); pit++) {
//
//			if ((*pit)->hasInterpenetrations()) {
//				//TODO: Review this decision again in the case of a whole population
//				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature discarded because of unsolvable interpenetrations.";
//				mHasFailed = true;
//				teardown();
//				break;
//			}
//		}
//	}

	if (mEvaluationModel.getTimePassed()
		> PhysicsConfiguration::DISCARDING_STARTS) {
		for (std::vector<Population*>::iterator pit = mPopulations.begin();
			pit != mPopulations.end(); pit++) {

			if ((*pit)->maxJointVelocity()
				> MorphologyConfiguration::JOINT_MAX_VELOCITY) {
				//TODO: Review this decision again in the case of a whole population
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature discarded because of too high speeds.";
				mHasFailed = true;
				teardown();
				break;
			}
		}
	}

	//update the time passed
	mEvaluationModel.addTimePassed(timeSinceLastTick);

//	std::cout <<  "\t" << mEvaluationModel.getTimePassed() << std::endl;

	//terminate if the time passed is higher than the evaluation time
	if (mEvaluationModel.getTimePassed()
		> mEvaluationModel.getEvaluationTime()) {

		teardown();
	}
}

void Evaluation::setFailed(bool hasFailed) {
	mHasFailed = hasFailed;
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature discarded on user request.";
}

void Evaluation::setMarked(bool marked){
	mMarked = marked;
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creature marked on user request.";
}
