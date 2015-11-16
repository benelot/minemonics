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
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		ChaoticControllerGene::CHUA_CIRCUIT) {

}

ChaoticControllerGene::ChaoticControllerGene(ChaoticSystemType systemType) :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		systemType) {

}

ChaoticControllerGene::ChaoticControllerGene(
	const ChaoticControllerGene& gene) {
	mSystemType = gene.mSystemType;
}

ChaoticControllerGene::~ChaoticControllerGene() {

}

void ChaoticControllerGene::initialize() {
}

ChaoticControllerGene* ChaoticControllerGene::clone() {
	return new ChaoticControllerGene(*this);
}
