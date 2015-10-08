//# corresponding header
#include <math.h>
#include <model/universe/evolution/juries/IntegralAverageVelocity.hpp>
#include <cmath>
#include <vector>

//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

IntegralAverageVelocity::IntegralAverageVelocity() :
	Jury(Jury::AVG_VELOCITY, true, 1), mIsFirstTime(true), mAvgVelocity(0), mTimestamp(
		0), mSampleQty(0), mCreatureLimbQty(0), mTotalMovement(0, 0, 0) {
}

IntegralAverageVelocity::IntegralAverageVelocity(const bool higherIsBetter,
	double weight) :
	Jury(Jury::AVG_VELOCITY, higherIsBetter, weight), mIsFirstTime(true), mAvgVelocity(
		0), mTimestamp(0), mSampleQty(0), mCreatureLimbQty(0), mTotalMovement(0,
		0, 0) {
}

IntegralAverageVelocity::~IntegralAverageVelocity() {
//	mAvgVelocity
//	mFitness
//	mJuryType
//	mSampleQty
//	mTimestamp
//	mWeight
	mLastCoords.clear();
}

void IntegralAverageVelocity::calculateFitness(CreatureModel* creature,
	double timeSinceLastTick) {

	if (!mIsFirstTime) {

		int i = 0;
		Ogre::Vector3 totalMovement = Ogre::Vector3::ZERO;
		double totalVolume = 0;
		int segmentQty = 0;
		for (std::vector<LimbModel*>::iterator lit =
			creature->getPhenotypeModel()->getLimbModels().begin();
			lit != creature->getPhenotypeModel()->getLimbModels().end();
			lit++, i++) {
			totalMovement += (*lit)->getVolume()
				* ((*lit)->getPosition() - mLastCoords[i]);
			totalVolume += (*lit)->getVolume();
			segmentQty++;
		}
		if (totalVolume == 0 || segmentQty == 1) {

			mTotalMovement =
				(mHigherIsBetter) ?
					Ogre::Vector3::ZERO :
					Ogre::Vector3(std::numeric_limits<double>::max(),
						std::numeric_limits<double>::max(),
						std::numeric_limits<double>::max());
		} else {
			mTotalMovement += totalMovement / totalVolume;
		}

	}

	int i = 0;
	for (std::vector<LimbModel*>::iterator lit =
		creature->getPhenotypeModel()->getLimbModels().begin();
		lit != creature->getPhenotypeModel()->getLimbModels().end();
		lit++, i++) {
		if (mIsFirstTime) {

			mLastCoords.push_back((*lit)->getPosition());
		} else {
			mLastCoords[i] = (*lit)->getPosition();
		}
	}
	mTimestamp += timeSinceLastTick;
	mIsFirstTime = false;
	mSampleQty++;
}

Ogre::Vector3 IntegralAverageVelocity::getDistanceVector(const double x1,
	const double x2, const double y1, const double y2, const double z1,
	const double z2) {

	return Ogre::Vector3(x2 - x1, y2 - y1, z2 - z1);
}

double IntegralAverageVelocity::calculateDistance(const double x1,
	const double x2, const double y1, const double y2, const double z1,
	const double z2, const float diffTime) {
//faster distance
	double distance = pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2);
//	double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
	return distance / ((double) diffTime);
}

void IntegralAverageVelocity::evaluateFitness() {
	if (mTimestamp != 0) {
		mAvgVelocity = mTotalMovement.squaredLength() / mTimestamp;
	} else {
		mAvgVelocity = 0;
	}
	std::cout << "Average Velocity Fitness: " << mAvgVelocity << std::endl;
	mFitness = mAvgVelocity;
}

IntegralAverageVelocity * IntegralAverageVelocity::clone() {
	return new IntegralAverageVelocity(*this);
}
