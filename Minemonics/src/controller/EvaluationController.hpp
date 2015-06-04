/*
 * EvaluationController.hpp
 *
 *  Created on: Jun 2, 2015
 *      Author: leviathan
 */

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

/*
 *
 */
class EvaluationController {
public:
	EvaluationController();
	virtual ~EvaluationController();

	void addEvaluation(Evaluation* evaluation);

	void evaluate();

private:
	std::vector<Evaluation*> mEvaluations;
};

#endif /* CONTROLLER_EVALUATIONCONTROLLER_HPP_ */
