//# forward declarations
#include <model/universe/evolution/population/creature/genome/GeneBranch.hpp>

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
#include <utils/Randomness.hpp>

GeneBranch::GeneBranch() :
	mType(UNKNOWN_GENE_BRANCH), mActive(false) {

}

GeneBranch::GeneBranch(const GeneBranch& geneBranch) {
	mActive = geneBranch.mActive;
	mType = geneBranch.mType;
}

GeneBranch::~GeneBranch() {
}

void GeneBranch::initialize(const GeneBranchType geneBranchType) {
	mType = geneBranchType;
	mActive = Randomness::getSingleton()->nextUnifBoolean();

}

bool GeneBranch::equals(const GeneBranch& geneBranch) const {

	if (mActive != geneBranch.mActive) { 	/**!< Compare the gene branch is active or not*/
		return false;
	}

	if (mType != geneBranch.mType) { 	/**!< Compare the type of gene branch*/
		return false;
	}

	return true;
}

GeneBranch* GeneBranch::clone() {
	return new GeneBranch(*this);
}
