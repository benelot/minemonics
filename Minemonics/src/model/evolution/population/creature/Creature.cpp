/*
 * Creature.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Creature.h"

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
#include "utils/NameGenerator.h"

Creature::Creature() :
		mDeveloped(false) {

}

void Creature::initialize(double bushiness) {
	Randomness randomness;
	NameGenerator nameGenerator;
	mName = nameGenerator.generateName();
	mGenotype.createRandomGenome(bushiness);
	//genotype.expand();
	mGenotype.linkRandomGenes();
}

Creature::~Creature() {
	while (!mJuries.empty()) {
		Jury* f = mJuries.back();
		mJuries.pop_back();
		delete f;
	}
}

bool Creature::equals(const Creature & creature) const {
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

