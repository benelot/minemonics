/*
 * Limb.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 *
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_

//# corresponding headers
#include "controller/evolution/population/creature/phenome/Component.h"

//# forward declarations
class SimulationManager;

class LimbO3D;

class LimbPhysics;
class LimbBt;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

//## view headers
#include <OgreColourValue.h>

//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
//## model headers
//## view headers
#include "view/evolution/population/creature/phenome/morphology/LimbGraphics.h"

//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Limb: public Component {
public:
	Limb();
	virtual ~Limb();

	void initialize(SimulationManager* simulationManager, MorphologyConfiguration::PrimitiveType type,
			Ogre::Vector3 position, Ogre::Quaternion orientation,
			Ogre::Vector3 size, double mass,Ogre::ColourValue color = Ogre::ColourValue(1,1,1));

	void update();

	std::string getInfo();

	void addToWorld();

	void removeFromWorld();

	Ogre::Vector3 getIntersection(Ogre::Vector3 origin,Ogre::Vector3 direction);

	const Ogre::Vector3& getPosition() const {
		return mLimbGraphics->getPosition();
	}

	Ogre::Quaternion& getOrientation() {
		return mLimbGraphics->getOrientation();
	}

	LimbO3D* getLimbGraphics();
	LimbBt* getLimbPhysics();

private:
	LimbPhysics* mLimbPhysics;
	LimbGraphics* mLimbGraphics;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_ */
