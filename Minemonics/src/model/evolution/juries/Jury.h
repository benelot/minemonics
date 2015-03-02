/*
 * Jury.h
 *
 *  Created on: Dec 7, 2014
 *      Author: leviathan
 */

#ifndef JURY_H_
#define JURY_H_

//# corresponding header

//# forward declarations

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

class Jury {
public:
	enum JuryType {
		VELOCITY, ONES
	};

	Jury(JuryType juryType, int weight);
	virtual ~Jury();

	/**
	 * Returns the weight associated with this jury component.
	 * @return the weight
	 */
	double getWeight();

	/**
	 * Returns the fitness value that this jury assigns.
	 * @return the fitness value
	 */
	double getFitness();

	JuryType getJuryType();

	/**
	 * Calculates the fitness value at the end of the evaluation.
	 * Therefore it should be called when the evaluation ends.
	 */
	virtual void evaluateFitness() = 0;
private:
	JuryType mJuryType;
protected:
	double mWeight;
	double mFitness;
};

#endif /* JURY_H_ */
