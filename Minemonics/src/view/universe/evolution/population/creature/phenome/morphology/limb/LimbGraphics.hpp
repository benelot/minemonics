/*
 * LimbGraphics.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
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
class LimbGraphics {
public:
	LimbGraphics();
	virtual ~LimbGraphics();

	/**
	 * Add the limb to the graphical world.
	 */
	virtual void addToWorld() = 0;

	/**
	 * Remove the limb from the graphical world.
	 */
	virtual void removeFromWorld() = 0;

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	virtual void update() = 0;

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	virtual Ogre::Vector3 getIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally less expensive than the precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual Ogre::Vector3 getLocalIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;

	/**
	 * Get the precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally more expensive than the non-precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual Ogre::Vector3 getLocalPreciseIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;

	//Accessor methods

	const Ogre::Vector3& getPosition() const {
			return mPosition;
		}

		void setPosition(const Ogre::Vector3& position) {
			mPosition = position;
		}

		Ogre::Quaternion& getOrientation() {
			return mOrientation;
		}

		void setOrientation(const Ogre::Quaternion& orientation) {
			mOrientation = orientation;
		}

	bool isInWorld() const {
		return inWorld;
	}



protected:

	void setInWorld(bool inWorld) {
		this->inWorld = inWorld;
	}

	/**
	 * The position of the limb.
	 */
	Ogre::Vector3 mPosition;

	/**
	 * The orientation of the limb.
	 */
	Ogre::Quaternion mOrientation;

private:
	/**
	 * Whether the limb is in the world or not.
	 */
	bool inWorld;
};

#endif /* VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBGRAPHICS_HPP_ */
