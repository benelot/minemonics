#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_

//# corresponding header
//# forward declarations
class btCollisionShape;
class btQuaternion;
class btTransform;
class btVector3;
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>
#include <OgreColourValue.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The generic physical model of the limb.
 * @details		Details
 * @date		2015-03-24
 * @author		Benjamin Ellenberger
 */
class LimbPhysics {
public:
	/**
	 * Primitive type of a limb
	 */
	enum PrimitiveType {
		UNKNOWN = 0, BLOCK = 2, CAPSULE = 1, NUM_PRIMITIVES
	};

	LimbPhysics();
	virtual ~LimbPhysics();

	/**
	 * Clone the limb physics.
	 * @return The clone of the limb physics.
	 */
	virtual LimbPhysics* clone() = 0;

	/**
	 * Reset the limb to the place when the creature was born.
	 */
	virtual void reset(Ogre::Vector3 position) = 0;

	/**
	 * Reposition the limb without resetting it.
	 */
	virtual void reposition(Ogre::Vector3 position) = 0;

	virtual void calm() = 0;
	/**
	 * Add the limb to the physical world.
	 */
	virtual void addToWorld() {
		mInWorld = true;
	}

	/**
	 * Remove the limb from the physical world.
	 */
	virtual void removeFromWorld() {
		mInWorld = false;
	}

	virtual const Ogre::Vector3 getVelocities() const = 0;

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	virtual btTransform getIntersection(btVector3 origin,
		btVector3 direction) = 0;

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally less expensive than the precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual btTransform getLocalIntersection(btVector3 origin,
		btVector3 direction) = 0;

	/**
	 * Get the precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally more expensive than the non-precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual btTransform getLocalPreciseIntersection(btVector3 origin,
		btVector3 direction) = 0;

	/**
	 * Compare the limb physics model to another limb physics  model.
	 * @param limbPhysics Another limb physics  model.
	 * @return If the limb physics  model is equal to the other limb physics  model.
	 */
	bool equals(const LimbPhysics & limbPhysics) const;

	//Accessor methods

	/**
	 * Get the inertia of the limb.
	 * @return The inertia of the limb.
	 */
	virtual const btVector3& getInertia() const = 0;

	/**
	 * Get the collision shape of the limb.
	 * @return
	 */
	virtual btCollisionShape* getCollisionShape() = 0;

	/**
	 * Is the limb in the physical world?
	 * @return Whether the limb is in the physical world or not.
	 */
	bool isInWorld() const {
		return mInWorld;
	}

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	virtual btVector3 getPosition() const = 0;

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	virtual btQuaternion getOrientation() const = 0;

	/**
	 * Get the volume of the limb.
	 * @return The volume of the limb.
	 */
	virtual const double getVolume() {
		if (mVolume != 0) {
			return mVolume;
		}

		double volume = 0;
		switch (mType) {
		case BLOCK: {
			volume = mDimensions.x * mDimensions.y * mDimensions.z;
			break;
		}
		case CAPSULE: {
			volume = pow(mDimensions.x * 0.5f, 2) * M_PI * mDimensions.z
				+ pow(mDimensions.x, 3) * M_PI / 6.0f;
			break;
		}
		}
		mVolume = volume;
		return volume;
	}

	double getInitialRelativeXPosition() const {
		return mInitialRelativeXPosition;
	}

	double getInitialRelativeYPosition() const {
		return mInitialRelativeYPosition;
	}

	double getInitialRelativeZPosition() const {
		return mInitialRelativeZPosition;
	}

	double getInitialWOrientation() const {
		return mInitialWOrientation;
	}

	double getInitialXOrientation() const {
		return mInitialXOrientation;
	}

	double getInitialYOrientation() const {
		return mInitialYOrientation;
	}

	double getInitialZOrientation() const {
		return mInitialZOrientation;
	}

	double getInterpenetrationDepth() const {
		return mInterpenetrationDepth;
	}

	void setInterpenetrationDepth(double interpenetrationDepth) {
		mInterpenetrationDepth = interpenetrationDepth;
	}

	const Ogre::Vector3 getDimensions() const {
		return mDimensions;
	}

	void setDimensions(const Ogre::Vector3 dimensions) {
		mDimensions = dimensions;
	}

	const Ogre::ColourValue getColor() const {
		return mColor;
	}

	void setColor(const Ogre::ColourValue color) {
		mColor = color;
	}

	PrimitiveType getType() const {
		return mType;
	}

	double getMass() const {
		return mMass;
	}

	double getFriction() const {
		return mFriction;
	}

	bool isIntraBodyColliding() const {
		return mIntraBodyColliding;
	}

