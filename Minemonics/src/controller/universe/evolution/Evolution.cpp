//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/Evaluation.hpp>
#include <controller/EvaluationController.hpp>
#include <controller/universe/evolution/Evolution.hpp>
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

Evolution::Evolution() :
		mEvaluationController(NULL), mPlanet(NULL) {
}

Evolution::~Evolution() {

}

void Evolution::initialize(EvaluationController* evaluationController,
		Planet* planet, double evaluationTime,
		EvolutionModel::EvaluationType type, int tournamentSize) {
	mEvaluationController = evaluationController;
	mPlanet = planet;
	mEvolutionModel.initialize(type, evaluationTime, tournamentSize);
}

void Evolution::addPopulation(Population* population) {
	mPopulations.push_back(population);
	mEvolutionModel.addNewPopulation(population->getPopulationModel());
}

bool Evolution::proceedEvaluation() {

	if (mPopulations.size() != 0
			&& mEvolutionModel.getCurrentPopulationIndex()
					< mPopulations.size()) {

		switch (mEvolutionModel.getType()) {
		case EvolutionModel::INDIVIDUAL_EVALUATION: {

			if (mEvolutionModel.getCurrentCreatureIndex()
					< mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures().size()) {

				Evaluation* evaluation = new Evaluation();
				evaluation->initialize(mPlanet,
						mEvolutionModel.getEvaluationTime());

				Population* population = new Population();
				population->initialize(mPlanet, 1);
				population->addMember(
						mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel.getCurrentCreatureIndex()]);

				evaluation->addPopulation(population);

				mEvaluationController->addEvaluation(evaluation);
			}

			return mEvolutionModel.proceedEvaluation();
			break;
		}
		case EvolutionModel::N_INDIVIDUALS_TOURNAMENT_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
					mEvolutionModel.getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel.getTournamentSize(); i++) {
				population = new Population();
				population->initialize(mPlanet, 1);
				population->addMember(
						mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel.getCurrentCreatureIndex()]);
				;

				evaluation->addPopulation(population);

				//break if there are no more creatures
				if (!mEvolutionModel.proceedEvaluation()) {
					break;
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			return true;
			break;
		}
		case EvolutionModel::POPULATION_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
					mEvolutionModel.getEvaluationTime());

			Population* population;
			for (int i = 0;
					i
							< mEvolutionModel.getPopulationModels()[mEvolutionModel.getCurrentCreatureIndex()]->getCreatureModels().size();
					i++) {
				population = new Population();
				population->initialize(mPlanet, 1);
				population->addMember(
						mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel.getCurrentCreatureIndex()]);

				evaluation->addPopulation(population);

				//break if there are no more creatures
				if (!mEvolutionModel.proceedEvaluation()) {
					break;
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			return true;
			break;
		}
		case EvolutionModel::N_POPULATIONS_TOURNAMENT_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
					mEvolutionModel.getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel.getTournamentSize(); i++) {
				population = new Population();
				population->initialize(mPlanet,
						mEvolutionModel.getPopulationModels()[mEvolutionModel.getCurrentCreatureIndex()]->getCreatureModels().size());
				for (int j = 0;
						j
								< mEvolutionModel.getPopulationModels()[mEvolutionModel.getCurrentCreatureIndex()]->getCreatureModels().size();
						j++) {
					population->addMember(
							mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel.getCurrentCreatureIndex()]);

					evaluation->addPopulation(population);

					//break if there are no more creatures
					if (!mEvolutionModel.proceedEvaluation()) {
						break;
					}
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			break;
		}
		case EvolutionModel::POPULATIONS_EVALUATION: {
			Evaluation* evaluation = new Evaluation();
			evaluation->initialize(mPlanet,
					mEvolutionModel.getEvaluationTime());

			Population* population;
			for (int i = 0; i < mEvolutionModel.getPopulationModels().size();
					i++) {
				population = new Population();
				population->initialize(mPlanet,
						mEvolutionModel.getPopulationModels()[mEvolutionModel.getCurrentCreatureIndex()]->getCreatureModels().size());
				for (int j = 0;
						j
								< mEvolutionModel.getPopulationModels()[mEvolutionModel.getCurrentCreatureIndex()]->getCreatureModels().size();
						j++) {
					population->addMember(
							mPopulations[mEvolutionModel.getCurrentPopulationIndex()]->getCreatures()[mEvolutionModel.getCurrentCreatureIndex()]);
					mEvolutionModel.proceedEvaluation();

					evaluation->addPopulation(population);

					//break if there are no more creatures
					if (!mEvolutionModel.setCurrentCreatureIndex(
							mEvolutionModel.getCurrentCreatureIndex() + 1)) {
						break;
					}
				}
			}

			mEvaluationController->addEvaluation(evaluation);
			return true;
			break;
		}
		default:
			return false;
			break;
		}
	}
	return false;
}

void Evolution::update() {
	std::vector<Population*>::iterator pit = mPopulations.begin();
	for (; pit != mPopulations.end(); pit++) {
		(*pit)->update();
	}
}
