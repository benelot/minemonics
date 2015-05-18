//# corresponding headers
//# forward declarations
//# system headers
#include <cstdlib>
#include <iterator>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/PopulationConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/morphology/MorphogeneBranch.hpp>
#include <model/universe/evolution/population/creature/genome/MixedGenome.hpp>

//## view headers
//## utils headers
#include <utils/Randomness.hpp>

MixedGenome::MixedGenome() :
		mSegmentsDepthLimit(0), mTotalSegmentQtyLimit(0) {
}

MixedGenome::~MixedGenome() {
	while (!mGenes.empty()) {
		Gene* f = mGenes.back();
		mGenes.pop_back();
		delete f;
	}
}

void MixedGenome::createRandomGenome(double branchiness) {
	mBranchiness = branchiness;

	Randomness randomness;

	int geneQty =
			1
					+ abs(
							randomness.nextNormalInt(
									PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN,
									PopulationConfiguration::POPULATION_GENES_INITIAL_VAR));
	for (int i = 0; i < geneQty; i++) {
		Morphogene* gene = new Morphogene();
		gene->initialize(branchiness);
		mGenes.push_back(gene);
	}

	mSegmentsDepthLimit = abs(
			randomness.nextNormalInt(
					MorphologyConfiguration::LIMB_DEPTH_INITIAL_MEAN,
					MorphologyConfiguration::LIMB_DEPTH_INITIAL_VAR));

	mTotalSegmentQtyLimit = abs(
			randomness.nextNormalInt(
					MorphologyConfiguration::LIMB_TOTAL_INITIAL_MEAN,
					MorphologyConfiguration::LIMB_TOTAL_INITIAL_VAR));
}

bool MixedGenome::equals(const MixedGenome & genome) const {

	std::vector<Gene*>::const_iterator it = mGenes.begin();
	std::vector<Gene*>::const_iterator it2 = genome.getConstGenes().begin();
	for (; it != mGenes.end(), it2 != genome.getConstGenes().end(); it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;
}

void MixedGenome::addRandomGenes() {
	//TODO: Implement method.
}

void MixedGenome::addRandomGene() {
	Randomness randomness;
	Gene::GeneType type = (Gene::GeneType)randomness.nextPosInt(0, Gene::NUM_GENES);
	Gene* gene;
	switch (type) {
	case Gene::MorphoGene: {
		gene = new Morphogene();
		((Morphogene*) gene)->initialize(mBranchiness);
	}
		break;
	default:
		break;
	}
}

void MixedGenome::integrateRandomGenes() {
	Randomness randomness;

	//TODO:: Only links morphology and not controller, might break with a controller
	for (int geneIt = 0; geneIt < mGenes.size(); geneIt++) {

		switch (mGenes[geneIt]->getGeneType()) {
		case Gene::MorphoGene: {
			// randomly choose a follow up gene until you get one different from its own type
			do {
				((Morphogene*) mGenes[geneIt])->setFollowUpGene(
						randomness.nextPosInt(0, mGenes.size() - 1));
			} while (((Morphogene*) mGenes[geneIt])->getFollowUpGene() != geneIt);

			std::vector<MorphogeneBranch*>::iterator branchIt =
					((Morphogene*) mGenes[geneIt])->getGeneBranches().begin();
			for (;
					branchIt
							!= ((Morphogene*) mGenes[geneIt])->getGeneBranches().end();
					branchIt++) {

				//randomly choose a branch gene type until you get one distinct from the follow up gene
				do {
					(*branchIt)->setBranchGeneType(
							randomness.nextPosInt(0, mGenes.size() - 1));
				} while (mGenes.size() > 1
						&& (*branchIt)->getBranchGeneType()
								== ((Morphogene*) mGenes[geneIt])->getFollowUpGene());

			}
			break;
		}
		default:
			break;
		}
	}
}

void MixedGenome::integrateRandomGene() {
	//TODO: Implement method.
}

void MixedGenome::integrateGene(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::replaceRandomGenesWithRandomGenes() {
	//TODO: Implement method.
}

void MixedGenome::replaceRandomGeneWithRandomGene() {
	//TODO: Implement method.
}

void MixedGenome::replaceGeneWith(int geneIndex, int replacementIndex) {
	//TODO: Implement method.
}

void MixedGenome::duplicateRandomGenes() {
	//TODO: Implement method.
}

void MixedGenome::duplicateRandomGene() {
	//TODO: Implement method.
}

void MixedGenome::duplicateGene(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::splitRandomGenes() {
	//TODO: Implement method.
}

void MixedGenome::splitRandomGene() {
	//TODO: Implement method.
}

void MixedGenome::splitGene(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::growRandomStubs() {
	//TODO: Implement method.
}

void MixedGenome::growRandomStub() {
	//TODO: Implement method.
}

void MixedGenome::growStub(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::mutateRandomGenes() {
	//TODO: Implement method.
}

void MixedGenome::mutateRandomGene() {
	//TODO: Implement method.
}

void MixedGenome::mutateGene(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::mutateRandomBranches() {
	//TODO: Implement method.
}

void MixedGenome::mutateRandomBranch() {
	//TODO: Implement method.
}

void MixedGenome::mutateBranch(int geneIndex, int branchIndex) {
	//TODO: Implement method.
}

void MixedGenome::crossoverRandomly(Genome* genome) {
	//TODO: Implement method.
}

void MixedGenome::crossover(Genome* genome, int fatherSegmentIndex,
		int motherSegmentIndex) {
	//TODO: Implement method.
}

void MixedGenome::graftFrom(Genome* donator, int maxLinkDepth) {
	//TODO: Implement method.
}