	void setIntraBodyColliding(bool intraBodyColliding) {
		mIntraBodyColliding = intraBodyColliding;
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization*?

	 /**
	 * Serializes the limb physics model to a string.
	 * @param os The ostream.
	 * @param limbPhysics The limb physics model we want to serialize.
	 * @return A string containing all information about the limb physics model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const LimbPhysics &limbPhysics) {
		return os << "LimbPhysics: Type=" << limbPhysics.mType /**!< The primitive type of the limb*/

		<< "/Dimensions=(" /**!< The dimensions of the limb*/
		<< limbPhysics.mDimensions.x << "," << limbPhysics.mDimensions.y << ","
			<< limbPhysics.mDimensions.z

			<< ")/Color=(" /**!<The color of the limb*/
			<< limbPhysics.mColor.r << "," << limbPhysics.mColor.g << ","
			<< limbPhysics.mColor.b

			<< ")/isInWorld=" << limbPhysics.mInWorld /**!< if the limb physics model is in the world*/

			<< "/InitialRelativePosition=(" /**!< The limb's relative position*/
			<< limbPhysics.mInitialRelativeXPosition << ","
			<< limbPhysics.mInitialRelativeYPosition << ","
			<< limbPhysics.mInitialRelativeZPosition

			<< ")/InitialOrientation=(" /**!< The limb's orientation*/
			<< limbPhysics.mInitialWOrientation << ","
			<< limbPhysics.mInitialXOrientation << ","
			<< limbPhysics.mInitialYOrientation << ","
			<< limbPhysics.mInitialZOrientation

			<< ")/Restitution=" << limbPhysics.mRestitution /**!< The restitution of the limb physics model*/

			<< "/Friction=" << limbPhysics.mFriction /**!< The friction of the limb physics model*/

			<< "/Mass=" << limbPhysics.mMass /**!< The mass of the limb physics model*/

			<< "/Volume=" << limbPhysics.mVolume /**!< The volume of the limb physics model*/
			<< "/IntraBodyColliding=" << limbPhysics.mIntraBodyColliding; /**!< If the limb is colliding with the other limbs */
	}

	/**
	 * Serializes the limb physics model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mType) /**!< The primitive type of the limb*/

		& BOOST_SERIALIZATION_NVP(mDimensions.x) /**!< The dimensions of the limb*/
		& BOOST_SERIALIZATION_NVP(mDimensions.y)
			& BOOST_SERIALIZATION_NVP(mDimensions.z)

			& BOOST_SERIALIZATION_NVP(mColor.r) /**!< The color of the limb*/
			& BOOST_SERIALIZATION_NVP(mColor.g)
			& BOOST_SERIALIZATION_NVP(mColor.b)

			& BOOST_SERIALIZATION_NVP(mInitialRelativeXPosition) /**!< The limb's relative position*/
			& BOOST_SERIALIZATION_NVP(mInitialRelativeYPosition)
			& BOOST_SERIALIZATION_NVP(mInitialRelativeZPosition)

			& BOOST_SERIALIZATION_NVP(mInitialWOrientation) /**!< The limb's orientation*/
			& BOOST_SERIALIZATION_NVP(mInitialXOrientation)
			& BOOST_SERIALIZATION_NVP(mInitialYOrientation)
			& BOOST_SERIALIZATION_NVP(mInitialZOrientation)

			& BOOST_SERIALIZATION_NVP(mRestitution) /**!< The restitution of the limb physics model*/

			& BOOST_SERIALIZATION_NVP(mFriction) /**!< The friction of the limb physics model*/

			& BOOST_SERIALIZATION_NVP(mMass) /**!< The mass of the limb physics model*/
			& BOOST_SERIALIZATION_NVP(mIntraBodyColliding);/**!< If the limb is colliding with the other limbs */
	}

protected:

	PrimitiveType mType; /**!< The primitive type of this limb. */

	Ogre::Vector3 mDimensions; /**!< The dimensions of the limb. */

	Ogre::ColourValue mColor; /**!< The color of the limb. */

	double mInitialRelativeXPosition, /**!< Initial position at birth relative to the root node*/
	mInitialRelativeYPosition, mInitialRelativeZPosition;

	double mInitialXOrientation, mInitialYOrientation, /**!< Initial orientation at birth */
	mInitialZOrientation, mInitialWOrientation;

	double mRestitution; /**!< Restitution is the amount of force that is reflected in a collision. It is similar to elasticity. */

	double mFriction; /**!< The friction of this segment. */

	double mMass; /**!< Mass of the limb. */

	double mVolume; /**!< The volume of the limb. */

	bool mIntraBodyColliding; /**!< If the limb collides with the other limbs */

	// should not be serialized
	bool mInWorld; /**!< Whether the limb is in the world or not.*/

	// should not be serialized
	double mInterpenetrationDepth; /**!< The interpenetration depth of this limb with the others. */
};
BOOST_CLASS_VERSION(LimbPhysics, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(LimbPhysics)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_ */
