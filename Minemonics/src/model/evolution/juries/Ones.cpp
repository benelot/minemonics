//# corresponding header
#include <model/evolution/juries/Ones.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

Ones::Ones(double weight) :
		Jury(Jury::ONES, weight) {

}

Ones::~Ones() {
}

void Ones::setEvaluationSubject(const std::vector<bool>& x) {
	mEvaluationSubject = x;
}

/**
 * fitness function for the counting ones problem
 */
void Ones::evaluateFitness() {
	unsigned i;
	for (mFitness = 0., i = 0; i < mEvaluationSubject.size(); mFitness +=
			mEvaluationSubject[i++])
		;
}

