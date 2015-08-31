//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
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

class JointModelTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointModel = new JointModel();
		jointModel->initialize(NULL, NULL, NULL, btTransform(), btTransform(),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10), JointPhysics::HINGE_JOINT, true,
			true, true, randomness->nextVector(), randomness->nextVector(),
			randomness->nextVector());
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete jointModel;
		jointModel = NULL;
		delete randomness;
		randomness = NULL;
	}
	JointModel* jointModel;
	Randomness* randomness;
};

class JointModelSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		jointModel = new JointModel();
		jointModel->initialize(NULL, NULL, NULL, btTransform(), btTransform(),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10),
			randomness->nextUnifPosInt(0, 10), JointPhysics::HINGE_JOINT, true,
			true, true, randomness->nextVector(), randomness->nextVector(),
			randomness->nextVector());

		jointModel2 = new JointModel();

		SaveController < JointModel > saveController;

		saveController.save(*jointModel, "JointModel.test");

		saveController.restore(*jointModel2, "JointModel.test");
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
	JointModel* jointModel;
	JointModel* jointModel2;
	Randomness* randomness;
};

TEST_F(JointModelTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(JointModelSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(jointModel != jointModel2);
	ASSERT_TRUE(jointModel->equals(*jointModel2));
}

