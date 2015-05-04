#ifndef CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_HPP_
#define CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_HPP_

//# corresponding header
//# forward declarations
class SimulationManager;
class MixedGenome;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/physics/PhysicsController.hpp>
#include <controller/evolution/population/creature/phenome/Component.hpp>
#include <controller/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/evolution/population/creature/phenome/morphology/Limb.hpp>

//## model headers
#include <model/evolution/population/creature/genome/MixedGenome.hpp>
#include <model/evolution/population/creature/genome/Gene.hpp>
#include <model/evolution/population/creature/phenome/PhenomeModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The phenome controller synchronizes the graphical representation of the creature with the physical model in the physics engine.
 * @details		The phenome controller synchronizes the graphical representation of the creature with the physical model in the physics engine.
 * It also acts as a facade for methods of the physical and graphical models. Each creature's body is composed of a number of cuboids called "body segments". The
 * segments are arranged in a tree structure with each segment connected to its parent by a
 * type of physical constraint known as a universal joint. Segments are divided into groups
 * called types, with the properties of each type encoded in the genotype. Each
 * cuboid is a rigid solid with uniform density. The density value is a variable. Source: Lee Graham
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Phenome {
public:
	Phenome();
	virtual ~Phenome();

	/**
	 * @brief Initialize the phenotype with the simulation manager handle.
	 * @details Details
	 * @param simulationManager The handle of the simulation manager.
	 */
	void initialize(SimulationManager* simulationManager);

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 * @param genome The genome of the creature to be built.
	 * @param rootPosition The position of origin where the creature starts to be generated in the physical space.
	 */
	void performEmbryogenesis(MixedGenome* genome, Ogre::Vector3 rootPosition);

	/**
	 * Update the graphical representation of the creature with its physical representation.
	 */
	void update();

	/**
	 * Add the phenotype to the physical and graphical world.
	 */
	void addToWorld();

	/**
	 * Remove the phenotype from the physical and graphical world.
	 */
	void removeFromWorld();

	//Accessor methods
	/**
	 * Get the components the phenotype is built of.
	 * @return The components the phenotype is built of.
	 */
	std::vector<Component*>& getComponents() {
		return mComponents;
	}

	/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool isInWorld() const {
		return mPhenomeModel.isInWorld();
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void setInWorld(bool inWorld) {
		mPhenomeModel.setInWorld(inWorld);
	}

private:
	/**
	 * The phenome model representation.
	 */
	PhenomeModel mPhenomeModel;

	/**
	 * The simulation manager handle
	 */
	SimulationManager* mSimulationManager;

	/**
	 * The physics world of the physics engine.
	 */
	btDynamicsWorld* mWorld;

	/**
	 * The vector of phenotype components
	 */
	std::vector<Component*> mComponents;

	/**
	 * The vector of the phenotype's limbs
	 */
	std::vector<Limb*> mLimbs;

	/**
	 * The vector of the phenotype's joints between the limbs.
	 */
	std::vector<Joint*> mJoints;

	/**
	 * The controllers of the phenotype
	 */
	std::vector<Controller*> mControllers;

};

#endif /* CONTROLLER_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOME_HPP_ */
