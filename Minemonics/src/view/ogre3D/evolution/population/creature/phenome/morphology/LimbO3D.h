/*
 * LimbO3D.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef LIMBO3D_H_
#define LIMBO3D_H_

//# corresponding headers
#include "view/evolution/population/creature/phenome/morphology/LimbGraphics.h"

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
#include "configuration/MorphologyConfiguration.h"

//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class LimbO3D: public LimbGraphics {
public:
	LimbO3D();
	virtual ~LimbO3D();

	void initialize(SimulationManager* simulationManager,
			MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 scale,Ogre::ColourValue color);

	virtual void update();

	Ogre::Entity*& getEntity() {
		return mEntity;
	}

	Ogre::SceneNode*& getEntityNode() {
		return mEntityNode;
	}

	void addToWorld();

	void removeFromWorld();

	Ogre::Vector3 getIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

	Ogre::Vector3 getLocalIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

	Ogre::Vector3 getLocalPreciseIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

private:
	SimulationManager* mSimulationManager;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mEntityNode;

};

#endif /* LIMBO3D_H_ */
