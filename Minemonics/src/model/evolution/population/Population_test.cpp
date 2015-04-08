/*
 * Population_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Population.h"

//# forward declarations
//# system headers
#include <gtest/gtest.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
#include "controller/SaveController.h"

//## model headers
//## view headers
//## utils headers

class PopulationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		population = new Population();
		population->initialize(30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete population;
		population = 0;
	}
	Population* population;
};

class PopulationSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		population = new Population();
		population->initialize(30);

		population2 = new Population();

		SaveController<Population> saveController;

		saveController.save(*population, "Population.test");

		saveController.restore(*population2, "Population.test");
	}

	virtual void TearDown() {
		delete population;
		population = NULL;
		delete population2;
		population2 = NULL;
	}
	Population* population;

	Population* population2;
};

TEST_F(PopulationTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(PopulationSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(population != population2);
	ASSERT_TRUE(population->equals(*population2));
}


