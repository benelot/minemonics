/*
 * LimbO3D.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef LIMBO3D_H_
#define LIMBO3D_H_

//# corresponding header
//# forward declarations
class SimulationManager;

//# system headers
//## controller headers
//## model headers
#include <OgreEntity.h>
#include <OgreSceneNode.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"

//## model headers
//## view headers
#include "view/evolution/population/creature/phenome/morphology/LimbGraphics.h"

//## utils headers

class LimbO3D: public LimbGraphics {
public:
	LimbO3D();
	virtual ~LimbO3D();

	void initialize(SimulationManager* simulationManager, Limb::PrimitiveType type, Ogre::Vector3 scale);

	virtual void update();

	Ogre::Entity*& getEntity() {
		return mEntity;
	}

	Ogre::SceneNode*& getEntityNode() {
		return mEntityNode;
	}

private:
	SimulationManager* mSimulationManager;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mEntityNode;

};

#endif /* LIMBO3D_H_ */
