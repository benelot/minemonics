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
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers

class AverageVelocityTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new AverageVelocity(false, 2);
	}

	virtual void TearDown() {
		delete velocity;
		velocity = 0;
	}
	AverageVelocity* velocity;
};

class AverageVelocitySerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new AverageVelocity(false, 2);
		velocity2 = new AverageVelocity(true, 1);

		SaveController<AverageVelocity> saveController;

		saveController.save(*velocity, "AvgVelocity.test");

		saveController.restore(*velocity2, "AvgVelocity.test");
	}

	virtual void TearDown() {
		delete velocity;
		velocity = 0;
		delete velocity2;
		velocity2 = 0;
	}
	AverageVelocity* velocity;
	AverageVelocity* velocity2;
};

TEST_F(AverageVelocityTest,hasWeightTwo) {
	ASSERT_TRUE(velocity->getWeight() == 2);
}

TEST_F(AverageVelocityTest,evaluateVelocity) {
	//TODO: Broken test
//	velocity->calculateFitness(0,0,0,0);
//	velocity->calculateFitness(1,0,0,1);
//	velocity->evaluateFitness();
//	ASSERT_TRUE(velocity->getFitness() == 1);
}

TEST_F(AverageVelocitySerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(velocity != velocity2);
	ASSERT_TRUE(velocity->equals(*velocity2));
}

