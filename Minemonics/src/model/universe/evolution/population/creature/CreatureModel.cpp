//# corresponding headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

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
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//## utils headers
#include <utils/NameGenerator.hpp>
#include <utils/Randomness.hpp>

CreatureModel::CreatureModel() :
		mDeveloped(false),mPopulationModel(NULL) {

}

void CreatureModel::initialize(PopulationModel* populationModel,Ogre::Vector3 position,double branchiness) {
	mPopulationModel = populationModel;
	mPosition = position;
	Randomness randomness;
	NameGenerator nameGenerator;
	mName = nameGenerator.generateName();
	mGenotype.createRandomGenome(branchiness);
	//genotype.expand();
}

CreatureModel::~CreatureModel() {
	while (!mJuries.empty()) {
		Jury* f = mJuries.back();
		mJuries.pop_back();
		delete f;
	}
}

bool CreatureModel::equals(const CreatureModel & creature) const {
	if (mName != creature.mName) {
		return false;
	}

	if (mDeveloped != creature.mDeveloped) {
		return false;
	}

	if (!mGenotype.equals(creature.mGenotype)) {
		return false;
	}

//	std::vector<Jury>::const_iterator it = mJuries.begin();
//	std::vector<Jury>::const_iterator it2 =
//			creature.mJuries.begin();
//	for (; it != mJuries.end(), it2 != creature.mJuries.end();
//			it++, it2++) {
	//TODO:: Add equals for juries
//		if (!it->equals(*(it2))) {
//			return false;
//		}
//	}

//	if (mSegmentsDepthLimit != creature.mSegmentsDepthLimit) {
//		return false;
//	}
//
//	if (mTotalSegmentQtyLimit != creature.mTotalSegmentQtyLimit) {
//		return false;
//	}

	return true;
}

void CreatureModel::evaluate() {
	//TODO: Add creature to world
	//TODO: Add it somewhere so that it updates the creature
}
