//# corresponding header
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class MorphoGeneTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		gene = new Morphogene();
		gene->initialize(30);

	}

	virtual void TearDown() {
		delete gene;
		gene = NULL;
		delete randomness;
		randomness = NULL;
	}
	Morphogene* gene;
	Randomness* randomness;
};

class MorphoGeneSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		morphoGene = new Morphogene();
		morphoGene->initialize(30);

		morphoGene2 = new Morphogene();

		SaveController < Morphogene > saveController;

		saveController.save(*morphoGene, "test/MorphoGene.test");

		saveController.restore(*morphoGene2, "test/MorphoGene.test");
	}

	virtual void TearDown() {
		delete morphoGene;
		morphoGene = NULL;
		delete morphoGene2;
		morphoGene2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	Morphogene* morphoGene;

	Morphogene* morphoGene2;

	Randomness* randomness;
};

TEST_F(MorphoGeneTest,hasSizeWithinBounds) {
	ASSERT_TRUE(
		MorphologyConfiguration::LIMB_MIN_SIZE <= gene->getX()
		<= MorphologyConfiguration::LIMB_MAX_SIZE);
	ASSERT_TRUE(
		MorphologyConfiguration::LIMB_MIN_SIZE <= gene->getY()
		<= MorphologyConfiguration::LIMB_MAX_SIZE);
	ASSERT_TRUE(
		MorphologyConfiguration::LIMB_MIN_SIZE <= gene->getZ()
		<= MorphologyConfiguration::LIMB_MAX_SIZE);
}

TEST_F(MorphoGeneTest,hasValidJointAnchor) {
	//test valid joint anchor
	ASSERT_TRUE(0 <= gene->getJointAnchorX() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorY() <= 1);
	ASSERT_TRUE(0 <= gene->getJointAnchorZ() <= 1);
	ASSERT_TRUE(
		gene->getJointAnchorX() != 0 && gene->getJointAnchorY() != 0
		&& gene->getJointAnchorZ() != 0);
}

TEST_F(MorphoGeneTest,hasValidJointRotation) {
	//test valid joint rotation
	ASSERT_TRUE(
		0 <= gene->getJointPitch()
		<= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(
		0 <= gene->getJointYaw()
		<= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(
		0 <= gene->getJointRoll()
		<= 2 * boost::math::constants::pi<double>());
}

TEST_F(MorphoGeneTest,hasValidColor) {
	//test valid color
	ASSERT_TRUE(0 <= gene->getColorR() <= 255);
	ASSERT_TRUE(0 <= gene->getColorG() <= 255);
	ASSERT_TRUE(0 <= gene->getColorB() <= 255);
}

TEST_F(MorphoGeneTest,hasAccurateBranchQty) {
	//test if the number of branches is lower or equal to the bushiness factor
	ASSERT_TRUE(gene->getGeneBranches().size() <= 30);
}

TEST_F(MorphoGeneTest,testMisc) {
	//test genetype is morphogene
	ASSERT_TRUE(gene->getType() == Gene::MorphoGene);

	//test segment shrink factor is in range
	ASSERT_TRUE(
		1 - MorphologyConfiguration::LIMB_SCALE_MAX
		<= gene->getSegmentShrinkFactor()
		<= 1 + MorphologyConfiguration::LIMB_SCALE_MAX);

	// test repetition limit
	ASSERT_TRUE(
		0 <= gene->getRepetitionLimit()
		<= MorphologyConfiguration::LIMB_INITIAL_TYPE_REPEATS);

	// follow up gene can not be valid at this time
}

TEST_F(MorphoGeneSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(morphoGene != morphoGene2);
	ASSERT_TRUE(morphoGene->equals(*morphoGene2));
}

