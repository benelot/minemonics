//# corresponding header
#include <gtest/gtest.h>
#include <model/universe/evolution/juries/AverageHeight.hpp>
#include <iostream>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers

class AverageHeightTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new AverageHeight(false, 2);
	}

	virtual void TearDown() {
		delete height;
		height = 0;
	}
	AverageHeight* height;
};

class AverageHeightSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new AverageHeight(false, 2);
		height2 = new AverageHeight(true, 1);

		SaveController < AverageHeight > saveController;

		saveController.save(*height, "test/AvgHeight.test");

		saveController.restore(*height2, "test/AvgHeight.test");
	}

	virtual void TearDown() {
		delete height;
		height = 0;
		delete height2;
		height2 = 0;
	}
	AverageHeight* height;
	AverageHeight* height2;
};

TEST_F(AverageHeightTest,hasWeightTwo) {
	ASSERT_TRUE(height->getWeight() == 2);
}

TEST_F(AverageHeightTest,evaluateHeight) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

TEST_F(AverageHeightSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(height != height2);
	ASSERT_TRUE(height->equals(*height2));
}

