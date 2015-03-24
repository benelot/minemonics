/*
 * Genome.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Genome.h"

//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers
#include "configuration/PopulationConfiguration.h"
#include "configuration/MorphologyConfiguration.h"
#include "utils/Randomness.h"
/*
 * The genetic representation of this morphology is a directed graph of
 * nodes and connections. Each graph contains the developmental instructions
 * for growing a creature, and provides a way of reusing instructions to
 * make similar or recursive components within the creature. A phenotype
 * hierarchy of parts is made from a graph by starting at a defined
 * root-node and synthesizing parts from the node information while tracing
 * through the connections of the graph. The graph can be recurrent. Nodes
 * can connect to themselves or in cycles to form recursive or fractal like
 * structures. They can also connect to the same child multiple times to
 * make duplicate instances of the same appendage.
 */
Genome::Genome():mSegmentsDepthLimit(0), mTotalSegmentQtyLimit(0) {

}

Genome::~Genome() {
	while (!mGenes.empty()) {
		MorphoGene* f = mGenes.back();
		mGenes.pop_back();
		delete f;
	}
}

void Genome::createRandomGenome(double bushiness) {
	Randomness randomness;

	int geneQty = randomness.nextNormalInt(
			PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN,
			PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
	for (int i = 0; i < geneQty; i++) {
		MorphoGene* gene = new MorphoGene();
		gene->initialize(bushiness);
		mGenes.push_back(gene);
	}

	mSegmentsDepthLimit = abs(
			randomness.nextNormalInt(
					MorphologyConfiguration::BODY_SEGMENTS_DEPTH_INITIAL_MEAN,
					MorphologyConfiguration::BODY_SEGMENTS_DEPTH_INITIAL_VAR));

	mTotalSegmentQtyLimit = abs(
			randomness.nextNormalInt(
					MorphologyConfiguration::BODY_SEGMENTS_TOTAL_INITIAL_MEAN,
					MorphologyConfiguration::BODY_SEGMENTS_TOTAL_INITIAL_VAR));
}

void Genome::addGene(MorphoGene* gene) {
	mGenes.push_back(gene);
}

void Genome::linkRandomGenes() {
	Randomness randomness;
	std::vector<MorphoGene*>::iterator geneIt = mGenes.begin();
	for (; geneIt != mGenes.end(); geneIt++) {
		std::vector<MorphoGeneBranch*>::iterator branchIt =
				(*geneIt)->getGeneBranches().begin();
		for (; branchIt != (*geneIt)->getGeneBranches().end(); branchIt++) {
			(*branchIt)->setBranchGeneType(
					randomness.nextPosInt(0, mGenes.size()));
		}
	}
}

bool Genome::equals(const Genome & genome) const {

	std::vector<MorphoGene*>::const_iterator it = mGenes.begin();
	std::vector<MorphoGene*>::const_iterator it2 = genome.mGenes.begin();
	for (; it != mGenes.end(), it2 != genome.mGenes.end(); it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;
}

