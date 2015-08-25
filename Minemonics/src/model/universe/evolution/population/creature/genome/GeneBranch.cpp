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
}


bool GeneBranch::equals(const GeneBranch& geneBranch) const {

	/**Compare the gene branch is active or not*/
	if(mActive != geneBranch.mActive){
		return false;
	}

	/**Compare the type of gene branch*/
	if (mType != geneBranch.mType) {
		return false;
	}

	return true;
}

GeneBranch* GeneBranch::clone() {
	return new GeneBranch(*this);
}
