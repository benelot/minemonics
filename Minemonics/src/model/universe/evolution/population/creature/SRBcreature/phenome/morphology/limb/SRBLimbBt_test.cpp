//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbBt.hpp>
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

class LimbBtTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbBt = new SRBLimbBt(NULL, NULL,
			(LimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				LimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true);
		limbBt->initialize();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete limbBt;
		limbBt = NULL;
		delete randomness;
		randomness = NULL;
	}
	SRBLimbBt* limbBt;
	Randomness* randomness;
};

class LimbBtSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		limbBt = new SRBLimbBt(NULL, NULL,
			(LimbPhysics::PrimitiveType) randomness->nextUnifPosInt(1,
				LimbPhysics::NUM_PRIMITIVES), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextQuaternion(), randomness->nextVector(),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10),
			Ogre::ColourValue(randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1),
				randomness->nextUnifDouble(0, 1)), true);
		limbBt->initialize();

		limbBt2 = new SRBLimbBt();

		SaveController < SRBLimbBt > saveController;

		saveController.save(*limbBt, "test/SRBLimbBt.test");

		saveController.restore(*limbBt2, "test/SRBLimbBt.test");
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
	SRBLimbBt* limbBt;
	SRBLimbBt* limbBt2;
	Randomness* randomness;
};

TEST_F(LimbBtTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(LimbBtSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(limbBt != limbBt2);
	ASSERT_TRUE(limbBt->equals(*limbBt2));
}

