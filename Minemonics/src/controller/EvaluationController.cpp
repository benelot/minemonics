/*
 * EvaluationController.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: leviathan
 */

#include <controller/EvaluationController.hpp>

EvaluationController::EvaluationController() {
	// TODO Auto-generated constructor stub

}

EvaluationController::~EvaluationController() {
	// TODO Auto-generated destructor stub
}

void EvaluationController::addEvaluation(Evaluation* evaluation) {
	mEvaluations.push_back(evaluation);
}

void EvaluationController::evaluate() {
	std::vector<Evaluation*>::iterator eit = mEvaluations.begin();
	for(;eit != mEvaluations.end();eit++){
		(*eit)->runEvaluation();
	}
}
