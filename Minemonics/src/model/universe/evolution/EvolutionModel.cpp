//# corresponding header
#include <model/universe/evolution/EvolutionModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/EvolutionConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers
EvolutionModel::EvolutionModel(const EvaluationType type,
	const double evaluationTime, const int tournamentSize) :
	mPhase(VARIATION_PHASE), mType(type), mEvaluationTime(evaluationTime), mCurrentPopulationIndex(
		0), mCurrentCreatureIndex(0), mTournamentSize(tournamentSize) {

}
EvolutionModel::EvolutionModel() :
	mPhase(VARIATION_PHASE), mType(INDIVIDUAL_EVALUATION), mEvaluationTime(0), mCurrentPopulationIndex(
		0), mCurrentCreatureIndex(0), mTournamentSize(1) {

}

EvolutionModel::~EvolutionModel() {
	// models only delete their own things
	mPopulationModels.clear();
}

void EvolutionModel::initialize() {
	//TODO:Get reasonable numbers
	mReaper.initialize(EvolutionConfiguration::REAPER_REAP_PERCENTAGE,
		EvolutionConfiguration::REAPER_CROSSOVER_PERCENTAGE,
		EvolutionConfiguration::REAPER_GENE_MUTATION_PERCENTAGE,
		EvolutionConfiguration::REAPER_GENE_SPLIT_PERCENTAGE,
		EvolutionConfiguration::REAPER_LINK_MUTATION_PERCENTAGE,
		EvolutionConfiguration::REAPER_GROW_STUB_PERCENTAGE,
		EvolutionConfiguration::REAPER_GRAFT_PERCENTAGE,
		EvolutionConfiguration::REAPER_SOW_FRESH_PERCENTAGE);

	//GENERATION
}

bool EvolutionModel::proceedEvaluation() {
	if (mCurrentPopulationIndex < mPopulationModels.size()) {

		if (mCurrentCreatureIndex
			< mPopulationModels[mCurrentPopulationIndex]->getCreatureModels().size()) {
			mCurrentCreatureIndex++;
			return true;
		} else {
			// process the evaluated populations
			process();

			// cull the evaluated populations
			cull();

			// variate the evaluated populations
			variate();

			//increase generation
			mPopulationModels[mCurrentPopulationIndex]->setCurrentGeneration(
				mPopulationModels[mCurrentPopulationIndex]->getCurrentGeneration()
					+ 1);

			mPopulationModels[mCurrentPopulationIndex]->setOutOfSync(true);

			if (mCurrentPopulationIndex + 1 < mPopulationModels.size()) {
				mCurrentPopulationIndex++;
				mCurrentCreatureIndex = 0;
			} else {
				mCurrentPopulationIndex = 0;
				mCurrentCreatureIndex = 0;
				return false;
			}

		}
	} else {
		return false;
	}
	return true;
}

bool EvolutionModel::evaluate() {
	//EVALUATION
	mPhase = EVALUATION_PHASE;
	// run creature evaluation according to the evolution type and then return true

	return true;
}

bool EvolutionModel::process() {
	//Enter the Processing phase
	mPhase = PROCESSING_PHASE;

	//prepare statistics
	//TODO: Calculate everything for statistics
	return true;
}

bool EvolutionModel::cull() {
	//Enter the Culling phase
	mPhase = CULLING_PHASE;

	//call the reaper to reap
	mReaper.reap(mPopulationModels[mCurrentPopulationIndex]);

	return true;
}

void EvolutionModel::addNewPopulation(PopulationModel* const populationModel) {
	mPopulationModels.push_back(populationModel);
}

bool EvolutionModel::variate() {
	//Enter the Variation phase
	mPhase = VARIATION_PHASE;

	//call the reaper to sow
	mReaper.sow(mPopulationModels[mCurrentPopulationIndex]);
	return true;
}

void EvolutionModel::performEmbryogenesis() {
	for (std::vector<PopulationModel*>::iterator pit =
		mPopulationModels.begin(); pit != mPopulationModels.end(); pit++) {
		for (std::vector<CreatureModel*>::iterator cit =
			(*pit)->getCreatureModels().begin();
			cit != (*pit)->getCreatureModels().end(); cit++) {
			(*cit)->performEmbryogenesis();
		}
	}
}

bool EvolutionModel::setCurrentCreatureIndex(
	const std::vector<CreatureModel*>::size_type currentCreatureIndex) {
	if (currentCreatureIndex
		< mPopulationModels[mCurrentPopulationIndex]->getCreatureModels().size()) {
		mCurrentCreatureIndex = currentCreatureIndex;
		return true;
	} else {
		return false;
	}
}
