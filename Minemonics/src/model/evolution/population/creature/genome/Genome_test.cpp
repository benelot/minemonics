/*
 * Genome_test.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Genome.h"

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
#include "configuration/PopulationConfiguration.h"

class GenomeTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		// Set up an object of the class you want to test
		genome = new Genome();
		genome->createRandomGenome(30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete genome;
		genome = 0;
	}
	Genome* genome;
};


class GenomeSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		genome = new Genome();
		genome->createRandomGenome(30);

		genome2 = new Genome();

		SaveController<Genome> saveController;

		saveController.save(*genome,"Genome.test");

		saveController.restore(*genome2,"Genome.test");
	}

	virtual void TearDown() {
		delete genome;
		genome = 0;
		delete genome2;
		genome2 = 0;
	}
	Genome* genome;

	Genome* genome2;
};


TEST_F(GenomeTest,DummyTest) {
	ASSERT_TRUE(PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN - PopulationConfiguration::POPULATION_GENES_INITIAL_VAR <= genome->getGenes().size() <= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN + PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(GenomeSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(genome != genome2);
	ASSERT_TRUE(genome->equals(*genome2));
}


