/*
 * Randomness_test.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <math.h>

//# system headers
#include <gtest/gtest.h>
#include <utils/Randomness.hpp>

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

class RandomnessTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
	}

	virtual void TearDown() {
		delete randomness;
		randomness = NULL;
	}
	Randomness* randomness;
};

TEST_F(RandomnessTest,distributionsStayWithinBounds) {
	for (int i = 0; i < 100; i++) {
		//biased log distribution
		double biasedLogNumber = randomness->nextBiasedLogDouble(3, 7);
		std::cout << biasedLogNumber << "\t";
		ASSERT_TRUE(3 <= biasedLogNumber);
		ASSERT_TRUE(biasedLogNumber <= 7);

		// uniformly distributed double
		double uniformDouble = randomness->nextUnifDouble(10, 100);
		std::cout << uniformDouble << "\t";
		ASSERT_TRUE(10 <= uniformDouble);
		ASSERT_TRUE(uniformDouble <= 100);

		// positive integer
		double positiveInt = randomness->nextUnifPosInt(10, 100);
		std::cout << positiveInt << "\t";
		ASSERT_TRUE(10 <= positiveInt);
		ASSERT_TRUE(positiveInt <= 100);
		ASSERT_TRUE(positiveInt == floor(positiveInt));

		// normally distributed boolean
		double normalBoolean = randomness->nextNormalBoolean(0.8f, 3);
		std::cout << normalBoolean << "\t";
		ASSERT_TRUE(0 <= normalBoolean);
		ASSERT_TRUE(normalBoolean <= 1);

		// normally distributed double
		double normalDouble = randomness->nextNormalDouble(404.404f, 30);
		std::cout << normalDouble << "\t";

		// normally distributed integer
		double normalInt = randomness->nextNormalInt(404.404f, 30);
		std::cout << normalInt << "\t";
		ASSERT_TRUE(340 <= normalInt);
		ASSERT_TRUE(normalInt <= 470);
		ASSERT_TRUE(normalInt == floor(normalInt));

		//biased double
		double biasedDouble =  randomness->nextBiasedLogDouble(123,456);
		std::cout << biasedDouble << std::endl;
		ASSERT_TRUE(123 <= biasedDouble);
		ASSERT_TRUE(biasedDouble <= 456);
	}
}

TEST_F(RandomnessTest,distributionTest) {
//	std::cout << "How are unif(0.001,10) distributed?\n";
//	for (int i = 0; i < 100; i++) {
//		// uniformly distributed double
//		double uniformDouble = randomness->nextUnifDouble(0.001, 10);
//		std::cout << uniformDouble << "\n";
////		ASSERT_TRUE(10 <= uniformDouble);
////		ASSERT_TRUE(uniformDouble <= 100);
//
//	}

	std::cout << "How are log10(0.001,10) distributed?\n";
	for (int i = 0; i < 100; i++) {
		// log10 uniformly distributed double
		double uniformDouble = randomness->nextLog10Double(0.01, 10);
		std::cout << uniformDouble << "\n";
//		ASSERT_TRUE(10 <= uniformDouble);
//		ASSERT_TRUE(uniformDouble <= 100);

	}
}

