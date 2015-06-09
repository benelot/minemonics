//# corresponding header
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

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
		mType(UnknownGene) {
}

Gene::~Gene() {
}

void Gene::initialize(GeneType geneType) {
	mType = geneType;
}

bool Gene::equals(const Gene& gene) const {

	/**Compare the type of gene*/
	if (mType != gene.mType) {
		return false;
	}

	return true;
}

