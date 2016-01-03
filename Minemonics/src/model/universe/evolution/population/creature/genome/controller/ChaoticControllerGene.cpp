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
#include <utils/Randomness.hpp>

ChaoticControllerGene::ChaoticControllerGene() :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		ChaoticControllerGene::CHUA_CIRCUIT), mInitialX(0), mInitialY(0), mInitialZ(
		0),mSpeed(1) {

}

ChaoticControllerGene::ChaoticControllerGene(ChaoticSystemType systemType) :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		systemType),mInitialX(0), mInitialY(0), mInitialZ(
			0),mSpeed(1) {

}

ChaoticControllerGene::ChaoticControllerGene(ChaoticSystemType systemType, double initialX,
	double initialY, double initialZ, double speed) :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		systemType),mInitialX(initialX), mInitialY(initialY), mInitialZ(
			initialZ),mSpeed(speed) {

}

ChaoticControllerGene::ChaoticControllerGene(
	const ChaoticControllerGene& gene) {
	mSystemType = gene.mSystemType;
	mInitialX = gene.mInitialX;
	mInitialY = gene.mInitialY;
	mInitialZ = gene.mInitialZ;
	mSpeed = gene.mSpeed;
}

ChaoticControllerGene::~ChaoticControllerGene() {

}

void ChaoticControllerGene::initialize() {
	mInitialX = Randomness::getSingleton()->nextUnifDouble(-0.5,0.5);
	mInitialY = Randomness::getSingleton()->nextUnifDouble(-0.5,0.5);
	mInitialZ = Randomness::getSingleton()->nextUnifDouble(-0.5,0.5);
	mSpeed = Randomness::getSingleton()->nextUnifDouble(0.001f,10.0f);
}

ChaoticControllerGene* ChaoticControllerGene::clone() {
	return new ChaoticControllerGene(*this);
}
