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

class FSLimbModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbModel = new FSLimbModel();
		limbModel->initialize(NULL, NULL,
			(FSLimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				FSLimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
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
	FSLimbModel* limbModel;
	Randomness* randomness;
};

class FSLimbModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbModel = new FSLimbModel();
		limbModel->initialize(NULL, NULL,
			(FSLimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				FSLimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true,
			randomness->nextUnifPosInt(0, 10));

		limbModel2 = new FSLimbModel();

		SaveController < FSLimbModel > saveController;

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
	FSLimbModel* limbModel;
	FSLimbModel* limbModel2;
	Randomness* randomness;
};

TEST_F(FSLimbModelTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(FSLimbModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(limbModel != limbModel2);
	ASSERT_TRUE(limbModel->equals(*limbModel2));
}

