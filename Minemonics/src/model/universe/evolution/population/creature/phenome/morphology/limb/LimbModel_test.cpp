//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

class LimbModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbModel = new LimbModel();
		limbModel->initialize(NULL, NULL,
			(LimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				LimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true,
			randomness->nextUnifPosInt(0, 10));
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete limbModel;
		limbModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	LimbModel* limbModel;
	Randomness* randomness;
};

class LimbModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbModel = new LimbModel();
		limbModel->initialize(NULL, NULL,
			(LimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				LimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true,
			randomness->nextUnifPosInt(0, 10));

		limbModel2 = new LimbModel();

		SaveController < LimbModel > saveController;

		saveController.save(*limbModel, "LimbModel.test");

		saveController.restore(*limbModel2, "LimbModel.test");
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		// delete and set the pointer to zero
		delete limbModel;
		limbModel = NULL;
		delete limbModel2;
		limbModel2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	LimbModel* limbModel;
	LimbModel* limbModel2;
	Randomness* randomness;
};

TEST_F(LimbModelTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(LimbModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(limbModel != limbModel2);
	ASSERT_TRUE(limbModel->equals(*limbModel2));
}

