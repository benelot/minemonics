//# corresponding headers
#include <controller/universe/evolution/population/Population.hpp>
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

Population::Population() :
		mSimulationManager(NULL) {
}

Population::~Population() {
	//Clear the handle.
	mSimulationManager = NULL;
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param simulationManager The simulation manager handle
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void Population::initialize(SimulationManager* simulationManager,
		int creatureQty) {
	mSimulationManager = simulationManager;
	mPopulationModel.setCreatureQty(creatureQty);
	Randomness randomness;
	double bushiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		bushiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		addNewMember(bushiness);
	}
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(double bushiness) {
	if (mSimulationManager) {
		Creature* creature = new Creature();
		creature->initialize(mSimulationManager, Ogre::Vector3::ZERO,
				bushiness);
		mCreatures.push_back(creature);
		//hand model down to the population model
		mPopulationModel.addNewMember(creature->mCreature);
	}

}
