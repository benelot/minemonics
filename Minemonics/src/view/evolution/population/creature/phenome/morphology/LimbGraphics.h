/*
 * LimbGraphics.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBGRAPHICS_H_
#define VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBGRAPHICS_H_

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

	virtual void addToWorld() = 0;

	virtual void removeFromWorld() = 0;

	virtual void update() = 0;

	virtual Ogre::Vector3 getIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;

	virtual Ogre::Vector3 getLocalIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;
	virtual Ogre::Vector3 getLocalPreciseIntersection(Ogre::Vector3 origin,
			Ogre::Vector3 direction) = 0;

protected:
	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;
};

#endif /* VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBGRAPHICS_H_ */
