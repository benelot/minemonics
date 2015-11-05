//# corresponding headers
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
#include <configuration/MorphologyConfiguration.hpp>
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/environments/physics/GroundController.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class CreatureModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		physicsController = new GroundController(
			PhysicsController::FeatherstoneModel);
		physicsController->initialize();
		creature = new CreatureModel(NULL, PhysicsController::FeatherstoneModel,
			Ogre::Vector3(0, 0, 0));
		creature->createRandomGenome(30);
		creature->setWorld(physicsController->getDynamicsWorld());
		creature->initialize();
		creature->performEmbryogenesis();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete creature;
		creature = NULL;
		delete ((GroundController*) physicsController);
		physicsController = NULL;
		delete randomness;
		randomness = NULL;
	}
	CreatureModel* creature;

	Randomness* randomness;
	PhysicsController* physicsController;
};

class CreatureModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		physicsController = new GroundController(
			PhysicsController::FeatherstoneModel);
		physicsController->initialize();
		creature = new CreatureModel(NULL, PhysicsController::FeatherstoneModel,
			Ogre::Vector3(0, 0, 0));
		creature->createRandomGenome(30);
		creature->setWorld(physicsController->getDynamicsWorld());
		creature->initialize();
		creature->performEmbryogenesis();

		creature2 = new CreatureModel();

		SaveController < CreatureModel > saveController;

		saveController.save(*creature, "test/CreatureModel.test");

		saveController.restore(*creature2, "test/CreatureModel.test");
	}

	virtual void TearDown() {
		delete creature;
		creature = NULL;
		delete creature2;
		creature2 = NULL;
		delete ((GroundController*) physicsController);
		physicsController = NULL;
		delete randomness;
		randomness = NULL;
	}
	CreatureModel* creature;

	CreatureModel* creature2;

	Randomness* randomness;

	PhysicsController* physicsController;
};

TEST_F(CreatureModelTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(CreatureModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(creature != creature2);
	ASSERT_TRUE(creature->equals(*creature2));
}

