//# corresponding header
#include <controller/universe/evolution/population/creature/Creature.hpp>

//# forward declarations
class SimulationManager;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//## model headers
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

Creature::Creature() :
		mCreatureModel(NULL), mPhenotype(NULL) {

}

Creature::~Creature() {
	delete mCreatureModel;
	mCreatureModel = NULL;

	delete mPhenotype;
	mPhenotype = NULL;
}

void Creature::initialize(SimulationManager* simulationManager,
		Population* population, Ogre::Vector3 position, double branchiness) {
	// set up the creature model
	mCreatureModel = new CreatureModel();
	mCreatureModel->initialize(population->getPopulationModel(), NULL, position,
			branchiness);

	// set up the phenotype
	mPhenotype = new Phenome();
	mPhenotype->initialize(simulationManager, this);

	// hand down the phenome model to the creature model
	mCreatureModel->setPhenotypeModel(&mPhenotype->getPhenomeModel());

}

void Creature::performEmbryogenesis() {
	mPhenotype->performEmbryogenesis(this, &mCreatureModel->getGenotype(),
			mCreatureModel->getPosition());
	setDeveloped(true);
}

void Creature::reset(Ogre::Vector3 position) {
	mCreatureModel->reset(position);
	mPhenotype->reset(position);
}

void Creature::reset() {
	reset(mCreatureModel->getInitialPosition());
}

void Creature::reposition(Ogre::Vector3 position) {
	mCreatureModel->reposition(position);
	mPhenotype->reposition(position);
}

void Creature::update() {
	// Update the phenotype of the creature if it is in the world.
	if (mPhenotype->isInWorld()) {
		mPhenotype->update();
	}
}

void Creature::addToWorld() {
	// develop creature if it is not developed yet.
	if (!isDeveloped()) {
		performEmbryogenesis();
	}

	// Add phenotype to world
	mPhenotype->addToWorld();
}

void Creature::removeFromWorld() {
	// Remove phenotype from world
	mPhenotype->removeFromWorld();
}
