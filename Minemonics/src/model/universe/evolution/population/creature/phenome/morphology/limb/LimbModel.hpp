#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_

//# corresponding header
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//# forward declarations
class btDynamicsWorld;
class CreatureModel;
class Sensor;
class Tactioceptor;

//# system headers
//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
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
 *@details Details
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
	LimbModel(const LimbModel& limbModel);

	virtual ~LimbModel();

	/**
	 * Initialize the limb model.
	 * @param world A handle to the bullet dynamics world.
	 * @param creatureModel A handle to the creature model.
	 * @param type The type of 3D primitive of the limb.
	 * @param position The position of the limb.
	 * @param orientation The orientation of the limb.
	 * @param dimensions The dimensions of the limb.
	 * @param mass The mass of the limb.
	 * @param restitution The restitution of the limb.
	 * @param friction The friction of the limb.
	 * @param color The color of the limb.
	 */
	void initialize(btDynamicsWorld* world, CreatureModel* creatureModel,
			PrimitiveType type, Ogre::Vector3 position,
			Ogre::Quaternion orientation,
			const Ogre::Vector3 initialRelativePosition,
			const Ogre::Quaternion initialOrientation, Ogre::Vector3 dimensions,
			double mass, double restitution, double friction,
			Ogre::ColourValue color, int ownIndex);

	void update(double timeSinceLastTick);
	/**
	 * Reset the limb to the place when the creature was born.
	 */
	void reset(Ogre::Vector3 position);

	/**
	 * Reposition the limb without resetting it.
	 */
	void reposition(Ogre::Vector3 position);

	/**
	 * Compare the limb model to another limb model.
	 * @param limbModel Another limb model.
	 * @return If the limb model is equal to the other limb model.
	 */
	bool equals(const LimbModel & limbModel) const;

	/**
	 * Clone the limb model.
	 * @return The clone of the limb model.
	 */
	LimbModel* clone();

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the phemone model to a string.
	 * @param os The ostream.
	 * @param phenomeModel The phemone model we want to serialize.
	 * @return A string containing all information about the phemone model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const LimbModel &limbModel) {
		return os
		/**The type of the limb*/
		<< "LimbModel: Type=" << limbModel.mPrimitiveType

		/**The dimensions of the limb*/
		<< "/Dimensions=(" << limbModel.mDimensions.x << ","
				<< limbModel.mDimensions.y << "," << limbModel.mDimensions.z
				<< ")"

				/**The color of the limb*/
				<< "/Color=(" << limbModel.mColor.r << "," << limbModel.mColor.b
				<< "," << limbModel.mColor.g << ")";
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/** Serialize the base object */
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(ComponentModel)

		/**The type of the limb*/
		& BOOST_SERIALIZATION_NVP(mPrimitiveType)

		/**The dimensions of the limb*/
		& BOOST_SERIALIZATION_NVP(mDimensions.x)
		& BOOST_SERIALIZATION_NVP(mDimensions.y)
		& BOOST_SERIALIZATION_NVP(mDimensions.z)

		/**The color of the limb*/
		& BOOST_SERIALIZATION_NVP(mColor.r)
		& BOOST_SERIALIZATION_NVP(mColor.g)
		& BOOST_SERIALIZATION_NVP(mColor.b);
	}

	//Accessor methods
	/**
	 * The the limb physics model of the limb.
	 * @return The limb physics model of the limb.
	 */
	LimbPhysics* getLimbPhysics() const {
		return mLimbPhysics;
	}

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	const Ogre::Vector3 getPosition() const {
		return OgreBulletUtils::convert(mLimbPhysics->getPosition());
	}

	const double getVolume() const {
		return mLimbPhysics->getVolume();
	}

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	const Ogre::Quaternion getOrientation() const {
		return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
	}

	const Ogre::ColourValue getColor() const {
		return mColor;
	}

	const PrimitiveType getPrimitiveType() const {
		return mPrimitiveType;
	}

	const Ogre::Vector3 getDimensions() const {
		return mDimensions;
	}

	const int getOwnIndex() const {
		return mOwnIndex;
	}

	void activateTactioceptors();

	void resetSensors();

private:

	/**
	 * The creature model this limb belongs to.
	 */
	CreatureModel* mCreatureModel;

	/**
	 * The physics model of the limb.
	 */
	LimbPhysics* mLimbPhysics;

	/**
	 * The color of the limb.
	 */
	Ogre::ColourValue mColor;

	/**
	 * The 3D primitive type of the limb.
	 */
	PrimitiveType mPrimitiveType;

	/**
	 * The dimensions of the limb.
	 */
	Ogre::Vector3 mDimensions;

	std::vector<Sensor*> mSensors;

	std::vector<Tactioceptor*> mTactioceptors;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBMODEL_HPP_ */
