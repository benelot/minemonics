/*
 * Joint.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_H_

//# corresponding header
#include "controller/evolution/population/creature/phenome/Component.h"

//# forward declarations
class SimulationManager;
class Limb;

//# system headers
//## controller headers
//## model headers
#include <bullet/LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include "model/evolution/population/creature/phenome/morphology/JointPhysics.h"

//## view headers
#include "view/evolution/population/creature/phenome/morphology/JointGraphics.h"

//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Joint: public Component {
public:
	Joint();
	virtual ~Joint();

	void initialize(SimulationManager* simulationManager, Limb* limbA,
			Limb* limbB, btTransform localA, btTransform localB);

	void update();

	void addToWorld();

	void removeFromWorld();

	void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit);

	JointGraphics*& getJointGraphics() {
		return mJointGraphics;
	}

	JointPhysics*& getJointPhysics() {
		return mJointPhysics;
	}

private:
	JointPhysics* mJointPhysics;
	JointGraphics* mJointGraphics;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_H_ */
