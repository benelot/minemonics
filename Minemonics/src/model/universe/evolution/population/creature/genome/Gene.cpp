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

Gene::Gene(GeneType geneType) :
		mType(geneType) {
}

Gene::Gene() :
		mType(NUM_GENES) {
}

Gene::~Gene() {
}

void Gene::initialize(const GeneType geneType) {
	mType = geneType;
}

bool Gene::equals(const Gene& gene) const {

	if (mType != gene.mType) { 	/**Compare the type of gene*/
		return false;
	}

	return true;
}

