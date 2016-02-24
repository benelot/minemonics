//# corresponding headers
#include <math.h>
#include <cmath>
#include <vector>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <model/universe/evolution/juries/GroundContactRatio.hpp>
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
#include <utils/MathUtils.hpp>

GroundContactRatio::GroundContactRatio() :
	Jury(Jury::AVG_HEIGHT, true, 1),mGroundContacts(0), mIsFirstTime(true), mSampleQty(
		0),mGroundContactRatio(0) {
}

GroundContactRatio::GroundContactRatio(const bool higherIsBetter, const double weight) :
	Jury(Jury::AVG_HEIGHT, higherIsBetter, weight), mIsFirstTime(true), mGroundContacts(
		0), mSampleQty(0),mGroundContactRatio(0) {

}

GroundContactRatio::~GroundContactRatio() {

}

void GroundContactRatio::calculateFitness(CreatureModel* creature,
	double timeSinceLastTick) {

	if (!mIsFirstTime) {
		int i = 0;
		double totalVolume = 0;
		int segmentQty = 0;
		mGroundContacts = 0;
		for (std::vector<LimbModel*>::iterator lit =
			creature->getPhenotypeModel()->getLimbModels().begin();
			lit != creature->getPhenotypeModel()->getLimbModels().end();
			lit++, i++) {
			if (MathUtils::isFinite((*lit)->getPosition())) {
				mGroundContacts += (*lit)->hadGroundContact();
				segmentQty++;
				totalVolume += (*lit)->getVolume();
			}
		}
		if (totalVolume == 0 || segmentQty == 1) {

			mGroundContactRatio =
				(mHigherIsBetter) ? 0 : std::numeric_limits<double>::max();

		} else {
			mGroundContactRatio = ((double)mGroundContacts)/((double)segmentQty);
		}
	}

	mIsFirstTime = false;

	mSampleQty++;
}

void GroundContactRatio::evaluateFitness() {

	std::cout << "Ground Contact Quantity: " << mGroundContactRatio << std::endl;
	mFitness = mGroundContactRatio;
}

GroundContactRatio* GroundContactRatio::clone() {
	return new GroundContactRatio(*this);
}

std::string GroundContactRatio::getScoreString() {
	std::string scoreString = "Ground Contact Quantity : "
		+ boost::lexical_cast<std::string>(getFitness())
		+ ((isHigherBetter()) ?
			" (where higher is better)" : " (where lower is better)");
	return scoreString;
}
