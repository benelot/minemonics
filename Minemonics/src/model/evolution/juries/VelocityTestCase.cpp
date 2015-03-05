/*
 * VelocityTestCase.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */
#include "model/evolution/juries/Velocity.h"
#include <iostream>

#include <gtest/gtest.h>

class VelocityTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		velocity = new Velocity(1);
	}

	virtual void TearDown() {
		delete velocity;
		velocity =0;
	}
	Velocity* velocity;
};

TEST_F(VelocityTest,hasWeightOne) {
	ASSERT_TRUE(velocity->getWeight() == 1);
}

TEST_F(VelocityTest,evaluateVelocity)
{
	velocity->calculateAvgVelocity(0,0,0,0);
	velocity->calculateAvgVelocity(1,0,0,1);
	velocity->evaluateFitness();
	ASSERT_TRUE(velocity->getFitness() == 1);
}

