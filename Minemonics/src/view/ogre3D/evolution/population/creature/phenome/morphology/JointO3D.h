/*
 * JointO3D.h
 *
 *  Created on: Apr 14, 2015
 *      Author: leviathan
 */

#ifndef VIEW_OGRE3D_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTO3D_H_
#define VIEW_OGRE3D_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTO3D_H_

//# corresponding header
#include "view/evolution/population/creature/phenome/morphology/JointGraphics.h"

//# forward declarations
class SimulationManager;

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
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## view headers
//## utils headers

class JointO3D: public JointGraphics {
public:
	JointO3D();
	virtual ~JointO3D();

	void initialize(SimulationManager* simulationManager, Limb* limbA,
			Limb* limbB, btTransform localA, btTransform localB);

	void update();

	void addToWorld();

	void removeFromWorld();

private:
	SimulationManager* mSimulationManager;
	Limb* mLimbA;
	Limb* mLimbB;
	btTransform mLocalA;
	btTransform mLocalB;
};

#endif /* VIEW_OGRE3D_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINTO3D_H_ */
