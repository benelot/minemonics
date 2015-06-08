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

	void addEvaluation(Evaluation* evaluation);

	void scheduleEvaluations();

	void update(double timeSinceLastFrame);

private:
	std::vector<Evaluation*> mEvaluations;
};

#endif /* CONTROLLER_EVALUATIONCONTROLLER_HPP_ */
