#ifndef CONTROLLER_EVALUATIONCONTROLLER_HPP_
#define CONTROLLER_EVALUATIONCONTROLLER_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <controller/Evaluation.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>
//#include <utils/TimerManager.hpp>

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
	 * @param simulationManager Handle to the simulation manager.
	 * @param parallelEvaluationsQty The number of parallel evaluations running in the simulator.
	 */
	void initialize(SimulationManager* const simulationManager,const int parallelEvaluationsQty);

	/**
	 * Add a new evaluation.
	 * @param evaluation The evaluation to add.
	 */
	void addEvaluation(Evaluation* const evaluation);

	/**
	 * Schedule the evaluations, clear the torndown and setup new ones.
	 */
	void scheduleEvaluations();

	/**
	 * Update evaluated objects according to the time that has passed.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void update(const double timeSinceLastFrame);


	//Accessor methods

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
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

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

	std::vector<Evaluation*> mEvaluations;

	/**
	 * The currently running evaluations.
	 */
	int mCurrentlyRunningEvaluationsQty;

	/**
	 * Parallel evaluations.
	 */
	int mParallelEvaluationsQty;

	/**
	 * If the evaluation is paused or not.
	 */
	bool mPaused;

	//TODO: Use the timer manager to trigger proceeding.
//	TimerManager<EvaluationController> mEvaluationManager;

	/**
	 * The handler to the simulation manager.
	 */
	SimulationManager* mSimulationManager;
};

#endif /* CONTROLLER_EVALUATIONCONTROLLER_HPP_ */
