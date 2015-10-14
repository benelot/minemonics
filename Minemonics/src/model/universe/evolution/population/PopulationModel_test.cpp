//# corresponding header
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <gtest/gtest.h>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/environments/physics/GroundController.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class PopulationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		randomness = new Randomness();
		population = new PopulationModel(NULL,0,Ogre::Vector3(0,0,0));
		physicsController = new GroundController(
			PhysicsController::FeatherstoneModel);
		physicsController->initialize();
		population->initialize();
		for (int i = 0; i < 30; ++i) {
			CreatureModel* creature = new CreatureModel(NULL, PhysicsController::FeatherstoneModel,
				Ogre::Vector3(0, 0, 0), 30);
			creature->setWorld(physicsController->getDynamicsWorld());
			creature->initialize();
			creature->performEmbryogenesis();
			population->addMember(creature);
		}
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete population;
		population = NULL;
		delete ((GroundController*) physicsController);
		physicsController = NULL;
		delete randomness;
		randomness = NULL;
	}
	Randomness* randomness;
	PopulationModel* population;

	PhysicsController* physicsController;
};

class PopulationSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		population = new PopulationModel(NULL,0,Ogre::Vector3(0,0,0));
		physicsController = new GroundController(
			PhysicsController::FeatherstoneModel);
		physicsController->initialize();
		population->initialize();
		for (int i = 0; i < 30; ++i) {
			CreatureModel* creature = new CreatureModel(NULL, PhysicsController::FeatherstoneModel,
				Ogre::Vector3(0, 0, 0), 30);
			creature->setWorld(physicsController->getDynamicsWorld());
			creature->initialize();
			creature->performEmbryogenesis();
			population->addMember(creature);
		}

		population2 = new PopulationModel();

		SaveController < PopulationModel > saveController;

		saveController.save(*population, "test/Population.test");

		saveController.restore(*population2, "test/Population.test");
	}

	virtual void TearDown() {
		delete population;
		population = NULL;
		delete population2;
		population2 = NULL;
		delete ((GroundController*) physicsController);
		physicsController = NULL;
		delete randomness;
		randomness = NULL;
	}
	Randomness* randomness;

	PopulationModel* population;

	PopulationModel* population2;

	PhysicsController* physicsController;
};

TEST_F(PopulationTest,DummyTest) {
	//TODO: Add all tests
	//ASSERT_TRUE(creature->)
}

TEST_F(PopulationSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(population != population2);
	ASSERT_TRUE(population->equals(*population2));
}

