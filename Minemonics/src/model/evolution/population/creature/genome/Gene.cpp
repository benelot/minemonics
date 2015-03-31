/*
 * Gene.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Gene.h"

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
		mActive(false),mGeneType(UnknownGene) {
	// TODO Auto-generated constructor stub

}

void Gene::initialize(GeneType geneType) {

}

Gene::~Gene() {
	// TODO Auto-generated destructor stub
}

bool Gene::equals(const Gene& gene) const {
	if (mActive == gene.mActive) {
		return false;
	}

	return true;
}

