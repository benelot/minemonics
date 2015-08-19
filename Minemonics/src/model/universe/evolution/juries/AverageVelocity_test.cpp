//# corresponding header
#include <gtest/gtest.h>
#include <model/universe/evolution/juries/AverageVelocity.hpp>
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

class AverageVelocityTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new AverageVelocity(true, 1);
	}

	virtual void TearDown() {
		delete velocity;
		velocity = 0;
	}
	AverageVelocity* velocity;
};

TEST_F(AverageVelocityTest,hasWeightOne) {
	ASSERT_TRUE(velocity->getWeight() == 1);
}

TEST_F(AverageVelocityTest,evaluateVelocity) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

