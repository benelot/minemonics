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
	 * @param parallelEvaluationsQty The number of parallel evaluations running in the simulator.
	 */
	void initialize(int parallelEvaluationsQty);

	/**
	 * Add a new evaluation.
	 * @param evaluation The evaluation to add.
	 */
	void addEvaluation(Evaluation* evaluation);

	/**
	 * Schedule the evaluations, clear the torndown and setup new ones.
	 */
	void scheduleEvaluations();

	/**
	 * Update evaluated objects according to the time that has passed.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void update(double timeSinceLastFrame);


	//Accesssor methods

	void setPaused(bool paused) {
		mPaused = paused;
	}

	const bool isPaused() const {
		return mPaused;
	}

private:
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
};

#endif /* CONTROLLER_EVALUATIONCONTROLLER_HPP_ */
