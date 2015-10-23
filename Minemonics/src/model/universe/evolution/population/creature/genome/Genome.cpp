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
	mLength(0), mGenomeType(type), mBranchiness(0), mRootIndex(0) {
}

Genome::~Genome() {
	for (std::vector<Gene*>::iterator git = mGenes.begin(); git != mGenes.end();
		git++) {
		delete *git;
	}

	mGenes.clear();
}

void Genome::addGene(Gene* gene) {
	mGenes.push_back(gene);
}

bool Genome::equals(const Genome& genome) const {

	if (mGenomeType != genome.mGenomeType) { /**!< Compare the type of genome*/
		return false;
	}

	if (mLength != genome.mLength) { /**!< The length of the genome*/
		return false;
	}

	if (mGenes.size() != genome.getGenes().size()) { /**!< Compare the vector of genes.*/
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
