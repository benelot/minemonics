#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_SRBLimbModel_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_SRBLimbModel_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//# forward declarations
class btDynamicsWorld;
class CreatureModel;
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
#include <OgreColourValue.h>
#include <LinearMath/btVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//## view headers
//## utils headers
#include<utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/logging/Logger.hpp>

/**
 *@brief The limb model holds all the information of the limb state.
 *@details Details
 *@date 2015-04-29
 *@author Benjamin Ellenberger
 */
class SRBLimbModel: public LimbModel {
public:

	SRBLimbModel();
	SRBLimbModel(const SRBLimbModel& SRBLimbModel);
	SRBLimbModel(btDynamicsWorld* world, CreatureModel* creatureModel,
		LimbPhysics::PrimitiveType type, Ogre::Vector3 position,
		Ogre::Quaternion orientation,
		const Ogre::Vector3 initialRelativePosition,
		const Ogre::Quaternion initialOrientation, Ogre::Vector3 dimensions,
		double mass, double restitution, double friction,
		Ogre::ColourValue color, bool isIntraBodyColliding,
		std::vector<ComponentModel*>::size_type ownIndex);

	virtual ~SRBLimbModel();

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
	 * @param SRBLimbModel Another limb model.
	 * @return If the limb model is equal to the other limb model.
	 */
	bool equals(const SRBLimbModel & SRBLimbModel) const;

	/**
	 * Clone the limb model.
	 * @return The clone of the limb model.
	 */
	SRBLimbModel* clone();

	void calm();

	// Accessor methods ##########################
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

	const std::vector<std::vector<JointModel*>::size_type>& getChildJointIndices() const {
		return mChildJointIndices;
	}

	void addChildJointIndex(
		std::vector<JointModel*>::size_type childJointIndex) {
		mChildJointIndices.push_back(childJointIndex);
	}

	const bool isIntraBodyColliding() const {
		return mLimbPhysics->isIntraBodyColliding();
	}

	void setWorld(btDynamicsWorld* world){
		((SRBLimbBt*)mLimbPhysics)->setWorld(world);
	}

	btRigidBody* getRigidBody(){
		return ((SRBLimbBt*)mLimbPhysics)->getRigidBody();
	}

// Serialization
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the limb model to a string.
	 * @param os The ostream.
	 * @param SRBLimbModel The limb model we want to serialize.
	 * @return A string containing all information about the limb model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const SRBLimbModel &SRBLimbModel);
	/**
	 * Serializes the limb model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(LimbModel); /**!< Serialize the base object */

	}

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string > ("SRBLimbModel"));
		}
	} _initializer;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_SRBLIMBMODEL_HPP_ */
