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
#include <controller/EvaluationController.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger EvaluationController::mBoostLogger; /*<! initialize the boost logger*/
EvaluationController::_Init EvaluationController::_initializer;
EvaluationController::EvaluationController() : mCurrentlyRunningEvaluationsQty(0), mParallelEvaluationsQty(
				0), mPaused(false) {
}

EvaluationController::~EvaluationController() {
//	mCurrentlyRunningEvaluationsQty
	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
			eit != mEvaluations.end();) {
		Evaluation* evaluation = *eit;
		eit = mEvaluations.erase(eit);
		delete evaluation;
	}
//	mParallelEvaluationsQty
//	mPaused
}

void EvaluationController::initialize(SimulationManager* const simulationManager,
		int parallelEvaluationsQty) {
	mParallelEvaluationsQty = parallelEvaluationsQty;
	mEvaluations.clear();
}

void EvaluationController::addEvaluation(Evaluation* const evaluation) {
	mEvaluations.push_back(evaluation);
}

void EvaluationController::scheduleEvaluations() {
	std::vector<Evaluation*>::iterator eit;
	for (eit = mEvaluations.begin(); eit != mEvaluations.end();) {

		// erase torn down evaluations
		if ((*eit)->isTornDown()) {
			mCurrentlyRunningEvaluationsQty--;
			eit = mEvaluations.erase(eit);
		} else {
			eit++;
		}
	}

	for (eit = mEvaluations.begin(); eit != mEvaluations.end(); eit++) {

		//if the evaluation is newly scheduled, then set it up for evaluation
		if (!(*eit)->isEvaluating()
				&& mCurrentlyRunningEvaluationsQty < mParallelEvaluationsQty) {
			mCurrentlyRunningEvaluationsQty++;
			(*eit)->setup();
			SimulationManager::getSingleton()->getViewController().setEvaluationInView(*eit);
		}
	}
}

void EvaluationController::update(const double timeSinceLastFrame) {
	if (!mPaused) {
		std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		for (; eit != mEvaluations.end(); eit++) {
			if ((*eit)->isEvaluating()) {
				(*eit)->update(timeSinceLastFrame);
			}
		}
	}
}
