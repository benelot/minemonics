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
#include <configuration/ControlConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

ChaoticControllerGene::ChaoticControllerGene() :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		ChaoticControllerGene::CHUA_CIRCUIT), mInitialX(0), mInitialY(0), mInitialZ(
		0), mSpeed(1) {

}

ChaoticControllerGene::ChaoticControllerGene(ChaoticSystemType systemType) :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		systemType), mInitialX(0), mInitialY(0), mInitialZ(0), mSpeed(1) {

}

ChaoticControllerGene::ChaoticControllerGene(ChaoticSystemType systemType,
	double initialX, double initialY, double initialZ, double speed) :
	ControllerGene(ControllerGene::ChaoticControllerGene), mSystemType(
		systemType), mInitialX(initialX), mInitialY(initialY), mInitialZ(
		initialZ), mSpeed(speed) {

}

ChaoticControllerGene::ChaoticControllerGene(const ChaoticControllerGene& gene) :
	ControllerGene(ControllerGene::ChaoticControllerGene) {
	mSystemType = gene.mSystemType;
	mInitialX = gene.mInitialX;
	mInitialY = gene.mInitialY;
	mInitialZ = gene.mInitialZ;
	mSpeed = gene.mSpeed;
}

ChaoticControllerGene::~ChaoticControllerGene() {

}

void ChaoticControllerGene::initialize() {
	mInitialX = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::CHAOS_MIN_INIT_CONDITION,
		ControlConfiguration::CHAOS_MAX_INIT_CONDITION);
	mInitialY = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::CHAOS_MIN_INIT_CONDITION,
		ControlConfiguration::CHAOS_MAX_INIT_CONDITION);
	mInitialZ = Randomness::getSingleton()->nextUnifDouble(
		ControlConfiguration::CHAOS_MIN_INIT_CONDITION,
		ControlConfiguration::CHAOS_MAX_INIT_CONDITION);
	mSpeed = Randomness::getSingleton()->nextTwoDistDouble(
		ControlConfiguration::CHAOS_MIN_INTEGRATION_SPEED, 1, 1,
		ControlConfiguration::CHAOS_MAX_INTEGRATION_SPEED);
}

ChaoticControllerGene* ChaoticControllerGene::clone() {
	return new ChaoticControllerGene(*this);
}
