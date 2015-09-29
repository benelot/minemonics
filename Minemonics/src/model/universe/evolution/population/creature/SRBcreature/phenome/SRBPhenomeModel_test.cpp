//# corresponding headers
#include <gtest/gtest.h>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/SRBPhenomeModel.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class SRBPhenomeModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new SRBPhenomeModel();
		phenomeModel->initialize(NULL);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete phenomeModel;
		phenomeModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	SRBPhenomeModel* phenomeModel;

	Randomness* randomness;
};

class SRBPhenomeModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new SRBPhenomeModel();
		phenomeModel->initialize(NULL);

		phenomeModel2 = new SRBPhenomeModel();

		SaveController < SRBPhenomeModel > saveController;

		saveController.save(*phenomeModel, "test/SRBPhenomeModel.test");

		saveController.restore(*phenomeModel2, "test/SRBPhenomeModel.test");
	}

	virtual void TearDown() {
		delete phenomeModel;
		phenomeModel = NULL;
		delete phenomeModel2;
		phenomeModel2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	SRBPhenomeModel* phenomeModel;

	SRBPhenomeModel* phenomeModel2;

	Randomness* randomness;
};

TEST_F(SRBPhenomeModelTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(SRBPhenomeModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(phenomeModel != phenomeModel2);
	ASSERT_TRUE(phenomeModel->equals(*phenomeModel2));
}
