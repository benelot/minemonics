#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_

//# corresponding header
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */
class btQuaternion;
class btVector3;

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

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

	/**
	 * Add the limb to the physical world.
	 */
	virtual void addToWorld(){
		mInWorld = true;
	}

	/**
	 * Remove the limb from the physical world.
	 */
	virtual void removeFromWorld(){
		mInWorld = false;
	}

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	virtual btVector3 getIntersection(btVector3 origin,
			btVector3 direction) = 0;

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally less expensive than the precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual btVector3 getLocalIntersection(btVector3 origin,
			btVector3 direction) = 0;

	/**
	 * Get the precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally more expensive than the non-precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	virtual btVector3 getLocalPreciseIntersection(btVector3 origin,
			btVector3 direction) = 0;

	/**
	 * Compare the limb physics model to another limb physics  model.
	 * @param limbPhysics Another limb physics  model.
	 * @return If the limb physics  model is equal to the other limb physics  model.
	 */
	bool equals(const LimbPhysics & limbPhysics) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the limb physics model to a string.
	 * @param os The ostream.
	 * @param limbPhysics The limb physics model we want to serialize.
	 * @return A string containing all information about the limb physics model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const LimbPhysics &limbPhysics) {
		return os
		/**If the limb physics is in the world*/
		<< "LimbPhysics: isInWorld=" << limbPhysics.mInWorld

		/**The restitution of the limb*/
		<< "/Restitution=" << limbPhysics.mRestitution

		/**The friction of the limb*/
		<< "/Friction=" << limbPhysics.mFriction;
	}

	//Accessor methods

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
	virtual const double getVolume() = 0;

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

protected:

	/**
	 * Whether the limb is in the world or not.
	 */
	bool mInWorld;

	/**
	 * Initial position at birth relative to the root node
	 */
	double mInitialRelativeXPosition, mInitialRelativeYPosition,
			mInitialRelativeZPosition;

	/**
	 * Initial orientation at birth
	 */
	double mInitialXOrientation, mInitialYOrientation, mInitialZOrientation,
			mInitialWOrientation;

	/**
	 * Restitution is the amount of force that is reflected in a collision. It is similar to elasticity.
	 */
	double mRestitution;

	/**
	 * The friction of this segment.
	 */
	double mFriction;

	/**
	 * Mass of the limb.
	 */
	double mMass;

	/**
	 * The volume of the limb.
	 */
	double mVolume;

	double mInterpenetrationDepth;

	LimbModel::PrimitiveType mType;

};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_HPP_ */
