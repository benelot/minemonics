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
#include <controller/EvaluationController.hpp>

//## model headers
//## view headers
//## utils headers

EvaluationController::EvaluationController() :
		mCurrentlyRunningEvaluationsQty(0), mParallelEvaluationsQty(0), mPaused(
				false) {
	// TODO Auto-generated constructor stub

}

EvaluationController::~EvaluationController() {
	// TODO Auto-generated destructor stub
}

void EvaluationController::initialize(int parallelEvaluationsQty) {
	mParallelEvaluationsQty = parallelEvaluationsQty;
	mEvaluations.clear();
}

void EvaluationController::addEvaluation(Evaluation* evaluation) {
	mEvaluations.push_back(evaluation);
}

void EvaluationController::scheduleEvaluations() {
	std::vector<Evaluation*>::iterator eit;
	for (eit = mEvaluations.begin(); eit != mEvaluations.end();) {

		// erase torn down evaluations
		if ((*eit)->isTornDown()) {
			mCurrentlyRunningEvaluationsQty--;
			eit = mEvaluations.erase(eit);
		}
		else{
			eit++;
		}
	}

	for (eit = mEvaluations.begin(); eit != mEvaluations.end(); eit++) {

		//if the evaluation is newly scheduled, then set it up for evaluation
		if (!(*eit)->isEvaluating()
				&& mCurrentlyRunningEvaluationsQty < mParallelEvaluationsQty) {
			mCurrentlyRunningEvaluationsQty++;
			(*eit)->setup();
		}
	}
}

void EvaluationController::update(double timeSinceLastFrame) {
	if (!mPaused) {
		std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		for (; eit != mEvaluations.end(); eit++) {
			if ((*eit)->isEvaluating()) {
				(*eit)->update(timeSinceLastFrame);
			}
		}
	}
}
