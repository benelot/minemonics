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

Population::Population() :
		mSimulationManager(NULL), mPopulationModel(NULL), mPlanet(NULL) {
}

Population::~Population() {
	//Clear the handle.
	mSimulationManager = NULL;
	delete mPopulationModel;
}

/**
 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
 * @param simulationManager The simulation manager handle
 * @param creatureQty The number of creatures that the population will consist of in every generation.
 */
void Population::initialize(Planet* planet,
		SimulationManager* simulationManager, int creatureQty) {
	mSimulationManager = simulationManager;
	mPopulationModel = new PopulationModel();
	mPopulationModel->initialize(&planet->getPlanetModel(), creatureQty);
	Randomness randomness;
	double bushiness = 0;
	for (int i = 0; i < creatureQty; i++) {
		bushiness = randomness.nextNormalDouble(
				MorphologyConfiguration::BODY_BRANCH_INITIAL_MEAN,
				MorphologyConfiguration::BODY_BRANCH_INITIAL_VAR);
		addNewMember(bushiness);
	}
	mPlanet = planet;
}

void Population::initialize(Planet* planet, int creatureQty) {
	mPopulationModel = new PopulationModel();
	mPopulationModel->initialize(&planet->getPlanetModel(), creatureQty);
	mPlanet = planet;
}

/**
 * Adds a new creature to the population with the bushiness as a input.
 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
 */
void Population::addNewMember(double branchiness, Ogre::Vector3 rootPosition) {
	if (mSimulationManager) {
		Creature* creature = new Creature();
		//TODO:Include planet into initializer
		creature->initialize(mSimulationManager, this, rootPosition,
				branchiness);
		addMember(creature);
	}

}

void Population::addMember(Creature* creature) {
	mCreatures.push_back(creature);
	//hand model down to the population model
	mPopulationModel->addMember(creature->getCreatureModel());
}

void Population::update() {
	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->update();
	}
}

void Population::reset() {
	std::vector<Creature*>::iterator cit = mCreatures.begin();
		for (; cit != mCreatures.end(); cit++) {
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
