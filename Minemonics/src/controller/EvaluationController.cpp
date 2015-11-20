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
	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end();) {

		if ((*eit)->isTornDown()) { /**!< erase torn down evaluations */

			if ((*eit)->hasFailed()) {
				mFails += (*eit)->hasFailed();
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Fails: " << mFails;
			}

			mCurrentlyRunningEvaluationsQty--;
			delete *eit;
			eit = mEvaluations.erase(eit);
		} else {
			eit++;
		}
	}

	for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
		eit != mEvaluations.end(); eit++) {

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

void EvaluationController::update(const double timeSinceLastTick) {

	if (!mPaused) { /**!< if the simulator is not paused, we update all evaluations that are in the loop */
		for (std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
			eit != mEvaluations.end(); eit++) {
			if ((*eit)->isEvaluating()) { /**!< if the evaluation is running */
				(*eit)->update(timeSinceLastTick); /**!< update the evaluation */
			}
		}
	}

	scheduleEvaluations(); /**!< setup new evaluations and tear down the old ones */

	while (mEvaluations.size() < mParallelEvaluationsQty /**!< if there are not enough evaluations evaluating */
	&& mUniverse->getTotalCreatureQty() != 0) { /**!< if the universe has creatures in it */
		if (!mUniverse->proceedEvaluation()) { /**!< we proceed the evaluation until it says it can not continue anymore */
			break;
		}
	}
}
