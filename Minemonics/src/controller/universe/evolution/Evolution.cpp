//# corresponding headers
#include <controller/universe/evolution/Evolution.hpp>

//# forward declarations
//# system headers
#include <iostream>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/Evaluation.hpp>
#include <controller/EvaluationController.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <model/universe/Epoch.hpp>
#include <model/universe/evolution/juries/JuryFactory.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

BoostLogger Evolution::mBoostLogger; /*<! initialize the boost logger*/
Evolution::_Init Evolution::_initializer;
Evolution::Evolution() :
	mEvaluationController(NULL), mPlanet(NULL) {
	mEvolutionModel = new EvolutionModel();
}

Evolution::Evolution(EvolutionModel* const evolutionModel) :
	mEvaluationController(NULL), mPlanet(NULL), mEvolutionModel(evolutionModel) {
}

Evolution::~Evolution() {
	delete mEvolutionModel;
	mEvolutionModel = NULL;

	mEvaluationController = NULL;
	mPlanet = NULL;
}

void Evolution::initialize(EvaluationController* const evaluationController,
	Planet* planet, double evaluationTime, EvolutionModel::EvaluationType type,
	int tournamentSize) {
	mEvaluationController = evaluationController;
	mPlanet = planet;
	mEvolutionModel->initialize(type, evaluationTime, tournamentSize);
}

void Evolution::addPopulation(Population* const population) {
	mPopulations.push_back(population);
	mEvolutionModel->addNewPopulation(population->getPopulationModel());
}

bool Evolution::proceedEvaluation() {
	if (mPopulations.size() != 0
		&& mEvolutionModel->getCurrentPopulationIndex() < mPopulations.size()) {

		if (mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->isOutOfSync()) {
			mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->resyncWithModel();
		}

		switch (mEvolutionModel->getType()) {
		case EvolutionModel::INDIVIDUAL_EVALUATION: {

			if (mEvolutionModel->getCurrentCreatureIndex()
				< mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures().size()) {

				// create generation folder
				if (mEvolutionModel->getCurrentCreatureIndex() == 0) {
					//create folder for the generation
					std::string generationName = std::string("Generation-")
						+ boost::lexical_cast<std::string>(
							mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCurrentGeneration());
					FilesystemManipulator::createFolder(
							mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getSerializationPath(),
							generationName);
				}

				Evaluation* evaluation = new Evaluation();
				evaluation->initialize(mPlanet,
					mEvolutionModel->getEvaluationTime());

				// create population with single creature for evaluation
				Population* population = new Population();
				population->initialize(mPlanet, 1);

				Creature* creature =
					mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel->getCurrentCreatureIndex()];
				//add juries
				creature->clearJuries();
				for (int i = 0;
					i
						< mPlanet->getPlanetModel()->getCurrentEpoch()->getJuryTypes().size();
					i++) {
					Epoch* epoch = mPlanet->getPlanetModel()->getCurrentEpoch();
					creature->addJury(
						JuryFactory::buildJury(epoch->getJuryTypes()[i],
							epoch->getSortOrders()[i], epoch->getWeights()[i]));
				}

				population->addMember(creature);
				evaluation->addPopulation(population);

				mEvaluationController->addEvaluation(evaluation);
			}

			mEvolutionModel->evaluate();
			return mEvolutionModel->proceedEvaluation();
			break;
		}
		case EvolutionModel::N_INDIVIDUALS_TOURNAMENT_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
				mEvolutionModel->getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel->getTournamentSize(); i++) {
				population = new Population();
				population->initialize(mPlanet, 1);
				population->addMember(
					mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel->getCurrentCreatureIndex()]);
				;

				evaluation->addPopulation(population);

				//break if there are no more creatures
				if (!mEvolutionModel->proceedEvaluation()) {
					break;
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			mEvolutionModel->evaluate();
			return true;
			break;
		}
		case EvolutionModel::POPULATION_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
				mEvolutionModel->getEvaluationTime());

			Population* population;
			for (int i = 0;
				i
					< mEvolutionModel->getPopulationModels()[mEvolutionModel->getCurrentCreatureIndex()]->getCreatureModels().size();
				i++) {
				population = new Population();
				population->initialize(mPlanet, 1);
				population->addMember(
					mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel->getCurrentCreatureIndex()]);

				evaluation->addPopulation(population);

				//break if there are no more creatures
				if (!mEvolutionModel->proceedEvaluation()) {
					break;
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			mEvolutionModel->evaluate();
			return true;
			break;
		}
		case EvolutionModel::N_POPULATIONS_TOURNAMENT_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
				mEvolutionModel->getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel->getTournamentSize(); i++) {
				population = new Population();
				population->initialize(mPlanet,
					mEvolutionModel->getPopulationModels()[mEvolutionModel->getCurrentCreatureIndex()]->getCreatureModels().size());
				for (int j = 0;
					j
						< mEvolutionModel->getPopulationModels()[mEvolutionModel->getCurrentCreatureIndex()]->getCreatureModels().size();
					j++) {
					population->addMember(
						mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel->getCurrentCreatureIndex()]);

					evaluation->addPopulation(population);

					//break if there are no more creatures
					if (!mEvolutionModel->proceedEvaluation()) {
						break;
					}
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			mEvolutionModel->evaluate();
			break;
		}
		case EvolutionModel::POPULATIONS_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
				mEvolutionModel->getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel->getPopulationModels().size();
				i++) {
				population = new Population();
				population->initialize(mPlanet,
					mEvolutionModel->getPopulationModels()[mEvolutionModel->getCurrentCreatureIndex()]->getCreatureModels().size());
				for (int j = 0;
					j
						< mEvolutionModel->getPopulationModels()[mEvolutionModel->getCurrentCreatureIndex()]->getCreatureModels().size();
					j++) {
					population->addMember(
						mPopulations[mEvolutionModel->getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel->getCurrentCreatureIndex()]);
					mEvolutionModel->proceedEvaluation();

					evaluation->addPopulation(population);

					//break if there are no more creatures
					if (!mEvolutionModel->setCurrentCreatureIndex(
						mEvolutionModel->getCurrentCreatureIndex() + 1)) {
						break;
					}
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			mEvolutionModel->evaluate();
			return true;
			break;
		}
		default:
			return false;
			break;
		}
	} else {

//update lasting generations
		mPlanet->getPlanetModel()->getCurrentEpoch()->setLastingGenerations(
			mPlanet->getPlanetModel()->getCurrentEpoch()->getLastingGenerations()
				+ 1);
	}
	return false;
}

