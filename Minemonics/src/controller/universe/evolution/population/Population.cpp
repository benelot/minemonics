//# corresponding headers
#include <controller/universe/evolution/population/Population.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/Randomness.hpp>

BoostLogger Population::mBoostLogger; /*<! initialize the boost logger*/
Population::_Init Population::_initializer;
Population::Population() :
		mSimulationManager(NULL), mPlanet(NULL) {
}

Population::~Population() {
	//Clear the handle.
	mSimulationManager = NULL;
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end();) {
		Creature* creature = *cit;
		cit = mCreatures.erase(cit);
		delete creature;
	}
	mPlanet = NULL;
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param simulationManager The simulation manager handle
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void Population::initialize(Planet* const planet,
		SimulationManager* const simulationManager, const int creatureQty,
		const Ogre::Vector3 initialPosition) {
	mSimulationManager = simulationManager;
	mPopulationModel.initialize(&planet->getPlanetModel(), 0);
	Randomness randomness;
	double branchiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		branchiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		addNewMember(branchiness, initialPosition);
	}
	mPlanet = planet;
}

void Population::initialize(Planet* const planet, const int creatureQty) {
	mPopulationModel.initialize(&planet->getPlanetModel(), creatureQty);
	mPlanet = planet;
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(const double branchiness,
		const Ogre::Vector3 rootPosition) {
	if (mSimulationManager) {
		Creature* creature = new Creature();
		creature->initialize(mSimulationManager, this, rootPosition,
				branchiness);
		addMember(creature);
	}

}

void Population::addMember(Creature* const creature) {
	mCreatures.push_back(creature);
	//hand model down to the population model
	mPopulationModel.addMember(&creature->getCreatureModel());
}

void Population::update() {
	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->update();
	}
}

void Population::reset() {
	for (std::vector<Creature*>::iterator cit = mCreatures.begin();
			cit != mCreatures.end(); cit++) {
		(*cit)->reset();
	}
}

void Population::addToWorld() {
	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->addToWorld();
	}
}

void Population::removeFromWorld() {
	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->removeFromWorld();
	}
}
