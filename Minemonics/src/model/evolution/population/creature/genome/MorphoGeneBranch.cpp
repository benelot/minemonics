/*
 * MorphoGeneBranch.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "MorphoGeneBranch.h"

//# forward declarations

//# system headers
//## controller headers

//## model headers
#include <boost/math/constants/constants.hpp>
#include <model/evolution/population/creature/genome/MorphoGene.h>
//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers
#include "utils/Randomness.h"

MorphoGeneBranch::MorphoGeneBranch() {

}

void MorphoGeneBranch::initialize() {
	Randomness randomness;

	/* Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached.*/
	do {
		mJointAnchorX = randomness.nextDouble(0, 1);
		mJointAnchorY = randomness.nextDouble(0, 1);
		mJointAnchorZ = randomness.nextDouble(0, 1);
	} while (mJointAnchorX == 0 && mJointAnchorY == 0 && mJointAnchorZ == 0);

	/*
	 * The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	 */
	mJointYaw = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitch = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRoll = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());

	/*
	 * Set if the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = randomness.nextBoolean();

	mFlipped = randomness.nextBoolean();

	mActive = randomness.nextBoolean();

	mBranchGeneType = -1;
}

MorphoGeneBranch::~MorphoGeneBranch() {
	// TODO Auto-generated destructor stub
}

bool MorphoGeneBranch::equals(const MorphoGeneBranch& geneBranch) {
	if (mActive != geneBranch.mActive) {
		return false;
	}

	if(mBranchGeneType != geneBranch.mBranchGeneType)
		return false;

	if(mFlipped != geneBranch.mFlipped)
		return false;

	if(mJointAnchorX != geneBranch.mJointAnchorX)
		return false;

	if(mJointAnchorY != geneBranch.mJointAnchorY)
		return false;

	if(mJointAnchorZ != geneBranch.mJointAnchorZ)
		return false;

	if(mJointPitch != geneBranch.mJointPitch)
		return false;

	if(mJointYaw != geneBranch.mJointYaw)
		return false;

	if(mJointRoll != geneBranch.mJointRoll)
		return false;

	if(mMirrored != geneBranch.mMirrored)
		return false;

	return true;
}

