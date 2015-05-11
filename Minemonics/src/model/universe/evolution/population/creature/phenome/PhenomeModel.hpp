#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_

//# corresponding headers
//# forward declarations
class SimulationManager;
class Creature;
class MixedGenome;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/controller/Controller.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The phenome model holds all the state information of the phenome independent of other models.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class PhenomeModel {
public:
	PhenomeModel();
	virtual ~PhenomeModel();

	void initialize(SimulationManager* simulationManager,btDynamicsWorld* world);

	/**
	 * @brief Perform the generation of the creature embryo.
	 * @details Details
	 * @param creature The creature handle we want to get back from the physics engine when we pick the creature.
	 * @param genome The genome of the creature to be built.
	 * @param rootPosition The position of origin where the creature starts to be generated in the physical space.
	 */
	void performEmbryogenesis(Creature* creature,MixedGenome* genome, Ogre::Vector3 rootPosition);


	void update(double totalMilliseconds);

	//Accessor methods
	/**
	 * Is the phenotype in the world?
	 * @return
	 */
	bool isInWorld() const {
		return inWorld;
	}

	/**
	 * Set whether the phenotype is in the world or not.
	 * @param inWorld Whether the phenotype is in the world or not.
	 */
	void setInWorld(bool inWorld) {
		this->inWorld = inWorld;
	}

	std::vector<Controller*>& getControllers() {
		return mControllers;
	}

	void setControllers(const std::vector<Controller*>& controllers) {
		mControllers = controllers;
	}

	const std::vector<ComponentModel*>& getComponentModels() const {
		return mComponentModels;
	}

private:

	/**
	 * Handle to the dynamics world.
	 */
	btDynamicsWorld* mWorld;

	/**
	 * Handle to the simulation manager
	 */
	SimulationManager* mSimulationManager;

	/**
	 * Whether the phenome is in the world or not.
	 */
	bool inWorld;

	/**
	 * The vector of phenotype component models.
	 */
	std::vector<ComponentModel*> mComponentModels;

	/**
	 * The vector of phenotype limb models.
	 */
	std::vector<LimbModel*> mLimbModels;

	/**
	 * The vector of phenotype joint models.
	 */
	std::vector<JointModel*> mJointModels;

	//std::vector<Sensor*> mSensors;

	/**
	 * The vector of phenotype joint controller models.
	 */
	std::vector<Controller*> mControllers;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_PHENOMEMODEL_HPP_ */
