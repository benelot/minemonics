/*
 * NameGenerator_test.cpp
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "NameGenerator.h"

//# forward declarations

//# system headers
#include <gtest/gtest.h>

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

class NameGeneratorTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		nameGenerator = new NameGenerator();

		for (int i = 0; i < 100; i++) {
			names.push_back(nameGenerator->generateName());
		}

	}

	virtual void TearDown() {
		delete nameGenerator;
		nameGenerator = 0;
	}
	NameGenerator* nameGenerator;
	std::vector<std::string> names;
};

TEST_F(NameGeneratorTest,namesAreUnique) {
	for (int i = 0; i < 100; i++) {
		//std::cout << names.at(i) << std::endl;
		for (int j = 0; j < 100; j++) {
			if (i != j) {
				ASSERT_TRUE(names.at(i) != names.at(j));
			}
		}
	}
}

