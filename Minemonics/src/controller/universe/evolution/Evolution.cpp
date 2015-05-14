//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/Evolution.hpp>

//## model headers
//## view headers
//## utils headers


Evolution::Evolution():mCurrentCreature(NULL),mEnvironment(NULL) {
}

Evolution::~Evolution() {
	mCurrentCreature = NULL;

	delete mEnvironment;
	mEnvironment = NULL;
}

void Evolution::initialize(Environment* environment) {
	mEnvironment = environment;
}

void Evolution::addNewPopulation(Population* population) {
	mPopulations.push_back(population);
	mEvolutionModel.addNewPopulation(population->getPopulationModel());
}

void Evolution::proceedEvaluation() {
}
