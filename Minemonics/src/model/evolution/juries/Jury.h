/*
 * Jury.h
 *
 *  Created on: Dec 7, 2014
 *      Author: leviathan
 */

#ifndef JURY_H_
#define JURY_H_

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
	void evaluateFitness();
private:
	JuryType mJuryType;
protected:
	double mWeight;
	double mFitness;
};

#endif /* JURY_H_ */
