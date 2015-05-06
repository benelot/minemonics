/*
 * Creature_test.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/SaveController.hpp>
#include <gtest/gtest.h>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers

//## controller headers

//## model headers
//## view headers
//## utils headers

class CreatureTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		creature = new CreatureModel();
		creature->initialize(Ogre::Vector3(0,0,0),30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete creature;
		creature = NULL;
	}
	CreatureModel* creature;
};

class CreatureSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		creature = new CreatureModel();
		creature->initialize(Ogre::Vector3(0,0,0),30);

		creature2 = new CreatureModel();

		SaveController<CreatureModel> saveController;

		saveController.save(*creature, "Creature.test");

		saveController.restore(*creature2, "Creature.test");
	}

	virtual void TearDown() {
		delete creature;
		creature = 0;
		delete creature2;
		creature2 = 0;
	}
	CreatureModel* creature;

	CreatureModel* creature2;
};

TEST_F(CreatureTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(CreatureSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(creature != creature2);
	ASSERT_TRUE(creature->equals(*creature2));
}

