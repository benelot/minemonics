#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_

//# corresponding header
//# forward declarations
class btDynamicsWorld;

//# system headers
//## controller headers
//## model headers
#include <OgreQuaternion.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers

/**
 *@brief The limb model holds all the information of the limb state.
 *@details
 *@date 2015-04-29
 *@author Benjamin Ellenberger
 */
class LimbModel {
public:
	LimbModel();
	virtual ~LimbModel();

	void initialize(btDynamicsWorld* world, void* limb,
			MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 position,
			Ogre::Quaternion orientation,Ogre::Vector3 dimensions, double mass);


	//TODO: Implement serialization methods for LimbModel.

	//Accessor methods
	/**
	 * The the limb physics model of the limb.
	 * @return The limb physics model of the limb.
	 */
	LimbPhysics* getLimbPhysics() {
		return mLimbPhysics;
	}

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	btVector3 getPosition(){
		return mLimbPhysics->getPosition();
	}

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	btQuaternion getOrientation(){
		return mLimbPhysics->getOrientation();
	}

private:
	/**
	 * The physics model of the limb.
	 */
	LimbPhysics* mLimbPhysics;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_ */
