//# corresponding header
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/SaveController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

class FSJointBtTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointBt = new FSJointBt(NULL, NULL, NULL, btTransform(), btTransform(),
			JointPhysics::HINGE_JOINT, true, true, true,
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()));
		jointBt->initialize();

		jointBt->generateMotors(
			OgreBulletUtils::convert(randomness->nextVector()),
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
	FSJointBt* jointBt;
	Randomness* randomness;
};

class FSJointBtSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointBt = new FSJointBt(NULL, NULL, NULL, btTransform(), btTransform(),
			JointPhysics::HINGE_JOINT, true, true, true,
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()));
		jointBt->generateMotors(
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()));
		jointBt->initialize();

		jointBt2 = new FSJointBt();

		SaveController < FSJointBt > saveController;

		saveController.save(*jointBt, "test/FSJointBt.test");

		saveController.restore(*jointBt2, "test/FSJointBt.test");
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
	FSJointBt* jointBt;
	FSJointBt* jointBt2;
	Randomness* randomness;
};

TEST_F(FSJointBtTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(FSJointBtSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(jointBt != jointBt2);
	ASSERT_TRUE(jointBt->equals(*jointBt2));
}

