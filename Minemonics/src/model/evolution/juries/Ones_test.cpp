/*
 * VelocityTestCase.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */
#include "model/evolution/juries/Ones.h"

#include <gtest/gtest.h>

class OnesTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		std::vector<bool> test;
		test.push_back(true);
		test.push_back(true);
		test.push_back(true);
		test.push_back(false);
		test.push_back(false);
		test.push_back(false);
		test.push_back(true);
		ones = new Ones(1);
		ones->setEvaluationSubject(test);
	}

	virtual void TearDown() {
		delete ones;
		ones = 0;
	}
	Ones* ones;
};

TEST_F(OnesTest,hasWeightOne) {
	ASSERT_TRUE(ones->getWeight() == 1);
}


TEST_F(OnesTest,evaluateOnesQty)
{
	ones->evaluateFitness();
	ASSERT_TRUE(ones->getFitness() == 4);
}

