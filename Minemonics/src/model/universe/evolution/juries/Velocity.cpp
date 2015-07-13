//# corresponding header
#include <model/universe/evolution/juries/Velocity.hpp>

//# forward declarations
//# system headers
#include <math.h>

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
//	mAvgVelocity
//	mFitness
//	mIsFirstTime
//	mJuryType
//	mSampleQty
//	mTimestamp
//	mWeight
//	mX
//	mY
//	mZ
}

// the continuously called function
void Velocity::calculateAvgVelocity(const double x2, const double y2,
		const double z2, const float diffTime) {
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

Velocity* Velocity::clone() {
	return new Velocity(*this);
}
