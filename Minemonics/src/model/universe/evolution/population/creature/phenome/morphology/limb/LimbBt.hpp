#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */
struct btDefaultMotionState;
class btDynamicsWorld;
class btMultiBody;
//class btMultiBodyLinkCollider;

//# system headers
#include <cmath>

//## controller headers
//## model headers
#include <BulletDynamics/Featherstone/btMultiBodyLinkCollider.h>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btScalar.h>
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
class LimbBt: public LimbPhysics {
public:
	LimbBt();
	LimbBt(const LimbBt& limbBt);

	virtual ~LimbBt();

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
	void initialize(btDynamicsWorld* const world, void* const limbModel,
			const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
			const btQuaternion orientation,
			const btVector3 initialRelativePosition,
			const btQuaternion initialOrientation,
			const Ogre::Vector3 dimensions, const btScalar mass,
			const btScalar restitution, const btScalar friction,
			const Ogre::ColourValue color);

	virtual void generateLink(btMultiBody* multiBody, btVector3 origin,
			btQuaternion rotation, int index);

	/**
	 * Clone the bullet physics limb.
	 */
	virtual LimbBt* clone();

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
	//Accessor methods

//	btVector3 getPosition() const {
//		return mBody->getCenterOfMassPosition();
//	}
//
//	btQuaternion getOrientation() const {
//		return mBody->getOrientation();
//	}

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

	virtual const double getVolume() {
		if (mVolume != 0) {
			return mVolume;
		}

		double volume = 0;
		switch (mType) {
		case LimbPhysics::BLOCK: {
			volume = mDimensions.x * mDimensions.y * mDimensions.z;
			break;
		}
		case LimbPhysics::CAPSULE: {
			volume = pow(mDimensions.x * 0.5f, 2) * M_PI * mDimensions.z
					+ pow(mDimensions.x, 3) * M_PI / 6.0f;
			break;
		}
		}
		mVolume = volume;
		return volume;
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
	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the limb bullet model to a string.
	 * @param os The ostream.
	 * @param limbPhysics The limb bullet model we want to serialize.
	 * @return A string containing all information about the limb bullet model.
	 */
//	friend std::ostream & operator<<(std::ostream &os,
//			const LimbPhysics &limbPhysics) {
//		return os
//				/**The limb physics model of the limb bullet model*/
//				<< "LimbBt: LimbPhysics=" << LimbPhysics;
//	}
	/**
	 * Serializes the limb bullet model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The limb physics model of the limb bullet model*/
		& BOOST_SERIALIZATION_BASE_OBJECT_NVP(LimbPhysics);
	}

private:
	btDynamicsWorld* mWorld;

	btCollisionShape* mCollisionShape;

	btDefaultMotionState* mMotionState;

	btRigidBody* mBody;

	btVector3 mInertia;

	btMultiBodyLinkCollider* mLink;
};
BOOST_CLASS_VERSION(LimbBt, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBBT_HPP_ */
