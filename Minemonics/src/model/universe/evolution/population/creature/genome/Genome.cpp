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
		mLength(0), mGenomeType(type), mBranchiness(0) {
}

Genome::~Genome() {
}

void Genome::addGene(Gene* gene) {
	mGenes.push_back(gene);
}

bool Genome::equals(const Genome& genome) const {

	/**Compare the type of genome*/
	if (mGenomeType != genome.mGenomeType) {
		return false;
	}

	/**The length of the genome*/
	if (mLength != genome.mLength) {
		return false;
	}

	/**Compare the vector of genes.*/
	if (mGenes.size() != genome.getGenes().size()) {
		return false;
	}
	std::vector<Gene*>::const_iterator it = mGenes.begin();
	std::vector<Gene*>::const_iterator it2 = genome.getGenes().begin();
	for (; it != mGenes.end(), it2 != genome.getGenes().end(); it++, it2++) {
		if (!(*it)->equals(**it2)) {
			return false;
		}
	}

	return true;
}
