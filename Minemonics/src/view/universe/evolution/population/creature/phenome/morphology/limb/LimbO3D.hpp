#ifndef VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBO3D_H_
#define VIEW_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_LIMB_LIMBO3D_H_

//# corresponding headers
#include <view/universe/evolution/population/creature/phenome/morphology/limb/LimbGraphics.hpp>

//# forward declarations
class SimulationManager;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include<model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The graphical representation of the limb in Ogre3D.
 * @details		Details
 * @date		2014-12-19
 * @author		Benjamin Ellenberger
 */
class LimbO3D: public LimbGraphics {
public:
	LimbO3D(SimulationManager* simulationManager,
			const LimbModel* const limbModel);
	LimbO3D(const LimbO3D& limbO3D);

	virtual ~LimbO3D();

	/**
	 * Clone the limbO3D
	 * @return The clone of the limbO3D.
	 */
	virtual LimbO3D* clone();

	/**
	 * Update the graphical representation of the limb with the physical representation.
	 */
	virtual void update();

	/**
	 * Add the limb to the graphical world.
	 */
	void addToWorld();

	/**
	 * Add the limb to the graphical world.
	 */
	void removeFromWorld();

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the global reference frame.
	 */
	Ogre::Vector3 getIntersection(const Ogre::Vector3 origin,
			const Ogre::Vector3 direction);

	/**
	 * Get the intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally less expensive than the precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	Ogre::Vector3 getLocalIntersection(const Ogre::Vector3 origin,
			const Ogre::Vector3 direction);

	/**
	 * Get the precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb. This might be computationally more expensive than the non-precise version.
	 * @param origin The origin of the ray in the global reference frame.
	 * @param direction The direction of the ray.
	 * @return The precise intersection of a ray with origin and direction and the limb surface in the local reference frame of this limb.
	 */
	Ogre::Vector3 getLocalPreciseIntersection(const Ogre::Vector3 origin,
			const Ogre::Vector3 direction);

	//Accessor methods

	Ogre::Entity*& getEntity() {
		return mLimbEntity;
	}

	Ogre::SceneNode*& getEntityNode() {
		return mLimbEntityNode;
	}

private:

	/**
	 * The simulation manager handle
	 */
	SimulationManager* mSimulationManager;

	/**
	 * The limb object in the graphical world.
	 */
	Ogre::Entity* mLimbEntity;

	/**
	 * The entity node of the limb to perform rotations and translations with.
	 */
	Ogre::SceneNode* mLimbEntityNode;

};

#endif /* LIMBO3D_H_ */
