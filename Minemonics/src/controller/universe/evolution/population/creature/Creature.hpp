#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_

//# corresponding header
//# forward declarations
class SimulationManager;
class Population;

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/Phenome.hpp>

//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/population/creature/CreatureModel.hpp>

//## view headers
//## utils headers

/**
 * @brief		The creature controller synchronizes the model with the view.
 * @details		Details
 * @date		2015-04-07
 * @author		Benjamin Ellenberger
 */
class Creature {
public:
	Creature(SimulationManager* const simulationManager,
			Population* const population, const Ogre::Vector3 position,
			const double branchiness);
	Creature(SimulationManager* const simulationManager,
			CreatureModel* const creatureModel);
	virtual ~Creature();

	/**
	 * Initialize the creature.
	 * @param simulationManager The simulation manager
	 * @param population The population the creature belongs to.
	 * @param position The position the creature should be created in.
	 * @param branchiness The branchiness factor of the creature.
	 */
	void initialize(SimulationManager* const simulationManager,
			Population* const population, const Ogre::Vector3 position,
			const double branchiness);

	/**
	 * Perform embryogenesis on the creature to build his phenotype from the genotype.
	 */
	void performEmbryogenesis();

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reset the creature to its former position.
	 */
	void reset();

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Update the creature as it moves.
	 */
	void update();

	/**
	 * Add the creature to the world.
	 */
	void addToWorld();

	/**
	 * Remove the creature from the world.
	 */
	void removeFromWorld();

	// Facade accessor methods
	void setPosition(const Ogre::Vector3 position) {
		mCreatureModel->setPosition(position);
	}

	PlanetModel* getPlanet() {
		return mCreatureModel->getPopulationModel()->getPlanetModel();
	}

	void setPlanet(PlanetModel* planetModel) {
		mCreatureModel->getPopulationModel()->setPlanetModel(planetModel);
	}

	bool isDeveloped() {
		return mCreatureModel->isDeveloped();
	}

	void setDeveloped(bool developed) {
		mCreatureModel->setDeveloped(developed);
	}

	CreatureModel* getCreatureModel() {
		return mCreatureModel;
	}

	bool isCulled() const {
		return mCreatureModel->isCulled();
	}

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>("Creature"));
		}
	} _initializer;

	/**
	 * The model representation of the creature
	 */
	CreatureModel* mCreatureModel;

	//CHILD
	/**
	 * The phenotype of the creature.
	 */
	Phenome mPhenotype;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_CREATURE_HPP_ */
