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
		mGeneBranchType(UNKNOWN_GENE_BRANCH), mActive(false) {

}

GeneBranch::~GeneBranch() {
	// TODO Auto-generated destructor stub
}

void GeneBranch::initialize(GeneBranchType geneBranchType) {
	mGeneBranchType = geneBranchType;
}

bool GeneBranch::equals(const GeneBranch& geneBranch) const {

	if (mGeneBranchType != geneBranch.mGeneBranchType) {
		return false;
	}

	return true;
}

