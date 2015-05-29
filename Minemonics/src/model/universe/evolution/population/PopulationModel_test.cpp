/*
 * Population_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/SaveController.hpp>
#include <gtest/gtest.h>
#include <model/universe/evolution/population/PopulationModel.hpp>

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

class PopulationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		population = new PopulationModel();
		population->initialize(NULL, 30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete population;
		population = 0;
	}
	PopulationModel* population;
};

class PopulationSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		population = new PopulationModel();
		population->initialize(NULL, 30);

		population2 = new PopulationModel();

		SaveController<PopulationModel> saveController;

		saveController.save(*population, "Population.test");

		saveController.restore(*population2, "Population.test");
	}

	virtual void TearDown() {
		delete population;
		population = NULL;
		delete population2;
		population2 = NULL;
	}
	PopulationModel* population;

	PopulationModel* population2;
};

TEST_F(PopulationTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(PopulationSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(population != population2);
	ASSERT_TRUE(population->equals(*population2));
}

