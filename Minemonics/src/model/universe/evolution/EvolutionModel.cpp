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
//## controller headers
//## model headers
//## view headers
//## utils headers

EvolutionModel::EvolutionModel() :
		mPhase(VARIATION_PHASE), mType(INDIVIDUAL_EVALUATION), mEvaluationTime(
				0), mCurrentPopulationIndex(0), mCurrentCreatureIndex(0), mTournamentSize(
				1) {

}

EvolutionModel::~EvolutionModel() {

}

void EvolutionModel::initialize(EvaluationType type, double evaluationTime,
		int tournamentSize) {
	mType = type;
	mEvaluationTime = evaluationTime;
	mTournamentSize = tournamentSize;
	//TODO:Get reasonable numbers
	mReaper.initialize(0.1, 0.1, 0.1, 0.1, 0.1, 0.2, 0.3);

	//GENERATION
}

bool EvolutionModel::proceedEvaluation() {
	if (mCurrentPopulationIndex < mPopulationModels.size()) {

		if (mCurrentCreatureIndex
				< mPopulationModels[mCurrentPopulationIndex]->getCreatureModels().size()) {
			mCurrentCreatureIndex++;
		} else if (mCurrentPopulationIndex + 1 < mPopulationModels.size()) {
			// process the evaluated populations
			process();

			// cull the evaluated populations
			cull();

			// variate the evaluated populations
			variate();
			mCurrentPopulationIndex++;
			mCurrentCreatureIndex = 0;
		} else {
			mCurrentPopulationIndex = 0;
			mCurrentCreatureIndex = 0;
			return false;
		}
	} else {
		return false;
	}
	return true;
}

bool EvolutionModel::evaluate() {
//EVALUATION
	mPhase = EVALUATION_PHASE;
	//TODO: Delete if not used in the end.
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

void EvolutionModel::addNewPopulation(PopulationModel* populationModel) {
	mPopulationModels.push_back(populationModel);
}

bool EvolutionModel::variate() {
	//Enter the Variation phase
	mPhase = VARIATION_PHASE;

	//call the reaper to sow
	mReaper.sow(mPopulationModels[mCurrentPopulationIndex]);
	return true;
}

void EvolutionModel::update() {
	//TODO: Delete if it is not necessary.
}
