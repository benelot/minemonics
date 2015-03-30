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
#include <OgreQuaternion.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

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

	virtual void update() = 0;

protected:
	Ogre::Vector3 mPosition;
	Ogre::Quaternion mOrientation;
};

#endif /* VIEW_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMBGRAPHICS_H_ */
