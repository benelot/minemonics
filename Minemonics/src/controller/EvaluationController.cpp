//# corresponding headers
#include <controller/EvaluationController.hpp>

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
#include <controller/universe/Universe.hpp>

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
		eit != mEvaluations.end(); eit++) {
		delete (*eit);
	}
	mEvaluations.clear();

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

void EvaluationController::update(const double timeSinceLastTick) {
	updateEvaluations(timeSinceLastTick); /**!< We update all evaluations that are in the loop */

	scheduleEvaluations(); /**!< Setup new evaluations and tear down the old ones. */

	pollNewEvaluations(); /**!< Add new evaluations from the universe if we run out of evaluations. */
}

void EvaluationController::updateEvaluations(const double timeSinceLastTick) {
	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end(); eit++) { /**!< We update all evaluations that are in the loop */
		if ((*eit)->isEvaluating()) { /**!< if the evaluation is running */
			(*eit)->update(timeSinceLastTick); /**!< update the evaluation */
		}
	}
}

void EvaluationController::scheduleEvaluations() {
	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end();) {

		if ((*eit)->isTornDown()) { /**!< erase torn down evaluations */

			if ((*eit)->hasFailed()) {
				mFails += (*eit)->hasFailed();
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Fails: " << mFails;
			}

			mCurrentlyRunningEvaluationsQty--;
			delete *eit;
			eit = mEvaluations.erase(eit);
		} else {
			eit++;
		}
	}

	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end(); eit++) { /**!< Setup the new evaluations */

		/** If the evaluation is newly scheduled, then set it up for evaluation */
		if (!(*eit)->isEvaluating()
			&& mCurrentlyRunningEvaluationsQty < mParallelEvaluationsQty) {
			mCurrentlyRunningEvaluationsQty++;
			(*eit)->setup();
			SimulationManager::getSingleton()->getViewController().setEvaluationInView(
				*eit);
		}
	}
}

void EvaluationController::pollNewEvaluations() {
	while (mEvaluations.size() < mParallelEvaluationsQty /**!< if there are not enough evaluations evaluating */
	&& mUniverse->getTotalCreatureQty() != 0) { /**!< if the universe has creatures in it */
		if (!mUniverse->proceedEvaluation()) { /**!< we proceed the evaluation until it says it can not continue anymore */
			break;
		}
	}
}
