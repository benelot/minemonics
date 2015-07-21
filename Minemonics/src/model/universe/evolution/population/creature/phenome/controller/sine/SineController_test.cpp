/*
 * SineController_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <gtest/gtest.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class SineControllerTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		sineController = new SineController();
		sineController->initialize(1,1,0,0);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete sineController;
		sineController = NULL;
	}
	SineController* sineController;
};

class SineControllerSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		sineController = new SineController();
		sineController->initialize(1,1,0,0);

		sineController2 = new SineController();

		SaveController<SineController> saveController;

		saveController.save(*sineController, "SineController.test");

		saveController.restore(*sineController2, "SineController.test");
	}

	virtual void TearDown() {
		delete sineController;
		sineController = 0;
		delete sineController2;
		sineController2 = 0;
	}
	SineController* sineController;

	SineController* sineController2;
};

TEST_F(SineControllerTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(SineControllerSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(sineController != sineController2);
	ASSERT_TRUE(sineController->equals(*sineController2));
}

