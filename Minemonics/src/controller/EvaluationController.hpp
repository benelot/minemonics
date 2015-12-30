#ifndef CONTROLLER_EVALUATIONCONTROLLER_HPP_
#define CONTROLLER_EVALUATIONCONTROLLER_HPP_

//# corresponding headers
//# forward declarations
class Universe;

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/Evaluation.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The evaluation controller schedules the evaluations for serial or parallel evaluation.
 * @details		Details
 * @date		2015-06-02
 * @author		Benjamin Ellenberger
 */
class EvaluationController {
public:
	EvaluationController();
	virtual ~EvaluationController();

	/**
	 * Initialize the evaluation controller.
	 * @param universe The universe the controller belongs to.
	 * @param parallelEvaluationsQty The number of parallel evaluations running in the simulator.
	 */
	void initialize(Universe* const universe, const int parallelEvaluationsQty);

	/**
	 * Add a new evaluation.
	 * @param evaluation The evaluation to add.
	 */
	void addEvaluation(Evaluation* const evaluation);

	/**
	 * Schedule the evaluations, clear the torn down and setup new ones.
	 */
	void scheduleEvaluations();

	/**
	 * Update evaluated objects according to the time that has passed.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void update(const double timeSinceLastFrame);

	void updateEvaluations(const double timeSinceLastTick);

	void pollNewEvaluations();

	// Accessor methods ##########################

	void setPaused(const bool paused) {
		mPaused = paused;
	}

	const bool isPaused() const {
		return mPaused;
	}

	const std::vector<Evaluation*>& getEvaluations() const {
		return mEvaluations;
	}

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"EvaluationController"));
		}
	} _initializer;

	std::vector<Evaluation*> mEvaluations; /**!< The evaluations in the evaluation controller. */

	int mCurrentlyRunningEvaluationsQty; /**!<The currently running evaluations. */

	int mParallelEvaluationsQty; /**!< Number of parallel evaluations. */

	bool mPaused; /**!< If the evaluation is paused or not. */

	Universe* mUniverse; /**!< The universe of the evaluations controller. */

	int mFails; /**!< The number of failed evaluations */
};

#endif /* CONTROLLER_EVALUATIONCONTROLLER_HPP_ */
