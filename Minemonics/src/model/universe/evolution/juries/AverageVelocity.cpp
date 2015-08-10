//# corresponding header
#include <model/universe/evolution/juries/AverageVelocity.hpp>

//# forward declarations
//## system headers
#include <math.h>
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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>

//## view headers
//## utils headers

AverageVelocity::AverageVelocity(double weight) :
		Jury(Jury::AVG_VELOCITY, weight), mIsFirstTime(true), mAvgVelocity(0), mTimestamp(
				0), mSampleQty(0), mLastX(NULL), mLastY(NULL), mLastZ(NULL), mCreatureLimbQty(
				0) {

}

AverageVelocity::~AverageVelocity() {
//	mAvgVelocity
//	mFitness
//	mIsFirstTime
//	mJuryType
//	mSampleQty
//	mTimestamp
//	mWeight
	delete[] mLastX;
	mLastX = NULL;
	delete[] mLastY;
	mLastY = NULL;
	delete[] mLastZ;
	mLastZ = NULL;
}

void AverageVelocity::calculateFitness(CreatureModel* creature,
		double timeSinceLastTick) {
	if (mIsFirstTime) {
		mCreatureLimbQty = creature->getPhenotypeModel().getLimbModels().size();
		mLastX = new double[mCreatureLimbQty];
		mLastY = new double[mCreatureLimbQty];
		mLastZ = new double[mCreatureLimbQty];
		int i = 0;
		for (std::vector<LimbModel*>::iterator lit =
				creature->getPhenotypeModel().getLimbModels().begin();
				lit != creature->getPhenotypeModel().getLimbModels().end();
				lit++, i++) {
			mLastX[i] = (*lit)->getPosition().x;
			mLastY[i] = (*lit)->getPosition().y;
			mLastZ[i] = (*lit)->getPosition().z;
		}
		mIsFirstTime = false;
	} else {

		int i = 0;
		Ogre::Vector3 totalMovement = Ogre::Vector3::ZERO;
		double totalVolume = 0;
		for (std::vector<LimbModel*>::iterator lit =
				creature->getPhenotypeModel().getLimbModels().begin();
				lit != creature->getPhenotypeModel().getLimbModels().end();
				lit++, i++) {
			totalMovement += (*lit)->getVolume()
					* getDistanceVector((*lit)->getPosition().x, mLastX[i],
							(*lit)->getPosition().y, mLastY[i],
							(*lit)->getPosition().z, mLastZ[i]);
			totalVolume += (*lit)->getVolume();
		}
		if(totalVolume == 0){
			mTotalMovement = 0;
		}
		else{
			mTotalMovement += totalMovement / totalVolume;
		}



	}

	int i = 0;
	for (std::vector<LimbModel*>::iterator lit =
			creature->getPhenotypeModel().getLimbModels().begin();
			lit != creature->getPhenotypeModel().getLimbModels().end();
			lit++, i++) {
		mLastX[i] = (*lit)->getPosition().x;
		mLastY[i] = (*lit)->getPosition().y;
		mLastZ[i] = (*lit)->getPosition().z;
	}
	mTimestamp += timeSinceLastTick;
	mSampleQty++;
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
	mAvgVelocity = mTotalMovement.squaredLength() / mTimestamp;
	std::cout << "Fitness: " << mAvgVelocity << std::endl;
	mFitness = mAvgVelocity;
}

AverageVelocity* AverageVelocity::clone() {
	return new AverageVelocity(*this);
}
