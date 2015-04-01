/*
 * MorphoGeneBranch.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "MorphogeneBranch.h"

//# forward declarations
class Morphogene;

//# system headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include "model/evolution/population/creature/genome/morphology/Morphogene.h"

//## view headers
//## utils headers
#include "utils/Randomness.h"

MorphogeneBranch::MorphogeneBranch() :
		mActive(false), mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(
				0), mJointAnchorZ(0), mJointPitch(0), mJointYaw(0), mJointRoll(
				0), mActuated(false), mJointPitchMinAngle(0), mJointPitchMaxAngle(
				0), mJointYawMinAngle(0), mJointYawMaxAngle(0), mJointRollMinAngle(
				0), mJointRollMaxAngle(0), mMirrored(0) {

}

void MorphogeneBranch::initialize() {
	GeneBranch::initialize(GeneBranch::MORPHOGENE_BRANCH);

	Randomness randomness;

	/** Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached.*/
	do {
		mJointAnchorX = randomness.nextDouble(0, 1);
		mJointAnchorY = randomness.nextDouble(0, 1);
		mJointAnchorZ = randomness.nextDouble(0, 1);
	} while (mJointAnchorX == 0 && mJointAnchorY == 0 && mJointAnchorZ == 0);

	/**
	 * The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	 */
	mJointYaw = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitch = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRoll = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());

	/**
	 * The joint limits in each direction (pitch,yaw, roll)
	 */
	mJointPitchMinAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitchMaxAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointYawMinAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointYawMaxAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRollMinAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRollMaxAngle = randomness.nextDouble(0,
			2 * boost::math::constants::pi<double>());

	/**
	 * Set if the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = randomness.nextBoolean();

	mFlipped = randomness.nextBoolean();

	mActive = randomness.nextBoolean();

	mActuated = randomness.nextBoolean();

	mBranchGeneType = -1;
}

MorphogeneBranch::~MorphogeneBranch() {
	//TODO:Remove test action
	mActive = false;
}

bool MorphogeneBranch::equals(const MorphogeneBranch& geneBranch) const {

	if (mActive != geneBranch.mActive) {
		return false;
	}

	if (mBranchGeneType != geneBranch.mBranchGeneType)
		return false;

	if (mFlipped != geneBranch.mFlipped)
		return false;

	if (mJointAnchorX != geneBranch.mJointAnchorX)
		return false;

	if (mJointAnchorY != geneBranch.mJointAnchorY)
		return false;

	if (mJointAnchorZ != geneBranch.mJointAnchorZ)
		return false;

	if (mJointPitch != geneBranch.mJointPitch)
		return false;

	if (mJointYaw != geneBranch.mJointYaw)
		return false;

	if (mJointRoll != geneBranch.mJointRoll)
		return false;

	if (mMirrored != geneBranch.mMirrored)
		return false;

	return true;
}

