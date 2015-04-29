#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_H_

//# corresponding header
//# forward declarations
class btQuaternion;
class btVector3;

//# system headers
//## controller headers
//## model headers
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
	LimbPhysics();
	virtual ~LimbPhysics();

	/**
	 * Add the limb to the physical world.
	 */
	virtual void addToWorld() = 0;

	/**
	 * Remove the limb from the physical world.
	 */
	virtual void removeFromWorld() = 0;


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

	//accessor methods

	/**
	 * Is the limb in the physical world?
	 * @return Whether the limb is in the physical world or not.
	 */
	bool isInWorld() const {
		return inWorld;
	}

	/**
	 * Get the position of the limb in the physical world.
	 * @return The position of the limb in the physical world.
	 */
	virtual btVector3 getPosition() = 0;

	/**
	 * Get the orientation of the limb in the physical world.
	 * @return The orientation of the limb in the physical world.
	 */
	virtual btQuaternion getOrientation() = 0;

protected:
	void setInWorld(bool inWorld) {
		this->inWorld = inWorld;
	}

private:
	/**
	 * Whether the limb is in the world or not.
	 */
	bool inWorld;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBPHYSICS_H_ */
