#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBBT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBBT_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//# forward declarations
struct btDefaultMotionState;
class btDynamicsWorld;
class btMultiBody;
class CreatureModel;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <cmath>
#include <iostream>

//## controller headers
//## model headers
#include <OgreQuaternion.h>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/base_object.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyLinkCollider.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The physical model of the limb implemented in the Bullet Physics Engine.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class FSLimbBt: public LimbPhysics {
public:
	FSLimbBt();
	FSLimbBt(const FSLimbBt& limbBt);
	FSLimbBt(btDynamicsWorld* const world, CreatureModel* const creatureModel,
	const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding);

	virtual ~FSLimbBt();

	/**
	 * Initialize the bullet limb with the following parameters:
	 * @param world The dynamics world of the bullet engine to add and remove the limb.
	 * @param limbModel The handle of the limbModel that we want to get back if we raycast for it.
	 * @param type The primitive type of the limb that should be set as a collision shape.
	 * @param position The position of the limb.
	 * @param orientation The orientation of the limb.
	 * @param dimensions The dimensions of the limb.
	 * @param mass The mass of the limb.
	 */
	virtual void initialize();

	virtual void generateLink(btMultiBody* multiBody, void* const limbModel,
		btVector3 origin, btQuaternion rotation, int index);

	/**
	 * Clone the bullet physics limb.
	 */
	virtual FSLimbBt* clone();

	/**
	 * Reset the joint to the place when the creature was born.
	 */
	virtual void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the joint without resetting it.
	 */
	virtual void reposition(const Ogre::Vector3 position);

	/**
	 * Add the limb to the physical world.
	 */
	void addToWorld();

	/**
	 * Remove the limb from the physical world.
	 */
	void removeFromWorld();

	virtual const Ogre::Vector3 getVelocities() const;

	/**
	 * Get the intersection in the global reference frame.
	 * @param origin: The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the global reference frame.
	 */
	btTransform getIntersection(const btVector3 origin,
		const btVector3 direction);

	/**
	 * Get the precise intersection in the global reference frame.
	 * Note that this only hits other creature elements in the COL_CREATURE collision group.
	 * @param origin The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btTransform getPreciseIntersection(const btVector3 origin,
		const btVector3 direction);

	/**
	 * Get the fake intersection with the surface in the local reference frame.
	 * @param origin The origin the intersection starts from.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The fake intersection in the local reference frame.
	 */
	btVector3 getLocalFakeIntersection(const btVector3 origin,
		const btVector3 direction);

	/**
	 * Get the intersection in the local reference frame of the indicated origin.
	 * @param origin: The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btTransform getLocalIntersection(const btVector3 origin,
		const btVector3 direction);

	/**
	 * Get the precise intersection in the local reference frame of the indicated origin.
	 * @param origin The origin the intersection starts from and in whose reference frame the intersection is shown.
	 * @param direction: The direction of the intersection testing ray.
	 * @return The intersection in the local reference frame.
	 */
	btTransform getLocalPreciseIntersection(const btVector3 origin,
		const btVector3 direction);

	virtual void calm();

	/**
	 * Compare the limb bullet physics model to another limb bullet physics model.
	 * @param limbPhysics Another limb bullet physics model.
	 * @return If the limb bullet physics model is equal to the other limb bullet physics model.
	 */
	bool equals(const FSLimbBt & limbBt) const;

	//Accessor methods

	btVector3 getPosition() const {
		if (mLink) {
			return mLink->getWorldTransform().getOrigin();
		} else {
			return mBody->getCenterOfMassPosition();
		}
	}

	btQuaternion getOrientation() const {
		btTransform transform;
		if (mLink) {
			transform = mLink->getWorldTransform();
		} else {
			transform = mBody->getWorldTransform();
		}

		//if there are NaNs, this removes them it seems.
		return transform.getRotation().normalized();
	}

	btRigidBody* getRigidBody() const {
		return mBody;
	}

	virtual btCollisionShape* getCollisionShape() {
		return mCollisionShape;
	}

	virtual const btVector3& getInertia() const {
		return mInertia;
	}

	void setInertia(const btVector3& inertia) {
		mInertia = inertia;
	}

	btMultiBodyLinkCollider* getLink() {
		return mLink;
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the limb bullet model to a string.
	 * @param os The ostream.
	 * @param limbPhysics The limb bullet model we want to serialize.
	 * @return A string containing all information about the limb bullet model.
	 */
	friend std::ostream & operator<<(std::ostream &os, const FSLimbBt &limbBt) {
		return os << "LimbBt: LimbPhysics=" << limbBt; /**!< The limb physics model of the limb bullet model*/
	}

	void setWorld(btDynamicsWorld* world) {
		mWorld = world;
	}

	/**
	 * Serializes the limb bullet model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(LimbPhysics); /**!< Serialize the base object */
	}

private:
	btDynamicsWorld* mWorld; /**!< The world the limb is in */

	btCollisionShape* mCollisionShape; /**!< The collision shape of the limb */

	btDefaultMotionState* mMotionState; /**!< The motion state of the limb */

	btRigidBody* mBody; /**!< The rigid body of the limb */

	btVector3 mInertia; /**!< The inertia of the limb */

	btMultiBodyLinkCollider* mLink; /**!< The multibody link segment of the limb */

	CreatureModel* mCreatureModel;
};
BOOST_CLASS_VERSION(FSLimbBt, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_FSLIMBBT_HPP_ */
