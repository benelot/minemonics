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
//## model headers
//## view headers
//## utils headers

class AverageHeightTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		height = new AverageHeight(true, 1);
	}

	virtual void TearDown() {
		delete height;
		height = 0;
	}
	AverageHeight* height;
};

TEST_F(AverageHeightTest,hasWeightOne) {
	ASSERT_TRUE(height->getWeight() == 1);
}

TEST_F(AverageHeightTest,evaluateHeight) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

