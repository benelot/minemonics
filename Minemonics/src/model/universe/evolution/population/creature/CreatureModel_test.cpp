//# corresponding headers
#include <configuration/MorphologyConfiguration.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <gtest/gtest.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class CreatureModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		creature = new CreatureModel();
		creature->initialize(NULL, Ogre::Vector3(0, 0, 0), 30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete creature;
		creature = NULL;
		delete randomness;
		randomness = NULL;
	}
	CreatureModel* creature;

	Randomness* randomness;
};

class CreatureModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		creature = new CreatureModel();
		creature->initialize(NULL, Ogre::Vector3(0, 0, 0), 30);

		creature2 = new CreatureModel();

		SaveController<CreatureModel> saveController;

		saveController.save(*creature, "Creature.test");

		saveController.restore(*creature2, "Creature.test");
	}

	virtual void TearDown() {
		delete creature;
		creature = NULL;
		delete creature2;
		creature2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	CreatureModel* creature;

	CreatureModel* creature2;

	Randomness* randomness;
};

TEST_F(CreatureModelTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(CreatureModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(creature != creature2);
	ASSERT_TRUE(creature->equals(*creature2));
}

