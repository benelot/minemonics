/*
 * Velocity.h
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

#ifndef VELOCITY_H_
#define VELOCITY_H_

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
#include "Jury.h"

//## view headers

//## utils headers

class Velocity: public Jury {
public:
	Velocity(double weight);
	virtual ~Velocity();

	void calculateAvgVelocity(double x2, double y2, double z2, float diffTime);
	void evaluateFitness();

private:
	double mAvgVelocity;

	double mX, mY, mZ;
	float mTimestamp;
	int mSampleQty;
	bool mIsFirstTime;
};

#endif /* VELOCITY_H_ */
