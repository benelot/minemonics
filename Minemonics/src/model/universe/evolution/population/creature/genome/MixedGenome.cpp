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

	repairGenes();
}

bool MixedGenome::equals(const MixedGenome & genome) const {

	std::vector<Gene*>::const_iterator it = mGenes.begin();
	std::vector<Gene*>::const_iterator it2 = genome.getConstGenes().begin();
	for (; it != mGenes.end(), it2 != genome.getConstGenes().end();
			it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;
}

void MixedGenome::addRandomGenes(double percentage) {
	Randomness randomness;
	//TODO:Add reasonable number
	for (int i = 0; i < 10; i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			addRandomGene();
		}
	}
}

void MixedGenome::addRandomGene() {
	Randomness randomness;
	Gene::GeneType type = (Gene::GeneType) randomness.nextPosInt(0,
			Gene::NUM_GENES);
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

void MixedGenome::repairGenes(){
	integrateRandomGenes(1);
}

void MixedGenome::integrateRandomGenes(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			integrateGene(i);
		}
	}
}

void MixedGenome::integrateRandomGene() {
	Randomness randomness;
	integrateGene(randomness.nextPosInt(0, mGenes.size() - 1));
}

void MixedGenome::integrateGene(int geneIndex) {
	//TODO:: Only links morphology and not controller, might break with a controller
	Randomness randomness;
	switch (mGenes[geneIndex]->getGeneType()) {
	case Gene::MorphoGene: {
		// randomly choose a follow up gene until you get one different from its own type
		do {
			((Morphogene*) mGenes[geneIndex])->setFollowUpGene(
					randomness.nextPosInt(0, mGenes.size() - 1));
		} while (((Morphogene*) mGenes[geneIndex])->getFollowUpGene()
				!= geneIndex);

		std::vector<MorphogeneBranch*>::iterator branchIt =
				((Morphogene*) mGenes[geneIndex])->getGeneBranches().begin();
		for (;
				branchIt
						!= ((Morphogene*) mGenes[geneIndex])->getGeneBranches().end();
				branchIt++) {

			//randomly choose a branch gene type until you get one distinct from the follow up gene
			do {
				(*branchIt)->setBranchGeneType(
						randomness.nextPosInt(0, mGenes.size() - 1));
			} while (mGenes.size() > 1
					&& (*branchIt)->getBranchGeneType()
							== ((Morphogene*) mGenes[geneIndex])->getFollowUpGene());

		}
		break;
	}
	default:
		break;
	}
}

void MixedGenome::replaceRandomGenesWithRandomGenes(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			int replacementIndex = randomness.nextPosInt(0, mGenes.size() - 1);
			replaceGeneWith(i, replacementIndex);
		}
	}
}

void MixedGenome::replaceRandomGeneWithRandomGene() {
	Randomness randomness;
	int geneIndex = randomness.nextPosInt(0, mGenes.size() - 1);
	int replacementIndex = randomness.nextPosInt(0, mGenes.size() - 1);
	replaceGeneWith(geneIndex, replacementIndex);
}

void MixedGenome::replaceGeneWith(int geneIndex, int replacementIndex) {
	Gene* gene = mGenes[geneIndex];
	mGenes[geneIndex] = mGenes[replacementIndex]->clone();
	delete gene;
}

void MixedGenome::duplicateRandomGenes(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			duplicateGene(i);
		}
	}
}

void MixedGenome::duplicateRandomGene() {
	Randomness randomness;
	duplicateGene(randomness.nextPosInt(0, mGenes.size() - 1));
}

void MixedGenome::duplicateGene(int geneIndex) {
	mGenes.push_back(mGenes[geneIndex]->clone());
}

void MixedGenome::splitRandomGenes(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			splitGene(i);
		}
	}
}

void MixedGenome::splitRandomGene() {
	Randomness randomness;

	splitGene(randomness.nextPosInt(0, mGenes.size() - 1));
}

void MixedGenome::splitGene(int geneIndex) {
	//TODO: Implement method.
}

