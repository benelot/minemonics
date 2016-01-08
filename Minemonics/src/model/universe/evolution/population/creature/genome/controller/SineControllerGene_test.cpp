/*
 * SineControllerGene_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <model/universe/evolution/population/creature/genome/controller/SineControllerGene.hpp>

//## controller headers
//## model headers
#include <gtest/gtest.h>
#include <boost/math/constants/constants.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/ControlConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class SineControllerGeneTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		sineControllerGene = new SineControllerGene();
		sineControllerGene->initialize();
	}

	virtual void TearDown() {
		delete randomness;
		randomness = NULL;
		delete sineControllerGene;
		sineControllerGene = NULL;
	}
	SineControllerGene* sineControllerGene;
	Randomness* randomness;
};

class SineControllerGeneSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		sineControllerGene = new SineControllerGene();
		sineControllerGene->initialize();

		sineControllerGene2 = new SineControllerGene();

		SaveController < SineControllerGene > saveController;

		saveController.save(*sineControllerGene, "test/SineController.test");

		saveController.restore(*sineControllerGene2,
			"test/SineController.test");
	}

	virtual void TearDown() {
		delete sineControllerGene;
		sineControllerGene = NULL;
		delete sineControllerGene2;
		sineControllerGene2 = NULL;
	}
	SineControllerGene* sineControllerGene;

	SineControllerGene* sineControllerGene2;
};

TEST_F(SineControllerGeneTest,DummyTest) {
	ASSERT_TRUE(
		0 <= sineControllerGene->getXOffset()
		<= 2 * boost::math::constants::pi<double>());

	ASSERT_TRUE(-1 <= sineControllerGene->getYOffset() <= 1);
	ASSERT_TRUE(
		ControlConfiguration::SINE_MIN_AMPLITUDE <= sineControllerGene->getAmplitude()
		<= ControlConfiguration::SINE_MAX_AMPLITUDE);
	ASSERT_TRUE(
		ControlConfiguration::SINE_MIN_FREQUENCY <= sineControllerGene->getFrequency()
		<= ControlConfiguration::SINE_MAX_FREQUENCY);
}

TEST_F(SineControllerGeneSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(sineControllerGene != sineControllerGene2);
	ASSERT_TRUE(sineControllerGene->equals(*sineControllerGene2));
}
