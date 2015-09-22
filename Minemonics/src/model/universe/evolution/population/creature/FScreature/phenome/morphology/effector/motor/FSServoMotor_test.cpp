//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>
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

class FSServoMotorTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		servoMotor = new FSServoMotor();
		servoMotor->initialize(FSJointPhysics::RDOF_PITCH,
			randomness->nextUnifDouble(1, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10));
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete servoMotor;
		servoMotor = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSServoMotor* servoMotor;
	Randomness* randomness;
};

class FSServoMotorSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		servoMotor = new FSServoMotor();
		servoMotor->initialize(FSJointPhysics::RDOF_PITCH,
			randomness->nextUnifDouble(1, 10),
			randomness->nextUnifDouble(0, 10),
			randomness->nextUnifDouble(0, 10));

		servoMotor2 = new FSServoMotor();

		SaveController < FSServoMotor > saveController;

		saveController.save(*servoMotor, "ServoMotor.test");

		saveController.restore(*servoMotor2, "ServoMotor.test");
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete servoMotor;
		servoMotor = NULL;
		delete servoMotor2;
		servoMotor2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	FSServoMotor* servoMotor;
	FSServoMotor* servoMotor2;
	Randomness* randomness;
};

TEST_F(FSServoMotorTest,hasNormalGenes) {
//	ASSERT_TRUE(
//	PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
//	<= genome->getGenes().size()
//	<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
//	+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(FSServoMotorSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(servoMotor != servoMotor2);
	ASSERT_TRUE(servoMotor->equals(*servoMotor2));
}

