/*
 * VelocityTestCase.cpp
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <gtest/gtest.h>
#include <model/universe/evolution/juries/Ones.hpp>

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

