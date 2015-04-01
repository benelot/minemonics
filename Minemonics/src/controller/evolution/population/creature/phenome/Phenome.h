/*
 * Phenome.h
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 *
 *     From Lee Graham Thesis:
 *      Each creature's body is composed of a number of cuboids called "body segments". The
 * segments are arranged in a tree structure with each segment connected to its parent by a
 * type of physical constraint known as a universal joint. Segments are divided into groups
 * called types, with the properties of each type encoded in the genotype. Each
 * cuboid is a rigid solid with uniform density. The density value is a variable.
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class Limb;
class JointBt;

//# system headers
//## controller headers
//## model headers
#include <bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include "controller/physics/PhysicsController.h"

#include "controller/evolution/population/creature/phenome/Component.h"
//## model headers
#include "model/evolution/population/creature/genome/Genome.h"

//## view headers
//## utils headers

class Phenome {
public:
	Phenome();
	virtual ~Phenome();

	void initialize(SimulationManager* simulationManager);

	void performEmbryogenesis(Genome* genome);

	const std::vector<Component*>& getComponents() const {
		return mComponents;
	}

private:
	SimulationManager* mSimulationManager;

	std::vector<Component*> mComponents;

	std::vector<Limb*> mLimbs;
	std::vector<JointBt*> mJoints;

	btDynamicsWorld* mWorld;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_H_ */