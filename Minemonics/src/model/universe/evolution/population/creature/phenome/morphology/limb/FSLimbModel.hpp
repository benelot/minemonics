#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBMODEL_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//# forward declarations
class btDynamicsWorld;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreQuaternion.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers

/**
 *@brief The limb model holds all the information of the limb state.
 *@details Details
 *@date 2015-04-29
 *@author Benjamin Ellenberger
 */
class FSLimbModel: public LimbModel {
public:

	FSLimbModel();
	FSLimbModel(const FSLimbModel& limbModel);
	FSLimbModel(btDynamicsWorld* world, CreatureModel* creatureModel,
		LimbPhysics::PrimitiveType type, Ogre::Vector3 position,
		Ogre::Quaternion orientation,
		const Ogre::Vector3 initialRelativePosition,
		const Ogre::Quaternion initialOrientation, Ogre::Vector3 dimensions,
		double mass, double restitution, double friction,
		Ogre::ColourValue color, bool isIntraBodyColliding,
		std::vector<ComponentModel*>::size_type ownIndex);

	virtual ~FSLimbModel();

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
	virtual void initialize();

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
	bool equals(const FSLimbModel & limbModel) const;

	/**
	 * Clone the limb model.
	 * @return The clone of the limb model.
	 */
	FSLimbModel* clone();

	void calm();

	//Accessor methods
	/**
	 * The the limb physics model of the limb.
	 * @return The limb physics model of the limb.
	 */
	LimbPhysics* getLimbPhysics() const;

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	const Ogre::Vector3 getPosition() const;

	const double getVolume() const;

	const Ogre::Vector3 getVelocities() const;

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	const Ogre::Quaternion getOrientation() const;

	const Ogre::ColourValue getColor() const;

	const LimbPhysics::PrimitiveType getPrimitiveType() const;

	const Ogre::Vector3 getDimensions() const;

	const int getOwnIndex() const {
		return mOwnIndex;
	}

	void activateTactioceptors();

	void resetSensors();

	void setInterpenetrationDepth(double interpenetrationDepth);

	double getInterpenetrationDepth();

	const double getMass() const {
		return mLimbPhysics->getMass();
	}

	const btVector3 getInertia() const {
		return mLimbPhysics->getInertia();
	}

	virtual btCollisionShape* getCollisionShape() {
		return mLimbPhysics->getCollisionShape();
	}

	const double getFriction() {
		return mLimbPhysics->getFriction();
	}

	std::vector<FSLimbModel*>::size_type getParentJointIndex() const {
		return mParentJointIndex;
	}

	void setParentJointIndex(
		std::vector<FSLimbModel*>::size_type parentJointIndex) {
		mParentJointIndex = parentJointIndex;
	}

	const std::vector<std::vector<FSJointModel*>::size_type>& getChildJointIndices() const {
		return mChildJointIndices;
	}

	void addChildJointIndex(
		std::vector<FSJointModel*>::size_type childJointIndex) {
		mChildJointIndices.push_back(childJointIndex);
	}

	const bool isIntraBodyColliding() const {
		return mLimbPhysics->isIntraBodyColliding();
	}

	void setWorld(btDynamicsWorld* world){
		((FSLimbBt*)mLimbPhysics)->setWorld(world);
	}

// Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the limb model to a string.
	 * @param os The ostream.
	 * @param phenomeModel The limb model we want to serialize.
	 * @return A string containing all information about the limb model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const FSLimbModel &limbModel);
	/**
	 * Serializes the limb model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<FSLimbBt*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(LimbModel); /**!< Serialize the base object */

	}
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBMODEL_HPP_ */
