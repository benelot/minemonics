/*
 * Creature.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: leviathan
 */

#include <controller/evolution/population/creature/Creature.hpp>
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
#include <controller/evolution/population/creature/phenome/Phenome.hpp>

//## model headers
#include <model/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

Creature::Creature() :
		mCreature(0), mPhenotype(0) {
	// TODO Auto-generated constructor stub

}

Creature::~Creature() {
	// TODO Auto-generated destructor stub
}

void Creature::initialize(SimulationManager* simulationManager,
		Ogre::Vector3 position, double bushiness) {
	mCreature = new CreatureModel();
	mCreature->initialize(position, bushiness);
	mPhenotype = new Phenome();
	mPhenotype->initialize(simulationManager);
}

void Creature::performEmbryogenesis() {
	mPhenotype->performEmbryogenesis(&mCreature->getGenotype(),
			mCreature->getPosition());
}

void Creature::update() {
	mPhenotype->update();
}

void Creature::addToWorld() {
	// Add phenotype to world
	mPhenotype->addToWorld();
}

void Creature::removeFromWorld() {
	// Remove phenotype from world
	mPhenotype->removeFromWorld();
}
