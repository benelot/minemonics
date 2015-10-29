//# corresponding header
#include <model/universe/evolution/juries/AverageVelocity.hpp>

//##system headers
#include <cmath>
#include <vector>
#include <math.h>

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

BoostLogger AverageVelocity::mBoostLogger; /*<! initialize the boost logger*/
AverageVelocity::_Init AverageVelocity::_initializer;
AverageVelocity::AverageVelocity() :
	Jury(Jury::AVG_VELOCITY, true, 1), mIsFirstTime(true), mAvgVelocity(0), mTimestamp(
		0), mTotalMovement(0, 0, 0) {
}

AverageVelocity::AverageVelocity(const bool higherIsBetter, double weight) :
	Jury(Jury::AVG_VELOCITY, higherIsBetter, weight), mIsFirstTime(true), mAvgVelocity(
		0), mTimestamp(0), mTotalMovement(0, 0, 0) {
}

AverageVelocity::~AverageVelocity() {
//	mAvgVelocity
//	mFitness
//	mJuryType
//	mTimestamp
//	mWeight
	mInitialCoords.clear();
}

void AverageVelocity::calculateFitness(CreatureModel* creature,
	double timeSinceLastTick) {

	if (mIsFirstTime) { // if the fitness is calculated the first time, we store all the positions of the limbs
		int i = 0;
		for (std::vector<LimbModel*>::iterator lit =
			creature->getPhenotypeModel()->getLimbModels().begin();
			lit != creature->getPhenotypeModel()->getLimbModels().end();
			lit++, i++) {
			mInitialCoords.push_back((*lit)->getPosition());
		}
		mIsFirstTime = false;
	}

	int i = 0;
	Ogre::Vector3 totalMovement = Ogre::Vector3::ZERO;
	double totalVolume = 0;
	int segmentQty = 0;
	for (std::vector<LimbModel*>::iterator lit = // we calculate the difference between the limb's position and its initial position
		creature->getPhenotypeModel()->getLimbModels().begin();
		lit != creature->getPhenotypeModel()->getLimbModels().end();
		lit++, i++) {
		totalMovement += (*lit)->getPosition() - mInitialCoords[i];
		totalVolume += (*lit)->getVolume(); // we take the volume into account when we calculate the travelled distance
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
		mTotalMovement = totalMovement / totalVolume;
	}

	mTimestamp += timeSinceLastTick;
}

Ogre::Vector3 AverageVelocity::getDistanceVector(const double x1,
	const double x2, const double y1, const double y2, const double z1,
	const double z2) {

	return Ogre::Vector3(x2 - x1, y2 - y1, z2 - z1);
}

double AverageVelocity::calculateDistance(const double x1, const double x2,
	const double y1, const double y2, const double z1, const double z2,
	const float diffTime) {
//faster distance
	double distance = pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2);
//	double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
	return distance / ((double) diffTime);
}

void AverageVelocity::evaluateFitness() {
	if (mTimestamp != 0) {
		mAvgVelocity = mTotalMovement.squaredLength() / mTimestamp;
	} else {
		mAvgVelocity = 0;
	}
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Average Velocity Fitness: " << mAvgVelocity;
	mFitness = mAvgVelocity;
}

AverageVelocity * AverageVelocity::clone() {
	return new AverageVelocity(*this);
}
