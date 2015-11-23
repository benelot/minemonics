//# corresponding header
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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

class FSJointModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointModel = new FSJointModel(NULL, NULL, NULL,
			randomness->nextVector(), randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10), JointPhysics::HINGE_JOINT,
			randomness->nextVector(), randomness->nextVector(),
			randomness->nextVector(), randomness->nextVector());
		jointModel->initialize();
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointModel;
		jointModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSJointModel* jointModel;
	Randomness* randomness;
};

class FSJointModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointModel = new FSJointModel(NULL, NULL, NULL,
			randomness->nextVector(), randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10), JointPhysics::HINGE_JOINT,
			randomness->nextVector(), randomness->nextVector(),
			randomness->nextVector(), randomness->nextVector());
		jointModel->initialize();

		jointModel2 = new FSJointModel();

		SaveController<FSJointModel> saveController;

		saveController.save(*jointModel, "test/FSJointModel.test");

		saveController.restore(*jointModel2, "test/FSJointModel.test");
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointModel;
		jointModel = NULL;
		delete jointModel2;
		jointModel2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSJointModel* jointModel;
	FSJointModel* jointModel2;
	Randomness* randomness;
};

TEST_F(FSJointModelTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(FSJointModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(jointModel != jointModel2);
	ASSERT_TRUE(jointModel->equals(*jointModel2));
}

