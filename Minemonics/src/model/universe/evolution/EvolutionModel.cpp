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

		if (mCurrentCreatureIndex < mPopulationModels[mCurrentPopulationIndex]->getCreatureModels().size()) {
			mCurrentCreatureIndex++;
		}
		else{
			mCurrentPopulationIndex++;
			mCurrentCreatureIndex = 0;
		}
	}
	else{
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
//PROCESSING
	mPhase = PROCESSING_PHASE;

	return true;
}

bool EvolutionModel::cull() {
//REAP_AND_SOW
	mPhase = CULLING_PHASE;

//call the reaper to reap
	mReaper.reap(mPopulationModels[mCurrentPopulationIndex]);

	return true;
}

void EvolutionModel::addNewPopulation(PopulationModel* populationModel) {
	mPopulationModels.push_back(populationModel);
}

bool EvolutionModel::variate() {
	//VARIATION
	mPhase = VARIATION_PHASE;

	//call the reaper to sow
	mReaper.sow(mPopulationModels[mCurrentPopulationIndex]);
	return true;
}

void EvolutionModel::update() {

}
