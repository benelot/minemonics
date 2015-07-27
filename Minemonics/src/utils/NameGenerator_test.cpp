/*
 * NameGenerator_test.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <gtest/gtest.h>
#include <utils/NameGenerator.hpp>

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

#define NUM_NAMES 500

class NameGeneratorTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		//initialize the randomness singleton
		randomness = new Randomness();

		nameGenerator = new NameGenerator();

		for (int i = 0; i < NUM_NAMES; i++) {
			names.push_back(nameGenerator->generateFirstName());
		}

	}

	virtual void TearDown() {
		delete nameGenerator;
		nameGenerator = NULL;
		delete randomness;
		randomness = NULL;
	}
	Randomness* randomness;
	NameGenerator* nameGenerator;

	std::vector<std::string> names;
};

TEST_F(NameGeneratorTest,namesAreUnique) {
	for (int i = 0; i < NUM_NAMES; i++) {
//		std::cout << names.at(i) << std::endl;
		for (int j = 0; j < NUM_NAMES; j++) {
			if (i != j) {
				ASSERT_TRUE(names.at(i) != names.at(j));
			}
		}
	}
}