void MixedGenome::growRandomStubs(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			//TODO: Replace with reasonable number
			int branchiness = randomness.nextDouble(0, 3);
			growStub(i, branchiness);
		}
	}
}

void MixedGenome::growRandomStub() {
	Randomness randomness;
	int geneIndex = randomness.nextPosInt(0, mGenes.size() - 1);
	//TODO: Replace with reasonable number
	int branchiness = randomness.nextDouble(0, 3);
	growStub(geneIndex, branchiness);
}

void MixedGenome::growStub(int geneIndex, int branchiness) {
	mGenes[geneIndex]->grow(branchiness);
}

void MixedGenome::mutateRandomGenes(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			mutateGene(i);
		}
	}
}

void MixedGenome::mutateRandomGene() {
	Randomness randomness;

	mutateGene(randomness.nextPosInt(0, mGenes.size() - 1));
}

void MixedGenome::mutateGene(int geneIndex) {
	mGenes[geneIndex]->mutate();
}

void MixedGenome::mutateRandomBranches(double percentage) {
	Randomness randomness;
	for (int i = 0; i < mGenes.size(); i++) {
		if (randomness.nextPosInt(0, 1000.0f) / 1000.0f <= percentage) {
			mutateRandomBranchOfGene(i);
		}
	}
}

void MixedGenome::mutateRandomBranch() {
	int geneIndex;
	Randomness randomness;

	//TODO: This can freeze up in case of certain genomes
	do {
		geneIndex = randomness.nextPosInt(0, mGenes.size() - 1);
	} while (mGenes[geneIndex]->getGeneType() != Gene::MorphoGene);

	mutateBranch(geneIndex,
			((Morphogene*) mGenes[geneIndex])->getGeneBranches().size());
}

void MixedGenome::mutateRandomBranchOfGene(int geneIndex) {
	if (mGenes[geneIndex]->getGeneType() == Gene::MorphoGene) {
		mutateBranch(geneIndex,
				((Morphogene*) mGenes[geneIndex])->getGeneBranches().size());
	}
}

void MixedGenome::mutateBranch(int geneIndex, int branchIndex) {
	if (mGenes[geneIndex]->getGeneType() == Gene::MorphoGene) {
		((Morphogene*) mGenes[geneIndex])->getGeneBranches()[branchIndex]->mutate();
	}
}

void MixedGenome::crossoverRandomly(Genome* genome) {
	Randomness randomness;
	int motherStartSegmentIndex = randomness.nextPosInt(0, mGenes.size() - 1);
	int motherEndSegmentIndex = randomness.nextPosInt(motherStartSegmentIndex,
			mGenes.size() - 1);

	int fatherStartSegmentIndex = randomness.nextPosInt(0,
			genome->getGenes().size() - 1);
	int fatherEndSegmentIndex = randomness.nextPosInt(motherStartSegmentIndex,
			genome->getGenes().size() - 1);

	crossover(genome, motherStartSegmentIndex, motherEndSegmentIndex,
			fatherStartSegmentIndex, fatherEndSegmentIndex);
}

void MixedGenome::crossover(Genome* fathergenome, int motherSegmentStartIndex,
		int motherSegmentEndIndex, int fatherSegmentStartIndex,
		int fatherSegmentEndIndex) {
	for (int i = mGenes.size(); i > motherSegmentEndIndex; i--) {
		Gene* gene = mGenes[i];
		mGenes.erase(mGenes.begin() + i);
		delete gene;
	}

	for (int i = 0; i < motherSegmentStartIndex; i++) {
		Gene* gene = mGenes[0];
		mGenes.erase(mGenes.begin());
	}

	for (int i = fatherSegmentStartIndex; i < fatherSegmentEndIndex; i++) {
		mGenes.push_back(fathergenome->getGenes()[i]->clone());
	}
}

void MixedGenome::graftFrom(Genome* donator, int maxLinkDepth) {
	//TODO: Implement method.
}
