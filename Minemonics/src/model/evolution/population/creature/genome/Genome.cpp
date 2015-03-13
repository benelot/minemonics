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
Genome::Genome() {
	// TODO Auto-generated constructor stub

}

Genome::~Genome() {
	// TODO Auto-generated destructor stub
}

void Genome::createRandomGenome(double bushiness) {
	Randomness randomness;

	int geneQty = randomness.nextNormalInt(
			PopulationConfiguration::POPULATION_GENES_INITIAL_MEAN,
			PopulationConfiguration::POPULATION_GENES_INITIAL_VAR);
	for (int i = 1; i < geneQty; i++) {
		MorphoGene gene;
		gene.initialize(bushiness);
		mGenes.push_back(gene);
	}
}

bool Genome::equals(const Genome & genome) {

	std::vector<MorphoGene>::const_iterator it = mGenes.begin();
	std::vector<MorphoGene>::const_iterator it2 = genome.mGenes.begin();
	for (; it != mGenes.end(), it2 != genome.mGenes.end(); it++, it2++) {
		if (!it->equals(*(it2))) {
			return false;
		}
	}

	return true;
}

