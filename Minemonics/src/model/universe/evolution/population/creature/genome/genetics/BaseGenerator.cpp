//# corresponding headers
#include <model/universe/evolution/population/creature/genome/genetics/BaseGenerator.hpp>
#include <stddef.h>

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

BaseGenerator::BaseGenerator() :
	mGene(NULL) {

}

BaseGenerator::~BaseGenerator() {
	mGene = NULL;
}

