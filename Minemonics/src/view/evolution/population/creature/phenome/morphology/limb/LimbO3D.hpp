/*
 * LimbO3D.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef LIMBO3D_H_
#define LIMBO3D_H_

//# corresponding headers
#include <view/evolution/population/creature/phenome/morphology/limb/LimbGraphics.hpp>

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
#include <configuration/MorphologyConfiguration.hpp>

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
			MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 scale,
			Ogre::ColourValue color);

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	virtual void update();

	/**
	 * Add the limb to the graphical world.
	 */
	void addToWorld();

	/**
	 * Add the limb to the graphical world.
	 */
	void removeFromWorld();

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	Ogre::Vector3 getIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally less expensive than the precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	Ogre::Vector3 getLocalIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

	/**
	 * Get the precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally more expensive than the non-precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	Ogre::Vector3 getLocalPreciseIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction);

	//Accessor methods

	Ogre::Entity*& getEntity() {
		return mLimbEntity;
	}

	Ogre::SceneNode*& getEntityNode() {
		return mLimbEntityNode;
	}

private:

	/**
	 * The simulationmanager handle
	 */
	SimulationManager* mSimulationManager;

	/**
	 * The limb object in the graphical world.
	 */
	Ogre::Entity* mLimbEntity;

	/**
	 * The entity node of the limb to perform rotations and translations with.
	 */
	Ogre::SceneNode* mLimbEntityNode;

};

#endif /* LIMBO3D_H_ */
