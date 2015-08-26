//# corresponding headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
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

class CreatureModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();

		creature = new CreatureModel();
		physicsController = new PhysicsController();
		physicsController->initBulletPhysics();
		creature->setWorld(physicsController->getDynamicsWorld());
		creature->initialize(NULL, Ogre::Vector3(0, 0, 0), 30);
		creature->performEmbryogenesis();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete creature;
		creature = NULL;
		delete randomness;
		randomness = NULL;
		delete physicsController;
		physicsController = NULL;
	}
	CreatureModel* creature;

	PhysicsController* physicsController;

	Randomness* randomness;
};

class CreatureModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		creature = new CreatureModel();
		physicsController = new PhysicsController();
		physicsController->initBulletPhysics();
		creature->setWorld(physicsController->getDynamicsWorld());
		creature->initialize(NULL, Ogre::Vector3(0, 0, 0), 30);
		creature->performEmbryogenesis();

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
		delete physicsController;
		physicsController = NULL;

	}
	CreatureModel* creature;

	CreatureModel* creature2;

	PhysicsController* physicsController;

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

