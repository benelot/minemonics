#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_

//# corresponding headers
#include <controller/evolution/population/creature/phenome/Component.h>

//# forward declarations
class SimulationManager;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <btBulletDynamicsCommon.h>

//## view headers
#include <OgreColourValue.h>

//# custom headers
//## base headers
//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
//## model headers
#include <model/evolution/population/creature/phenome/morphology/limb/LimbPhysics.h>
#include <model/evolution/population/creature/phenome/morphology/limb/LimbBt.h>

//## view headers
#include <view/evolution/population/creature/phenome/morphology/limb/LimbGraphics.h>
#include <view/evolution/population/creature/phenome/morphology/limb/LimbO3D.h>

//## utils headers

/**
 * @brief		The limb controller synchronizes the state of the graphical representation with the physical model
 * @details		Details
 * @date		2014-12-19
 * @author		Benjamin Ellenberger
 */
class Limb: public Component {
public:
	Limb();
	virtual ~Limb();

	void initialize(SimulationManager* simulationManager,
			MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 position,
			Ogre::Quaternion orientation, Ogre::Vector3 size, double mass,
			Ogre::ColourValue color = Ogre::ColourValue(1, 1, 1));

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	void update();

	/**
	 * Add the limb to the graphical and the physical world.
	 */
	void addToWorld();

	/**
	 * Remove the limb from the graphical and the physical world.
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
	 * Get some information about the limb in a string.
	 * @return Some information about the limb in a string.
	 */
	std::string getInfo();
	// Accessor methods

	const Ogre::Vector3& getPosition() const {
		return mLimbGraphics->getPosition();
	}

	Ogre::Quaternion& getOrientation() {
		return mLimbGraphics->getOrientation();
	}

	/**
	 * Get the Graphics part of the limb.
	 */
	LimbO3D* getLimbGraphics() {
		return ((LimbO3D*) mLimbGraphics);

	}

	/**
	 * Get the Physics part of the limb.
	 */
	LimbBt* getLimbPhysics() {
		return ((LimbBt*) mLimbPhysics);
	}

private:
	LimbGraphics* mLimbGraphics;
	LimbPhysics* mLimbPhysics;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_H_ */
