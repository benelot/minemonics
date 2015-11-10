//# corresponding headers
#include <gtest/gtest.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
//## model headers
//## view headers
//## utils headers

#define AMPLITUDE 1
#define FREQUENCY 1

class SineControllerTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		sineController = new SineController(AMPLITUDE, FREQUENCY, 0, 0);
		sineController->initialize();
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
		sineController = new SineController(AMPLITUDE, FREQUENCY, 0, 0);
		sineController->initialize();

		sineController2 = new SineController();

		SaveController < SineController > saveController;

		saveController.save(*sineController, "test/SineController.test");

		saveController.restore(*sineController2, "test/SineController.test");
	}

	virtual void TearDown() {
		delete sineController;
		sineController = NULL;
		delete sineController2;
		sineController2 = NULL;
	}
	SineController* sineController;

	SineController* sineController2;
};

TEST_F(SineControllerTest,AmplitudeTest) {
	for (double i = 0; i < 2 * M_PI; i += 0.01) {
		sineController->perform(i);
		ASSERT_TRUE(sineController->getOutputValue() <= 1);
		ASSERT_TRUE(sineController->getOutputValue() >= -1);
	}

}

TEST_F(SineControllerTest,FrequencyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(SineControllerSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(sineController != sineController2);
	ASSERT_TRUE(sineController->equals(*sineController2));
}

