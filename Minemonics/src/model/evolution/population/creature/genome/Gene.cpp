//# corresponding header
#include <model/evolution/population/creature/genome/Gene.hpp>

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

Gene::Gene() :
		mGeneType(UnknownGene) {
}

Gene::~Gene() {
}

void Gene::initialize(GeneType geneType) {
	mGeneType = geneType;
}

bool Gene::equals(const Gene& gene) const {
	if (mGeneType != gene.mGeneType) {
		return false;
	}

	return true;
}

