/*
 * Reaper.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

//# corresponding header
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/Reaper.hpp>

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

Reaper::Reaper() :
		mAttributeMutationPercentage(0), mBranchAttributeMutationPercentage(0), mBranchMutationPercentage(
				0), mCrossOverPercentage(0), mGeneMutationPercentage(
				0), mReapPercentage(0), mSowFreshPercentage(0) {
}

Reaper::~Reaper() {
	// TODO Auto-generated destructor stub
}

void Reaper::initialize(double reapPercentage, double crossOverPercentage,
		double geneMutationPercentage, double attributeMutationPercentage,
		double branchMutationPercentage,
		double branchAttributeMutationPercentage, double sowFreshPercentage) {
	mReapPercentage = reapPercentage;
	mCrossOverPercentage = crossOverPercentage;
	mGeneMutationPercentage = geneMutationPercentage;
	mAttributeMutationPercentage = attributeMutationPercentage;
	mBranchMutationPercentage = branchMutationPercentage;
	mBranchAttributeMutationPercentage = branchAttributeMutationPercentage;
	mSowFreshPercentage = sowFreshPercentage;
}

void Reaper::reap(PopulationModel* population) {
}

void Reaper::sow(PopulationModel* population) {
}