void Evolution::update(double timeSinceLastTick) {
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {
		(*pit)->update(timeSinceLastTick);
	}
}

void Evolution::performEmbryogenesis() {

	//for each population...
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {

		int creatureQty = 0;
		//for each creature in the population
		for (std::vector<Creature*>::iterator cit =
			(*pit)->getCreatures().begin(); cit != (*pit)->getCreatures().end();
			) {

			//Performing embryogenesis on creature(x/all)
			//Gene Qty: z
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Performing embryogenesis on creature(" << creatureQty << "/"
			<< (*pit)->getCreatures().size() << "):\nGene Qty: "
			<< (*cit)->getCreatureModel()->getGenotype().getGenes().size();

			int limbQty = (*cit)->performEmbryogenesis();

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "Components:"
			<< (*cit)->getCreatureModel()->getPhenotypeModel()->getComponentModels().size();
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< (**cit).getCreatureModel();
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "Creature finished.\n"
			<< "################################\n\n";

			if (limbQty == 0) {
				Creature* creature = *cit;
				cit = (*pit)->getCreatures().erase(cit);
				delete creature;
			} else {
				creatureQty++;
				cit++;
			}
		}
	}
}

int Evolution::getTotalCreatureQty() {
	int creatureQty = 0;
	//for each population...
	for (std::vector<Population*>::iterator pit = mPopulations.begin();
		pit != mPopulations.end(); pit++) {

		//for each creature in the population
		for (std::vector<Creature*>::iterator cit =
			(*pit)->getCreatures().begin(); cit != (*pit)->getCreatures().end();
			cit++) {
			creatureQty++;
		}
	}
	return creatureQty;
}
