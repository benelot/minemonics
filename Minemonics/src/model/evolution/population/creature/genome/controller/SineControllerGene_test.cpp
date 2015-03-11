/*
 * SineControllerGene_test.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "SineControllerGene.h"

//# forward declarations

//# system headers
#include <gtest/gtest.h>
//## controller headers

//## model headers
#include <boost/math/constants/constants.hpp>
//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers
#include "controller/SaveController.h"

//## model headers

//## view headers

//## utils headers
#include "configuration/ControlConfiguration.h"

class SineControllerGeneTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		sineControllerGene = new SineControllerGene();
		sineControllerGene->initialize();
	}

	virtual void TearDown() {
		delete sineControllerGene;
		sineControllerGene = 0;
	}
	SineControllerGene* sineControllerGene;
};


class SineControllerGeneSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		sineControllerGene = new SineControllerGene();
		sineControllerGene->initialize();

		sineControllerGene2 = new SineControllerGene();

		SaveController<SineControllerGene> saveController;

		saveController.save(*sineControllerGene,"Controller.test");

		saveController.restore(*sineControllerGene2,"Controller.test");
	}

	virtual void TearDown() {
		delete sineControllerGene;
		sineControllerGene = 0;
		delete sineControllerGene2;
		sineControllerGene2 = 0;
	}
	SineControllerGene* sineControllerGene;

	SineControllerGene* sineControllerGene2;
};


TEST_F(SineControllerGeneTest,DummyTest) {
	ASSERT_TRUE(
			0 <= sineControllerGene->getInitialValue()
					<= 2 * boost::math::constants::pi<double>());
	ASSERT_TRUE(
			0 <= sineControllerGene->getAmplitude()
					<= ControlConfiguration::CPG_SINE_INITIAL_MAX_AMPLITUDE);
	ASSERT_TRUE(
			0 <= sineControllerGene->getFrequency()
					<= ControlConfiguration::CPG_SINE_INITIAL_MAX_FREQUENCY);
}

TEST_F(SineControllerGeneSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(sineControllerGene != sineControllerGene2);
	ASSERT_TRUE(sineControllerGene->equals(*sineControllerGene2));
}
