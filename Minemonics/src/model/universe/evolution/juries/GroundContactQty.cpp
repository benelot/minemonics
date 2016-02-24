//# corresponding headers
#include <math.h>
#include <cmath>
#include <vector>

//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>
#include <model/universe/evolution/juries/GroundContactQty.hpp>
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

GroundContactQty::GroundContactQty() :
	Jury(Jury::AVG_HEIGHT, true, 1),mGroundContacts(0), mIsFirstTime(true), mSampleQty(
		0) {
}

GroundContactQty::GroundContactQty(const bool higherIsBetter, const double weight) :
	Jury(Jury::AVG_HEIGHT, higherIsBetter, weight), mIsFirstTime(true), mGroundContacts(
		0), mSampleQty(0) {

}

GroundContactQty::~GroundContactQty() {

}

void GroundContactQty::calculateFitness(CreatureModel* creature,
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

			mGroundContacts =
				(mHigherIsBetter) ? 0 : std::numeric_limits<double>::max();

		}
	}

	mIsFirstTime = false;

	mSampleQty++;
}

void GroundContactQty::evaluateFitness() {

	std::cout << "Ground Contact Quantity: " << mGroundContacts << std::endl;
	mFitness = mGroundContacts;
}

GroundContactQty* GroundContactQty::clone() {
	return new GroundContactQty(*this);
}

std::string GroundContactQty::getScoreString() {
	std::string scoreString = "Ground Contact Quantity : "
		+ boost::lexical_cast<std::string>(getFitness())
		+ ((isHigherBetter()) ?
			" (where higher is better)" : " (where lower is better)");
	return scoreString;
}
