//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/ChaoticControllerGene.hpp>

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

ChaoticControllerGene::ChaoticControllerGene() :
	ControllerGene(ControllerGene::ChaoticControllerGene) {

}

ChaoticControllerGene::ChaoticControllerGene(
	const ChaoticControllerGene& gene) {

}

ChaoticControllerGene::~ChaoticControllerGene() {

}

void ChaoticControllerGene::initialize() {
}



ChaoticControllerGene* ChaoticControllerGene::clone() {
	return new ChaoticControllerGene(this);
}
