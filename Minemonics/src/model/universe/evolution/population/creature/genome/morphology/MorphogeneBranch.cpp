/*
 * MorphoGeneBranch.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <boost/math/constants/constants.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <utils/Randomness.hpp>

MorphogeneBranch::MorphogeneBranch() :
		mBranchGeneType(-1), mFlipped(false), mJointAnchorX(0), mJointAnchorY(
				0), mJointAnchorZ(0), mJointPitch(0), mJointYaw(0), mJointRoll(
				0), mJointPitchMinAngle(0), mJointPitchMaxAngle(0), mJointYawMinAngle(
				0), mJointYawMaxAngle(0), mJointRollMinAngle(0), mJointRollMaxAngle(
				0), mMirrored(0), mSpringPitchDampingCoefficient(0), mJointPitchStiffness(
				0), mSpringYawDampingCoefficient(0), mJointYawStiffness(0), mSpringRollDampingCoefficient(
				0), mJointRollStiffness(0), mJointPitchMotorEnabled(false), mJointYawMotorEnabled(
				false), mJointRollMotorEnabled(false), mJointMaxPitchForce(0), mJointMaxPitchSpeed(
				0), mJointMaxYawForce(0), mJointMaxYawSpeed(0), mJointMaxRollForce(
				0), mJointMaxRollSpeed(0) {
}

MorphogeneBranch::MorphogeneBranch(const MorphogeneBranch& morphogeneBranch) {
	mActive = morphogeneBranch.mActive;
	mBranchGeneType = morphogeneBranch.mBranchGeneType;
	mFlipped = morphogeneBranch.mFlipped;
	mType = morphogeneBranch.mType;
	mJointAnchorX = morphogeneBranch.mJointAnchorX;
	mJointAnchorY = morphogeneBranch.mJointAnchorY;
	mJointAnchorZ = morphogeneBranch.mJointAnchorZ;
	mJointMaxPitchForce = morphogeneBranch.mJointMaxPitchForce;
	mJointMaxPitchSpeed = morphogeneBranch.mJointMaxPitchSpeed;
	mJointMaxRollForce = morphogeneBranch.mJointMaxRollForce;
	mJointMaxRollSpeed = morphogeneBranch.mJointMaxRollSpeed;
	mJointMaxYawForce = morphogeneBranch.mJointMaxYawForce;
	mJointMaxYawSpeed = morphogeneBranch.mJointMaxYawSpeed;
	mJointPitch = morphogeneBranch.mJointPitch;
	mJointPitchMaxAngle = morphogeneBranch.mJointPitchMaxAngle;
	mJointPitchMinAngle = morphogeneBranch.mJointPitchMinAngle;
	mJointPitchMotorEnabled = morphogeneBranch.mJointPitchMotorEnabled;
	mJointPitchStiffness = morphogeneBranch.mJointPitchStiffness;
	mJointYaw = morphogeneBranch.mJointYaw;
	mJointYawMaxAngle = morphogeneBranch.mJointYawMaxAngle;
	mJointYawMinAngle = morphogeneBranch.mJointYawMinAngle;
	mJointYawMotorEnabled = morphogeneBranch.mJointYawMotorEnabled;
	mJointYawStiffness = morphogeneBranch.mJointYawStiffness;
	mJointRoll = morphogeneBranch.mJointRoll;
	mJointRollMaxAngle = morphogeneBranch.mJointRollMaxAngle;
	mJointRollMinAngle = morphogeneBranch.mJointRollMinAngle;
	mJointRollMotorEnabled = morphogeneBranch.mJointRollMotorEnabled;
	mJointRollStiffness = morphogeneBranch.mJointRollStiffness;
	mMirrored = morphogeneBranch.mMirrored;
	mSpringPitchDampingCoefficient =
			morphogeneBranch.mSpringPitchDampingCoefficient;
	mSpringYawDampingCoefficient =
			morphogeneBranch.mSpringYawDampingCoefficient;
	mSpringRollDampingCoefficient =
			morphogeneBranch.mSpringRollDampingCoefficient;
}

void MorphogeneBranch::initialize() {
	GeneBranch::initialize(GeneBranch::MORPHOGENE_BRANCH);

	Randomness randomness;

	/** Set joint anchor X, Y and Z, where the anchor lies in the center of mass
	 and the X, Y and Z form a vector, pointing to the point on the surface where
	 the joint will be attached.*/
	do {
		mJointAnchorX = randomness.nextUnifDouble(-1.0f, 1.0f);
		mJointAnchorY = randomness.nextUnifDouble(-1.0f, 1.0f);
		mJointAnchorZ = randomness.nextUnifDouble(-1.0f, 1.0f);
	} while (mJointAnchorX == 0 && mJointAnchorY == 0 && mJointAnchorZ == 0);

	/**
	 * The yaw, pitch and roll values representing a correction in angle of the joint anchor on the surface.
	 */
	mJointYaw = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitch = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRoll = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());

	/**
	 * The joint limits in each direction (pitch,yaw, roll)
	 */
	mJointPitchMinAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointPitchMaxAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointYawMinAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointYawMaxAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRollMinAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());
	mJointRollMaxAngle = randomness.nextUnifDouble(0,
			2 * boost::math::constants::pi<double>());

	/**
	 * Set whether the branch should be mirrored or flipped to the other side.
	 */
	mMirrored = randomness.nextUnifBoolean();

	mFlipped = randomness.nextUnifBoolean();

	mActive = randomness.nextUnifBoolean();

	mBranchGeneType = -1;

	/**
	 * The spring damping coefficient
	 */
	mSpringPitchDampingCoefficient = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringYawDampingCoefficient = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);
	mSpringRollDampingCoefficient = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPRING_COEFFICIENT,
			MorphologyConfiguration::JOINT_MAX_SPRING_COEFFICIENT);

	/**
	 * The joint stiffness
	 */
	mJointPitchStiffness = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointYawStiffness = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);
	mJointRollStiffness = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_STIFFNESS,
			MorphologyConfiguration::JOINT_MAX_STIFFNESS);

	/**
	 * Whether the joint motors are enabled or not.
	 */
	mJointPitchMotorEnabled = randomness.nextUnifBoolean();
	mJointYawMotorEnabled = randomness.nextUnifBoolean();
	mJointRollMotorEnabled = randomness.nextUnifBoolean();

	/**
	 * The maximum joint force
	 */
	mJointMaxPitchForce = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_FORCE,
			MorphologyConfiguration::JOINT_MAX_FORCE);
	mJointMaxYawForce = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_FORCE,
			MorphologyConfiguration::JOINT_MAX_FORCE);
	mJointMaxRollForce = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_FORCE,
			MorphologyConfiguration::JOINT_MAX_FORCE);

	/**
	 * The maximum joint speed
	 */
	mJointMaxPitchSpeed = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPEED,
			MorphologyConfiguration::JOINT_MAX_SPEED);
	mJointMaxYawSpeed = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPEED,
			MorphologyConfiguration::JOINT_MAX_SPEED);
	mJointMaxRollSpeed = randomness.nextUnifDouble(
			MorphologyConfiguration::JOINT_MIN_SPEED,
			MorphologyConfiguration::JOINT_MAX_SPEED);
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

	if (mSpringPitchDampingCoefficient
			!= geneBranch.mSpringPitchDampingCoefficient) {
		return false;
	}

	if (mJointPitchStiffness != geneBranch.mJointPitchStiffness) {
		return false;
	}

	if (mSpringYawDampingCoefficient
			!= geneBranch.mSpringYawDampingCoefficient) {
		return false;
	}

	if (mJointYawStiffness != geneBranch.mJointYawStiffness) {
		return false;
	}

	if (mSpringRollDampingCoefficient
			!= geneBranch.mSpringRollDampingCoefficient) {
		return false;
	}

	if (mJointRollStiffness != geneBranch.mJointRollStiffness) {
		return false;
	}

	if (mJointPitchMotorEnabled != geneBranch.mJointPitchMotorEnabled) {
		return false;
	}

	if (mJointYawMotorEnabled != geneBranch.mJointYawMotorEnabled) {
		return false;
	}

	if (mJointRollMotorEnabled != geneBranch.mJointRollMotorEnabled) {
		return false;
	}

	if (mJointMaxPitchForce != geneBranch.mJointMaxPitchForce) {
		return false;
	}

	if (mJointMaxYawForce != geneBranch.mJointMaxYawForce) {
		return false;
	}

	if (mJointMaxRollForce != geneBranch.mJointMaxRollForce) {
		return false;
	}

	if (mJointMaxPitchSpeed != geneBranch.mJointMaxPitchSpeed) {
		return false;
	}

	if (mJointMaxYawSpeed != geneBranch.mJointMaxYawSpeed) {
		return false;
	}

	if (mJointMaxRollSpeed != geneBranch.mJointMaxRollSpeed) {
		return false;
	}

	return true;
}

MorphogeneBranch* MorphogeneBranch::clone() {
	return new MorphogeneBranch(*this);
}

void MorphogeneBranch::mutate() {

	//no clean up necessary

	initialize();
}
