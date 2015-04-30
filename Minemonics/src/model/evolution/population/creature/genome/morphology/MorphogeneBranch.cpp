/*
 * MorphoGeneBranch.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <model/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

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
#include <model/evolution/population/creature/genome/morphology/Morphogene.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

MorphogeneBranch::MorphogeneBranch() : mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(
				0), mJointAnchorZ(0), mJointPitch(0), mJointYaw(0), mJointRoll(
				0), mActuated(false), mJointPitchMinAngle(0), mJointPitchMaxAngle(
				0), mJointYawMinAngle(0), mJointYawMaxAngle(0), mJointRollMinAngle(
				0), mJointRollMaxAngle(0), mMirrored(0), mSpringPitchDampingCoefficient(
				0), mJointPitchStiffness(0),mSpringYawDampingCoefficient(
						0), mJointYawStiffness(0),mSpringRollDampingCoefficient(
								0), mJointRollStiffness(0) {
}

void MorphogeneBranch::initialize() {
	GeneBranch::initialize(GeneBranch::MORPHOGENE_BRANCH);

	Randomness randomness;

	/** Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, Y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached.*/
	do {
		mJointAnchorX = randomness.nextDouble(-1.0f, 1.0f);
		mJointAnchorY = randomness.nextDouble(-1.0f, 1.0f);
		mJointAnchorZ = randomness.nextDouble(-1.0f, 1.0f);
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
	 * Set whether the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = randomness.nextBoolean();

	mFlipped = randomness.nextBoolean();

	mActive = randomness.nextBoolean();

	/**
	 * Set whether the joint should be actuated.
	 */
	mActuated = randomness.nextBoolean();

	mBranchGeneType = -1;

	/**
	 * The spring damping coefficient
	 */
	mSpringPitchDampingCoefficient = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringYawDampingCoefficient = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringRollDampingCoefficient = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);

	/**
	 * The joint stiffness
	 */
	mJointPitchStiffness = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointYawStiffness = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointRollStiffness = randomness.nextDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);
}

MorphogeneBranch::~MorphogeneBranch() {
}

bool MorphogeneBranch::equals(const MorphogeneBranch& geneBranch) const {

	if (mActive != geneBranch.mActive) {
		return false;
	}

	if (mBranchGeneType != geneBranch.mBranchGeneType) {
		return false;
	}

	if (mFlipped != geneBranch.mFlipped) {
		return false;
	}

	if (mJointAnchorX != geneBranch.mJointAnchorX) {
		return false;
	}

	if (mJointAnchorY != geneBranch.mJointAnchorY) {
		return false;
	}

	if (mJointAnchorZ != geneBranch.mJointAnchorZ) {
		return false;
	}

	if (mJointPitch != geneBranch.mJointPitch) {
		return false;
	}

	if (mJointPitchMinAngle != geneBranch.mJointPitchMinAngle) {
		return false;
	}

	if (mJointPitchMaxAngle != geneBranch.mJointPitchMaxAngle) {
		return false;
	}

	if (mJointYaw != geneBranch.mJointYaw) {
		return false;
	}

	if (mJointYawMinAngle != geneBranch.mJointYawMinAngle) {
		return false;
	}

	if (mJointYawMaxAngle != geneBranch.mJointYawMaxAngle) {
		return false;
	}

	if (mJointRoll != geneBranch.mJointRoll) {
		return false;
	}

	if (mJointRollMinAngle != geneBranch.mJointRollMinAngle) {
		return false;
	}

	if (mJointRollMaxAngle != geneBranch.mJointRollMaxAngle) {
		return false;
	}

	if (mMirrored != geneBranch.mMirrored) {
		return false;
	}

	if (mActuated != geneBranch.mActuated) {
		return false;
	}

	if (mSpringPitchDampingCoefficient != geneBranch.mSpringPitchDampingCoefficient) {
		return false;
	}

	if (mJointPitchStiffness != geneBranch.mJointPitchStiffness) {
		return false;
	}

	if (mSpringYawDampingCoefficient != geneBranch.mSpringYawDampingCoefficient) {
		return false;
	}

	if (mJointYawStiffness != geneBranch.mJointYawStiffness) {
		return false;
	}

	if (mSpringRollDampingCoefficient != geneBranch.mSpringRollDampingCoefficient) {
		return false;
	}

	if (mJointRollStiffness != geneBranch.mJointRollStiffness) {
		return false;
	}

	return true;
}

