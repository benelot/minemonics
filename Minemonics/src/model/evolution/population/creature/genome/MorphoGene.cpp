/*
 * MorphoGene.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */
//# corresponding header
#include "MorphoGene.h"

//# forward declarations
//# system headers

//## controller headers

//## model headers
#include <boost/math/constants/constants.hpp>

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers
#include "model/evolution/population/creature/genome/controller/ControllerGene.h"
#include "model/evolution/population/creature/genome/controller/SineControllerGene.h"
//## model headers

//## view headers

//## utils headers
#include "configuration/MorphologyConfiguration.h"
#include "configuration/ControlConfiguration.h"
#include "utils/Randomness.h"

/**
 * A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neuronal
 * network connection.
 *
 * @author leviathan
 *
 */

MorphoGene::MorphoGene() {

}

MorphoGene::~MorphoGene() {
// TODO Auto-generated destructor stub
}

void MorphoGene::initialize(double bushiness)
{
	Randomness randomness;
	//Choose the dimensions of the segment with a bias toward larger dimensions
	mX = randomness.nextBiasedLog(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE,
			MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	mY = randomness.nextBiasedLog(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE,
			MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	mZ = randomness.nextBiasedLog(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE,
			MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);

	mSegmentShrinkFactor = 1.0
			+ randomness.nextDouble(
					MorphologyConfiguration::BODY_SEGMENT_SCALE_MIN,
					MorphologyConfiguration::BODY_SEGMENT_SCALE_MAX);

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

	// The maximum repetition of this gene in a root-to-leaf path. This can change later to a higher number than the initial type repeats.
	mRepetitionLimit = randomness.nextPosInt(0,MorphologyConfiguration::BODY_SEGMENT_INITIAL_TYPE_REPEATS);

	//The follow up gene follows instead if this gene's repetition limit is reached.
	mFollowUpGene = NULL;


	int branchQty = randomness.nextPosInt(0,bushiness);

	for(int i = 0; i < branchQty;i++)
	{
		MorphoGeneBranch branch;
		mGeneBranches.push_back(branch);
	}

	mControllerGene = new SineControllerGene();
	mControllerGene->initialize();
}

void MorphoGene::print() {
//I am a gene.
}

