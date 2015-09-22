//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
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

class FSLimbBtTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbBt = new FSLimbBt();
		limbBt->initialize(NULL, NULL,
			(FSLimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				FSLimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			OgreBulletUtils::convert(randomness->nextQuaternion()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextQuaternion()),
			randomness->nextVector(), randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete limbBt;
		limbBt = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSLimbBt* limbBt;
	Randomness* randomness;
};

class FSLimbBtSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbBt = new FSLimbBt();
		limbBt->initialize(NULL, NULL,
			(FSLimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				FSLimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			OgreBulletUtils::convert(randomness->nextQuaternion()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextQuaternion()),
			randomness->nextVector(), randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true);

		limbBt2 = new FSLimbBt();

		SaveController < FSLimbBt > saveController;

		saveController.save(*limbBt, "LimbBt.test");

		saveController.restore(*limbBt2, "LimbBt.test");
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete limbBt;
		limbBt = NULL;
		delete limbBt2;
		limbBt2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSLimbBt* limbBt;
	FSLimbBt* limbBt2;
	Randomness* randomness;
};

TEST_F(FSLimbBtTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(FSLimbBtSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(limbBt != limbBt2);
	ASSERT_TRUE(limbBt->equals(*limbBt2));
}

