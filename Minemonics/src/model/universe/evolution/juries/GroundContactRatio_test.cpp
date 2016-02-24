//# corresponding header
#include <gtest/gtest.h>
#include <iostream>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>
#include <model/universe/evolution/juries/GroundContactRatio.hpp>

//## model headers
//## view headers
//## utils headers

class GroundContactRatioTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new GroundContactRatio(false, 2);
	}

	virtual void TearDown() {
		delete height;
		height = 0;
	}
	GroundContactRatio* height;
};

class GroundContactRatioSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new GroundContactRatio(false, 2);
		height2 = new GroundContactRatio(true, 1);

		SaveController < GroundContactRatio > saveController;

		saveController.save(*height, "test/GroundContactRatio.test");

		saveController.restore(*height2, "test/GroundContactRatio.test");
	}

	virtual void TearDown() {
		delete height;
		height = 0;
		delete height2;
		height2 = 0;
	}
	GroundContactRatio* height;
	GroundContactRatio* height2;
};

TEST_F(GroundContactRatioTest,hasWeightTwo) {
	ASSERT_TRUE(height->getWeight() == 2);
}

TEST_F(GroundContactRatioTest,evaluateHeight) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

TEST_F(GroundContactRatioSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(height != height2);
	ASSERT_TRUE(height->equals(*height2));
}

