//# corresponding headers
#include <gtest/gtest.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/chaotic/ChaoticController.hpp>
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class ChaoticControllerTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();

		// Set up an object of the class you want to test
		chaoticController = new ChaoticController(
			ChaoticControllerGene::CHUA_CIRCUIT,
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(0.1, 10));
		chaoticController->initialize();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete chaoticController;
		chaoticController = NULL;

		delete randomness;
		randomness = NULL;
	}
	ChaoticController* chaoticController;

	Randomness* randomness;
};

class ChaoticControllerSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();

		chaoticController = new ChaoticController(
			ChaoticControllerGene::CHUA_CIRCUIT,
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(-10, 10),
			Randomness::getSingleton()->nextUnifDouble(0.1, 10));
		chaoticController->initialize();

		chaoticController2 = new ChaoticController();

		SaveController<ChaoticController> saveController;

		saveController.save(*chaoticController, "test/ChaoticController.test");

		saveController.restore(*chaoticController2,
			"test/ChaoticController.test");
	}

	virtual void TearDown() {
		delete chaoticController;
		chaoticController = NULL;
		delete chaoticController2;
		chaoticController2 = NULL;

		delete randomness;
		randomness = NULL;
	}
	ChaoticController* chaoticController;

	ChaoticController* chaoticController2;

	Randomness* randomness;
};

TEST_F(ChaoticControllerTest,TestRun) {
	for (int i = 0; i < 50000; i++) {
		chaoticController->calcChuaCircuit();
	}
	//TODO: Add all tests
	//ASSERT_TRUE(chaoticConstroller->)
}

TEST_F(ChaoticControllerSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(chaoticController != chaoticController2);
	ASSERT_TRUE(chaoticController->equals(*chaoticController2));
}

