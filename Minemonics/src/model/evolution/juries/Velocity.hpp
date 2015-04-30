/*
 * Velocity.h
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

#ifndef VELOCITY_H_
#define VELOCITY_H_

//# corresponding headers
#include <model/evolution/juries/Jury.hpp>

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

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
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
