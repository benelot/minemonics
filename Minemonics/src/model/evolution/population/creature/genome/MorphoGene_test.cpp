/*
 * Gene_test.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <gtest/gtest.h>
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

//## view headers

//## utils headers
#include "configuration/MorphologyConfiguration.h"

class GeneTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		gene = new MorphoGene();
		gene->initialize(30);

	}

	virtual void TearDown() {
		delete gene;
		gene = 0;
	}
	MorphoGene* gene;
};

TEST_F(GeneTest,hasSizeWithinBounds) {
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getX() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getY() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getZ() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
}


TEST_F(GeneTest,hasValidJointAnchor)
{
	//test valid joint anchor
	ASSERT_TRUE(0 <= gene->getJointAnchorX() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorY() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorZ() <= 1);
	ASSERT_TRUE(gene->getJointAnchorX() != 0 && gene->getJointAnchorY() != 0 && gene->getJointAnchorZ() != 0);
}

TEST_F(GeneTest,hasValidJointRotation)
{
	//test valid joint rotation
	ASSERT_TRUE(0 <= gene->getJointPitch() <= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(0 <= gene->getJointYaw() <= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(0 <= gene->getJointRoll() <= 2 * boost::math::constants::pi<double>());
}

TEST_F(GeneTest,hasValidColor)
{
	//test valid color
	ASSERT_TRUE(0 <= gene->getColorR() <= 255);
	ASSERT_TRUE(0 <= gene->getColorG() <= 255);
	ASSERT_TRUE(0 <= gene->getColorB() <= 255);
}

TEST_F(GeneTest,hasAccurateBranchQty)
{
	//test if the number of branches is lower or equal to the bushiness factor
	ASSERT_TRUE(gene->getGeneBranches().size() <= 30);
}

TEST_F(GeneTest,testMisc)
{
	//test segment shrink factor is in range
	ASSERT_TRUE(1-MorphologyConfiguration::BODY_SEGMENT_SCALE_MAX <= gene->getSegmentShrinkFactor() <= 1 + MorphologyConfiguration::BODY_SEGMENT_SCALE_MAX);

	// test repetition limit
	ASSERT_TRUE(0 <= gene->getRepetitionLimit() <= MorphologyConfiguration::BODY_SEGMENT_INITIAL_TYPE_REPEATS);

	// follow up gene can not be valid at this time

	//test if controller is there
	ASSERT_TRUE(gene->getControllerGene() != NULL);
}
