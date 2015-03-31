/*
 * Limb.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 *
 */

#ifndef LIMB_H_
#define LIMB_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class LimbBt;
class LimbO3D;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
#include "controller/evolution/population/creature/phenome/Component.h"

//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbPhysics.h"

//## view headers
#include "view/evolution/population/creature/phenome/morphology/LimbGraphics.h"

//## utils headers

class Limb: public Component {
public:
	Limb();
	virtual ~Limb();

	void initialize(SimulationManager* simulationManager, MorphologyConfiguration::PrimitiveType type,
			Ogre::Vector3 position, Ogre::Quaternion orientation,
			Ogre::Vector3 size, double mass);

	void update();

	std::string getInfo();

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

#endif /* LIMB_H_ */
