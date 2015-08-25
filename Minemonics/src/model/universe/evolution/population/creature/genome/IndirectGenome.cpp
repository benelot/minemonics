//# corresponding headers
#include <model/universe/evolution/population/creature/genome/IndirectGenome.hpp>

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

IndirectGenome::IndirectGenome() :
Genome(Genome::UnknownGenome) {

}

IndirectGenome::~IndirectGenome() {
}

bool IndirectGenome::equals(const IndirectGenome& genome) const {
	if (!Genome::equals(genome)) {
		return false;
	}
	return true;
}
