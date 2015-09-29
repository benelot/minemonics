//# corresponding header
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>
#include <gtest/gtest.h>

//## controller headers
//## model headers
#include <boost/math/constants/constants.hpp>
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PopulationConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

class MixedGenomeTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();
		// Set up an object of the class you want to test
		genome = new MixedGenome();
		genome->createRandomGenome(30);
	}

	virtual void TearDown() {
		// delete and set the pointer to zero
		delete genome;
		genome = NULL;
		delete randomness;
		randomness = NULL;
	}
	MixedGenome* genome;
	Randomness* randomness;
};

class MixedGenomeSerializationTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		randomness = new Randomness();

		genome = new MixedGenome();
		genome->createRandomGenome(30);

		genome2 = new MixedGenome();

		SaveController < MixedGenome > saveController;

		saveController.save(*genome, "test/MixedGenome.test");

		saveController.restore(*genome2, "test/MixedGenome.test");
	}

	virtual void TearDown() {
		delete genome;
		genome = NULL;
		delete genome2;
		genome2 = NULL;
		delete randomness;
		randomness = NULL;
	}
	MixedGenome* genome;

	MixedGenome* genome2;

	Randomness* randomness;
};

TEST_F(MixedGenomeTest,hasNormalGenes) {
	ASSERT_TRUE(
		PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
		- PopulationConfiguration::POPULATION_GENES_INITIAL_VAR
		<= genome->getGenes().size()
		<= PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN
		+ PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
}

TEST_F(MixedGenomeTest,areAllBranchesSet) {
	for (std::vector<Gene*>::const_iterator geneIt = genome->getGenes().begin();
		geneIt != genome->getGenes().end(); geneIt++) {
		if ((*geneIt)->getType() == Gene::MorphoGene) {
			for (std::vector<MorphogeneBranch*>::const_iterator branchIt =
				((Morphogene*) (*geneIt))->getGeneBranches().begin();
				branchIt
				!= ((Morphogene*) (*geneIt))->getGeneBranches().end();
				branchIt++) {
				ASSERT_TRUE((*branchIt)->getBranchGeneType() != -1);
			}
		}
	}
}

TEST_F(MixedGenomeSerializationTest,isEqualAfterSerialization) {
	ASSERT_TRUE(genome != genome2);
	ASSERT_TRUE(genome->equals(*genome2));
}

