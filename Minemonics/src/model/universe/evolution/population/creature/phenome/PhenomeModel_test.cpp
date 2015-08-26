//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/PhenomeModel.hpp>
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

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class PhenomeModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new PhenomeModel();
		phenomeModel->initialize(NULL);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete phenomeModel;
		phenomeModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	PhenomeModel* phenomeModel;

	Randomness* randomness;
};

class PhenomeModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		phenomeModel = new PhenomeModel();
		phenomeModel->initialize(NULL);

		phenomeModel2 = new PhenomeModel();

		SaveController<PhenomeModel> saveController;

		saveController.save(*phenomeModel, "PhenomeModel.test");

		saveController.restore(*phenomeModel2, "PhenomeModel.test");
	}

	virtual void TearDown() {
		delete phenomeModel;
		phenomeModel = NULL;
		delete phenomeModel2;
		phenomeModel2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	PhenomeModel* phenomeModel;

	PhenomeModel* phenomeModel2;

	Randomness* randomness;
};

TEST_F(PhenomeModelTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(PhenomeModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(phenomeModel != phenomeModel2);
	ASSERT_TRUE(phenomeModel->equals(*phenomeModel2));
}
