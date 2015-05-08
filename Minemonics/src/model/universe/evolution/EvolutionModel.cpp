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
		mState(GENERATION), mType(INDIVIDUAL_EVALUATION), mEvaluationTime(0) {

}

EvolutionModel::~EvolutionModel() {

}

void EvolutionModel::initialize(double evaluationTime) {
	mEvaluationTime = evaluationTime;
}

bool EvolutionModel::evaluate() {
	// run creature evaluation according to the evolution type and then return true
}

bool EvolutionModel::selectAndReap(){
	//call the reaper to reap
}

bool EvolutionModel::evolve() {
	//mutate creatures
	//cross over creatures
}
