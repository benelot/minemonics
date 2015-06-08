#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//# forward declarations
class btDynamicsWorld;

//# system headers
//## controller headers
//## model headers
#include <OgreColourValue.h>
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
#include<utils/ogre3D/OgreBulletUtils.hpp>

/**
 *@brief The limb model holds all the information of the limb state.
 *@details
 *@date 2015-04-29
 *@author Benjamin Ellenberger
 */
class LimbModel: public ComponentModel {
public:

	/**
	 * Primitive type of a limb
	 */
	enum PrimitiveType {
		UNKNOWN = 0, BLOCK = 2, CAPSULE = 1, NUM_PRIMITIVES
	};

	LimbModel();
	virtual ~LimbModel();

	void initialize(btDynamicsWorld* world, void* limb, PrimitiveType type,
			Ogre::Vector3 position, Ogre::Quaternion orientation,
			Ogre::Vector3 dimensions, double mass,double restitution,double friction, Ogre::ColourValue color);

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
	Ogre::Vector3 getPosition() {
		return OgreBulletUtils::convert(mLimbPhysics->getPosition());
	}

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	Ogre::Quaternion getOrientation() {
		return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
	}

	const Ogre::ColourValue& getColor() const {
		return mColor;
	}

	PrimitiveType getLimbType() const {
		return mLimbType;
	}

	const Ogre::Vector3& getDimensions() const {
		return mDimensions;
	}

private:
	/**
	 * The physics model of the limb.
	 */
	LimbPhysics* mLimbPhysics;

	Ogre::ColourValue mColor;

	PrimitiveType mLimbType;

	Ogre::Vector3 mDimensions;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_ */
