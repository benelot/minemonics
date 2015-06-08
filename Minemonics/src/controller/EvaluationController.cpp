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

EvaluationController::EvaluationController() {
	// TODO Auto-generated constructor stub

}

EvaluationController::~EvaluationController() {
	// TODO Auto-generated destructor stub
}

void EvaluationController::addEvaluation(Evaluation* evaluation) {
	mEvaluations.push_back(evaluation);
}

void EvaluationController::scheduleEvaluations() {
	std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
	for (; eit != mEvaluations.end(); eit++) {

		// erase torn down evaluations
		if((*eit)->isTornDown())
		{
			eit = mEvaluations.erase(eit);
		}

		//if the evaluation is newly scheduled, then set it up for evaluation
		if (!(*eit)->isEvaluating()) {
			(*eit)->setup();
		}
	}
}

void EvaluationController::update(double timeSinceLastFrame) {
	std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
	for (; eit != mEvaluations.end(); eit++) {
		if ((*eit)->isEvaluating()) {
			(*eit)->update(timeSinceLastFrame);
		}
	}
}
