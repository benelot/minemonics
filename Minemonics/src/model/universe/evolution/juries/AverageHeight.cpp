//# corresponding headers
#include <model/universe/evolution/juries/AverageHeight.hpp>

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

AverageHeight::AverageHeight() :
Jury(Jury::AVG_HEIGHT, true, 1), mIsFirstTime(true), mAvgHeight(0), mSampleQty(
0) {
}

AverageHeight::AverageHeight(const bool higherIsBetter, const double weight) :
Jury(Jury::AVG_HEIGHT, higherIsBetter, weight), mIsFirstTime(true), mAvgHeight(
0), mSampleQty(0) {

}

AverageHeight::~AverageHeight() {

}

void AverageHeight::calculateFitness(CreatureModel* creature,
double timeSinceLastTick) {

	if (!mIsFirstTime) {
		int i = 0;
		double currentAvgHeight = 0;
		double totalVolume = 0;
		int segmentQty = 0;
		for (std::vector<LimbModel*>::iterator lit =
		creature->getPhenotypeModel().getLimbModels().begin();
		lit != creature->getPhenotypeModel().getLimbModels().end();
		lit++, i++) {
			currentAvgHeight += (*lit)->getVolume() * ((*lit)->getPosition().y);
			totalVolume += (*lit)->getVolume();
			segmentQty++;
		}
		if (totalVolume == 0 || segmentQty == 1) {

			mAvgHeight =
			(mHigherIsBetter) ? 0 : std::numeric_limits<double>::max();

		} else {
			mAvgHeight = ((mAvgHeight * mSampleQty)
			+ currentAvgHeight / totalVolume) / (mSampleQty + 1);
		}
	}

	mIsFirstTime = false;

	mSampleQty++;
}

void AverageHeight::evaluateFitness() {

	std::cout << "Average Height Fitness: " << mAvgHeight << std::endl;
	mFitness = mAvgHeight;
}

AverageHeight* AverageHeight::clone() {
	return new AverageHeight(*this);
}
