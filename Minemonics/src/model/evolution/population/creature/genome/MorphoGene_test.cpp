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
#include "controller/SaveController.h"

//## model headers

//## view headers

//## utils headers
#include "configuration/MorphologyConfiguration.h"

class MorphoGeneTest: public ::testing::Test {
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

class MorphoGeneSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		morphoGene = new MorphoGene();
		morphoGene->initialize(30);

		morphoGene2 = new MorphoGene();

		SaveController<MorphoGene> saveController;

		saveController.save(*morphoGene,"MorphoGene.test");

		saveController.restore(*morphoGene2,"MorphoGene.test");
	}

	virtual void TearDown() {
		delete morphoGene;
		morphoGene = 0;
		delete morphoGene2;
		morphoGene2 = 0;
	}
	MorphoGene* morphoGene;

	MorphoGene* morphoGene2;
};

TEST_F(MorphoGeneTest,hasSizeWithinBounds) {
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getX() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getY() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
	ASSERT_TRUE(MorphologyConfiguration::BODY_CUBOID_MIN_SIZE <= gene->getZ() <= MorphologyConfiguration::BODY_CUBOID_MAX_SIZE);
}


TEST_F(MorphoGeneTest,hasValidJointAnchor)
{
	//test valid joint anchor
	ASSERT_TRUE(0 <= gene->getJointAnchorX() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorY() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorZ() <= 1);
	ASSERT_TRUE(gene->getJointAnchorX() != 0 && gene->getJointAnchorY() != 0 && gene->getJointAnchorZ() != 0);
}

TEST_F(MorphoGeneTest,hasValidJointRotation)
{
	//test valid joint rotation
	ASSERT_TRUE(0 <= gene->getJointPitch() <= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(0 <= gene->getJointYaw() <= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(0 <= gene->getJointRoll() <= 2 * boost::math::constants::pi<double>());
}

TEST_F(MorphoGeneTest,hasValidColor)
{
	//test valid color
	ASSERT_TRUE(0 <= gene->getColorR() <= 255);
	ASSERT_TRUE(0 <= gene->getColorG() <= 255);
	ASSERT_TRUE(0 <= gene->getColorB() <= 255);
}

TEST_F(MorphoGeneTest,hasAccurateBranchQty)
{
	//test if the number of branches is lower or equal to the bushiness factor
	ASSERT_TRUE(gene->getGeneBranches().size() <= 30);
}

TEST_F(MorphoGeneTest,testMisc)
{
	//test segment shrink factor is in range
	ASSERT_TRUE(1-MorphologyConfiguration::BODY_SEGMENT_SCALE_MAX <= gene->getSegmentShrinkFactor() <= 1 + MorphologyConfiguration::BODY_SEGMENT_SCALE_MAX);

	// test repetition limit
	ASSERT_TRUE(0 <= gene->getRepetitionLimit() <= MorphologyConfiguration::BODY_SEGMENT_INITIAL_TYPE_REPEATS);

	// follow up gene can not be valid at this time

	//test if controller is there
	ASSERT_TRUE(gene->getControllerGene() != NULL);
}

TEST_F(MorphoGeneSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(morphoGene != morphoGene2);
	ASSERT_TRUE(morphoGene->equals(*morphoGene2));
}


