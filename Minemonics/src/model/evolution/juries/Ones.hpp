/*
 * Ones.h
 *
 *  Created on: Feb 25, 2015
 *      Author: leviathan
 */

#ifndef ONES_H_
#define ONES_H_

//# corresponding header
#include <model/evolution/juries/Jury.hpp>
#include <vector>

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

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Ones: public Jury {
public:
	Ones(double weight);
	virtual ~Ones();

	void setEvaluationSubject(const std::vector< bool >& x);
	void evaluateFitness();
private:
	std::vector< bool > mEvaluationSubject;
};

#endif /* ONES_H_ */
