//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Genome.hpp>

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

Genome::Genome(GenomeType type) :
		mLength(0), mGenomeType(type),mBranchiness(0) {
}

Genome::~Genome() {
}

void Genome::addGene(Gene* gene) {
	mGenes.push_back(gene);
}
