//# corresponding headers
#include <controller/EvaluationController.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/Universe.hpp>
#include <controller/SaveController.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/Evaluation.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger EvaluationController::mBoostLogger; /*<! initialize the boost logger*/
EvaluationController::_Init EvaluationController::_initializer;
EvaluationController::EvaluationController() :
	mCurrentlyRunningEvaluationsQty(0), mParallelEvaluationsQty(0), mPaused(
		false), mUniverse(NULL), mFails(0) {
}

EvaluationController::~EvaluationController() {
//	mCurrentlyRunningEvaluationsQty
	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end();) {
		Evaluation* evaluation = *eit;
		eit = mEvaluations.erase(eit);
		delete evaluation;
	}

	mUniverse = NULL;
//	mParallelEvaluationsQty
//	mPaused
}

void EvaluationController::initialize(Universe* const universe,
	int parallelEvaluationsQty) {
	mUniverse = universe;
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

			if ((*eit)->hasFailed()) {
				mFails += (*eit)->hasFailed();
				std::cout << "Fails: " << mFails << std::endl;
			}

			mCurrentlyRunningEvaluationsQty--;
			delete *eit;
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
			SimulationManager::getSingleton()->getViewController().setEvaluationInView(
				*eit);
		}
	}
}

void EvaluationController::update(const double timeSinceLastTick) {

	//breaks when there are no creatures on the planets to evaluate
	while (mEvaluations.size() < mParallelEvaluationsQty
		&& mUniverse->getTotalCreatureQty() != 0) {
		if (!mUniverse->proceedEvaluation()) {
			break;
		}
	}

	if (!mPaused) {
		std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		for (; eit != mEvaluations.end(); eit++) {
			if ((*eit)->isEvaluating()) {
				(*eit)->update(timeSinceLastTick);
			}
		}
	}
	scheduleEvaluations();
}
