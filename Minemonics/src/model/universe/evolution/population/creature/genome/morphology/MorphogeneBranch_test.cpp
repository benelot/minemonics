/*
 * GeneBranch_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/SaveController.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers

//## controller headers

//## model headers
//## view headers
//## utils headers

class MorphoGeneBranchTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		geneBranch = new MorphogeneBranch();
		geneBranch->initialize();

	}

	virtual void TearDown() {
		delete geneBranch;
		geneBranch = 0;
	}
	MorphogeneBranch* geneBranch;
};

class MorphoGeneBranchSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		geneBranch = new MorphogeneBranch();
		geneBranch->initialize();

		geneBranch2 = new MorphogeneBranch();

		SaveController<MorphogeneBranch> geneBranchSaveController;
		geneBranchSaveController.save(*geneBranch, "GeneBranch.test");
		geneBranchSaveController.restore(*geneBranch2, "GeneBranch.test");

	}

	virtual void TearDown() {
		delete geneBranch;
		geneBranch = NULL;

		delete geneBranch2;
		geneBranch2 = NULL;
	}
	MorphogeneBranch* geneBranch;

	MorphogeneBranch* geneBranch2;
};

TEST_F(MorphoGeneBranchTest,hasValidJointAnchor) {
	//test valid joint anchor
	ASSERT_TRUE(0 <= geneBranch->getJointAnchorX() <= 1);
	ASSERT_TRUE(0 <= geneBranch->getJointAnchorY() <= 1);
	ASSERT_TRUE(0 <= geneBranch->getJointAnchorZ() <= 1);
	ASSERT_TRUE(
			geneBranch->getJointAnchorX() != 0
					&& geneBranch->getJointAnchorY() != 0
					&& geneBranch->getJointAnchorZ() != 0);
}

TEST_F(MorphoGeneBranchTest,hasValidJointRotation) {
	//test valid joint rotation
	ASSERT_TRUE(
			0 <= geneBranch->getJointPitch()
					<= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(
			0 <= geneBranch->getJointYaw()
					<= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(
			0 <= geneBranch->getJointRoll()
					<= 2 * boost::math::constants::pi<double>());
}

// everything else can not be tested (booleans and a pointer pointing to NULL or non-NULL)

TEST_F(MorphoGeneBranchSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(geneBranch != geneBranch2);
	ASSERT_TRUE(geneBranch->equals(*geneBranch2));
}
