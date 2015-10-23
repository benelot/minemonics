//# corresponding headers
#include <model/universe/evolution/population/creature/genome/DirectGenome.hpp>

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

DirectGenome::DirectGenome() :
	Genome(Genome::UnknownGenome) {

}

DirectGenome::~DirectGenome() {

}

bool DirectGenome::equals(const DirectGenome& genome) const {
	if (Genome::equals(genome)) { /**!< Is the same as comparing a genome directly. */
		return false;
	}
	return true;
}
