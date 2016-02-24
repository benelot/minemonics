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
#include <model/universe/evolution/juries/GroundContactQty.hpp>

//## model headers
//## view headers
//## utils headers

class GroundContactQtyTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new GroundContactQty(false, 2);
	}

	virtual void TearDown() {
		delete height;
		height = 0;
	}
	GroundContactQty* height;
};

class GroundContactQtySerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new GroundContactQty(false, 2);
		height2 = new GroundContactQty(true, 1);

		SaveController < GroundContactQty > saveController;

		saveController.save(*height, "test/GroundContactQty.test");

		saveController.restore(*height2, "test/GroundContactQty.test");
	}

	virtual void TearDown() {
		delete height;
		height = 0;
		delete height2;
		height2 = 0;
	}
	GroundContactQty* height;
	GroundContactQty* height2;
};

TEST_F(GroundContactQtyTest,hasWeightTwo) {
	ASSERT_TRUE(height->getWeight() == 2);
}

TEST_F(GroundContactQtyTest,evaluateHeight) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

TEST_F(GroundContactQtySerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(height != height2);
	ASSERT_TRUE(height->equals(*height2));
}

