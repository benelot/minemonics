/*
 * Velocity.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <math.h>
#include <model/evolution/juries/Velocity.hpp>

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

Velocity::Velocity(double weight) :
		Jury(Jury::VELOCITY, weight), mIsFirstTime(true), mAvgVelocity(0), mX(
				0), mY(0), mZ(0), mTimestamp(0), mSampleQty(0) {

}

Velocity::~Velocity() {
	// TODO Auto-generated destructor stub
}

// the continuously called function
void Velocity::calculateAvgVelocity(double x2, double y2, double z2,
		float diffTime) {
	if (!mIsFirstTime) {
		double distance = sqrt(
				pow(x2 - mX, 2) + pow(y2 - mY, 2) + pow(z2 - mZ, 2));

		// continuous average avg = oldAvg * sampleQty + velocity/(sampleQty+1)
		mAvgVelocity = (mAvgVelocity * mSampleQty
				+ distance / ((double) diffTime)) / (mSampleQty + 1);
		mSampleQty++;
	}

	// update position
	mX = x2;
	mY = y2;
	mZ = z2;
	mIsFirstTime = false;
}

void Velocity::evaluateFitness() {
	mFitness = mAvgVelocity;
}

