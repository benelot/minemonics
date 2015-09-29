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
#include <model/universe/evolution/juries/IntegralAverageVelocity.hpp>

//## model headers
//## view headers
//## utils headers

class IntegralAverageVelocityTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new IntegralAverageVelocity(false, 2);
	}

	virtual void TearDown() {
		delete velocity;
		velocity = 0;
	}
	IntegralAverageVelocity* velocity;
};

class IntegralAverageVelocitySerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new IntegralAverageVelocity(false, 2);
		velocity2 = new IntegralAverageVelocity(true, 1);

		SaveController < IntegralAverageVelocity > saveController;

		saveController.save(*velocity, "test/AvgVelocity.test");

		saveController.restore(*velocity2, "test/AvgVelocity.test");
	}

	virtual void TearDown() {
		delete velocity;
		velocity = 0;
		delete velocity2;
		velocity2 = 0;
	}
	IntegralAverageVelocity* velocity;
	IntegralAverageVelocity* velocity2;
};

TEST_F(IntegralAverageVelocityTest,hasWeightTwo) {
	ASSERT_TRUE(velocity->getWeight() == 2);
}

TEST_F(IntegralAverageVelocityTest,evaluateVelocity) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

TEST_F(IntegralAverageVelocitySerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(velocity != velocity2);
	ASSERT_TRUE(velocity->equals(*velocity2));
}

