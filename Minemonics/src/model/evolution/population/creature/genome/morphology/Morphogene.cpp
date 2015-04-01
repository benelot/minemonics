/*
 * MorphoGene.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */
//# corresponding header
#include "Morphogene.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"
#include "configuration/ControlConfiguration.h"

//## controller headers
//## model headers
//## view headers
//## utils headers
#include "utils/Randomness.h"

/**
 * A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neural
 * network connection.
 *
 * @author leviathan
 *
 */

Morphogene::Morphogene() :
		mColorR(0), mColorG(0), mColorB(0), mPrimitiveType(
				MorphologyConfiguration::UNKNOWN), mControllerGene(NULL), mFollowUpGene(
				-1), mJointAnchorX(0), mJointAnchorY(0), mJointAnchorZ(0), mJointPitch(
				0), mJointYaw(0), mJointRoll(0), mSegmentShrinkFactor(0), mRepetitionLimit(
				0), mX(0), mY(0), mZ(0) {

}

Morphogene::~Morphogene() {
	if (mControllerGene != NULL) {
		delete mControllerGene;
		mControllerGene = NULL;
	}

	while (!mGeneBranches.empty()) {
		MorphogeneBranch* f = mGeneBranches.back();
		mGeneBranches.pop_back();
		delete f;
	}
}

void Morphogene::initialize(double bushiness) {
	Randomness randomness;
	//Choose the dimensions of the segment with a bias toward larger dimensions
	mX = randomness.nextBiasedLog(MorphologyConfiguration::BODY_LIMB_MIN_SIZE,
			MorphologyConfiguration::BODY_LIMB_MAX_SIZE);
	mY = randomness.nextBiasedLog(MorphologyConfiguration::BODY_LIMB_MIN_SIZE,
			MorphologyConfiguration::BODY_LIMB_MAX_SIZE);
	mZ = randomness.nextBiasedLog(MorphologyConfiguration::BODY_LIMB_MIN_SIZE,
			MorphologyConfiguration::BODY_LIMB_MAX_SIZE);

	mSegmentShrinkFactor = 1.0
			+ randomness.nextDouble(
					MorphologyConfiguration::BODY_LIMB_SCALE_MIN,
					MorphologyConfiguration::BODY_LIMB_SCALE_MAX);

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

	// A random color
	mColorR = randomness.nextDouble(0, 255);
	mColorG = randomness.nextDouble(0, 255);
	mColorB = randomness.nextDouble(0, 255);

	switch ((MorphologyConfiguration::PrimitiveType) randomness.nextPosInt(1,
			MorphologyConfiguration::PRIMITIVE_QTY)) {
	case MorphologyConfiguration::BLOCK: {
		//Randomly choose a segment primitive
		mPrimitiveType = MorphologyConfiguration::BLOCK;
	}
		break;
	case MorphologyConfiguration::CAPSULE: {
		mPrimitiveType = MorphologyConfiguration::CAPSULE;
	}
		break;
	}

	// The maximum repetition of this gene in a root-to-leaf path. This can change later to a higher number than the initial type repeats.
	mRepetitionLimit = randomness.nextPosInt(0,
			MorphologyConfiguration::BODY_LIMB_INITIAL_TYPE_REPEATS);

	//The follow up gene follows instead if this gene's repetition limit is reached.
	mFollowUpGene = -1;

	int branchQty = randomness.nextPosInt(0, bushiness);

	for (int i = 0; i < branchQty; i++) {
		MorphogeneBranch* branch = new MorphogeneBranch();
		branch->initialize();
		mGeneBranches.push_back(branch);
	}

	mControllerGene = new SineControllerGene();
	mControllerGene->initialize();
}

void Morphogene::print() {
//I am a gene.
}

bool Morphogene::equals(const Morphogene & morphoGene) const {

	if (mColorR != morphoGene.mColorR) {
		return false;
	}

	if (mColorG != morphoGene.mColorG) {
		return false;
	}

	if (mColorB != morphoGene.mColorB) {
		return false;
	}

	if ((mControllerGene == NULL && morphoGene.mControllerGene != NULL)
			|| (mControllerGene != NULL && morphoGene.mControllerGene == NULL)) {
		return false;
	} else if (mControllerGene != NULL && morphoGene.mControllerGene != NULL
			&& mControllerGene->equals(*morphoGene.mControllerGene)) {
		switch (mControllerGene->getControllerGeneType()) {
		case ControllerGene::SineControllerGene:
			if (!((SineControllerGene*) mControllerGene)->equals(
					((SineControllerGene&) (*morphoGene.mControllerGene)))) {
				return false;
			}
			break;
		default:
			break;
		}
	}

	if (mFollowUpGene != morphoGene.mFollowUpGene) {
		return false;
	}

	std::vector<MorphogeneBranch*>::const_iterator it = mGeneBranches.begin();
	std::vector<MorphogeneBranch*>::const_iterator it2 =
			morphoGene.mGeneBranches.begin();
	for (; it != mGeneBranches.end(), it2 != morphoGene.mGeneBranches.end();
			it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	if (mJointAnchorX != morphoGene.mJointAnchorX) {
		return false;
	}

	if (mJointAnchorY != morphoGene.mJointAnchorY) {
		return false;
	}

	if (mJointAnchorZ != morphoGene.mJointAnchorZ) {
		return false;
	}

	if (mJointPitch != morphoGene.mJointPitch) {
		return false;
	}

	if (mJointYaw != morphoGene.mJointYaw) {
		return false;
	}

	if (mJointRoll != morphoGene.mJointRoll) {
		return false;
	}

	if (mRepetitionLimit != morphoGene.mRepetitionLimit) {
		return false;
	}

	if (mSegmentShrinkFactor != morphoGene.mSegmentShrinkFactor) {
		return false;
	}

	if (mX != morphoGene.mX) {
		return false;
	}

	if (mY != morphoGene.mY) {
		return false;
	}

	if (mZ != morphoGene.mZ) {
		return false;
	}

	return true;
}

