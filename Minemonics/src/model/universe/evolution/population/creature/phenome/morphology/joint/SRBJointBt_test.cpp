//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>
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
		jointBt = new SRBJointBt(NULL, NULL, NULL, btVector3(),
			JointPhysics::HINGE_JOINT,
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()), 0);
		jointBt->initialize();

		jointBt->generateMotors(
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()), true);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointBt;
		jointBt = NULL;
		delete randomness;
		randomness = NULL;
	}
	SRBJointBt* jointBt;
	Randomness* randomness;
};

class JointBtSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointBt = new SRBJointBt(NULL, NULL, NULL, btVector3(),
			JointPhysics::HINGE_JOINT,
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()), 0);
		jointBt->initialize();
		jointBt->generateMotors(
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()),
			OgreBulletUtils::convert(randomness->nextVector()), true);

		jointBt2 = new SRBJointBt();

		SaveController<SRBJointBt> saveController;

		saveController.save(*jointBt, "test/SRBJointBt.test");

		saveController.restore(*jointBt2, "test/SRBJointBt.test");
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
	SRBJointBt* jointBt;
	SRBJointBt* jointBt2;
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

