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
		mState(VARIATION), mType(INDIVIDUAL_EVALUATION), mEvaluationTime(0), mCurrentPopulationIndex(
				0) {

}

EvolutionModel::~EvolutionModel() {

}

void EvolutionModel::initialize(double evaluationTime) {
	mEvaluationTime = evaluationTime;

	//GENERATION
}

bool EvolutionModel::proceedEvaluation() {

	if (mPopulationModels.size() != 0) {
		if (mCurrentPopulationIndex < mPopulationModels.size()) {
			if (!mPopulationModels[mCurrentPopulationIndex]->proceedEvaluation()) {
				mCurrentPopulationIndex =
						(mCurrentPopulationIndex < mPopulationModels.size()) ?
								mCurrentPopulationIndex + 1 : 0;
				if(mCurrentPopulationIndex != 0)
				{
					return true;
				}
			}
			else{
				return true;
			}
		}
	}

	//PROCESSING
	process();

	//REAP AND SOW
	selectAndReap();
	variate();

	return false;
}

bool EvolutionModel::evaluate() {
	//EVALUATION
	mState = EVALUATION;

	// run creature evaluation according to the evolution type and then return true

	return true;
}

bool EvolutionModel::process() {
	//PROCESSING
	mState = PROCESSING;

	return true;
}

bool EvolutionModel::selectAndReap() {
	//REAP_AND_SOW
	mState = REAP_AND_SOW;

	//call the reaper to reap
	mReaper.reap(mPopulationModels[mCurrentPopulationIndex]);

	//call the reaper to sow
	mReaper.sow(mPopulationModels[mCurrentPopulationIndex]);

	return true;
}

void EvolutionModel::addNewPopulation(PopulationModel* populationModel) {
	mPopulationModels.push_back(populationModel);
}

bool EvolutionModel::variate() {
	//VARIATION
	mState = VARIATION;

	//mutate creatures
	//cross over creatures

	return true;
}
