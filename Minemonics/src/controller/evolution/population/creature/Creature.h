/*
 * Creature.h
 *
 *  Created on: Apr 7, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_CREATURE_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_CREATURE_H_
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
#include "controller/evolution/population/creature/phenome/Phenome.h"

//## model headers
#include "model/evolution/population/creature/CreatureM.h"

//## view headers
//## utils headers

class Creature {
public:
	Creature();
	virtual ~Creature();

	void initialize(SimulationManager* simulationManager,
			Ogre::Vector3 position, double bushiness);

	void performEmbryogenesis();

	void update();

	void addToWorld();

	void removeFromWorld();

	/**
	 * The model of the creature
	 */
	CreatureM* mCreature;

	/**
	 * The phenotype of the creature.
	 */
	Phenome* mPhenotype;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_CREATURE_H_ */
