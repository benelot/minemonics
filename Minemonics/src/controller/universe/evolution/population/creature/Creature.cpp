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
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>
#include <controller/universe/evolution/population/Population.hpp>

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

void Creature::initialize(SimulationManager* simulationManager,Population* population,
		Ogre::Vector3 position, double branchiness) {
	mCreatureModel = new CreatureModel();
	mCreatureModel->initialize(population->getPopulationModel(),NULL,position, branchiness);

	mPhenotype = new Phenome();
	mPhenotype->initialize(simulationManager,this);

	mCreatureModel->setPhenotypeModel(&mPhenotype->getPhenomeModel());

}

void Creature::performEmbryogenesis() {
	mPhenotype->performEmbryogenesis(this,&mCreatureModel->getGenotype(),
			mCreatureModel->getPosition());
}

void Creature::update() {
	mPhenotype->update();
}

void Creature::addToWorld() {
	// develop creature if it is not developed yet.
	if(!isDeveloped())
	{
		performEmbryogenesis();
	}

	// Add phenotype to world
	mPhenotype->addToWorld();
}

void Creature::removeFromWorld() {
	// Remove phenotype from world
	mPhenotype->removeFromWorld();
}
