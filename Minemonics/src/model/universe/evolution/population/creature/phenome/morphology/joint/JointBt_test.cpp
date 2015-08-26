//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
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

class JointBtTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointBt = new JointBt();
		jointBt->initialize(NULL, NULL, NULL, btTransform(), btTransform(),
		OgreBulletUtils::convert(randomness->nextVector()),
		OgreBulletUtils::convert(randomness->nextVector()));
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointBt;
		jointBt = NULL;
		delete randomness;
		randomness = NULL;
	}
	JointBt* jointBt;
	Randomness* randomness;
};

class JointBtSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointBt = new JointBt();
		jointBt->initialize(NULL, NULL, NULL, btTransform(), btTransform(),
		OgreBulletUtils::convert(randomness->nextVector()),
		OgreBulletUtils::convert(randomness->nextVector()));

		jointBt2 = new JointBt();

		SaveController<JointBt> saveController;

		saveController.save(*jointBt, "JointBt.test");

		saveController.restore(*jointBt2, "JointBt.test");
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointBt;
		jointBt = NULL;
		delete jointBt2;
		jointBt2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	JointBt* jointBt;
	JointBt* jointBt2;
	Randomness* randomness;
};

TEST_F(JointBtTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(JointBtSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(jointBt != jointBt2);
	ASSERT_TRUE(jointBt->equals(*jointBt2));
}

