#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_

//# corresponding headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//# forward declarations
class SimulationManager;
class Creature;
class Planet;

//# system headers
//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The population controller holds a certain amount of creatures together from which a we cull after evaluation.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Population {
public:
	Population();
	Population(PopulationModel* const populationModel);
	virtual ~Population();

	/**
	 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
	 * @param planet The planet the population lives on.
	 * @param creatureQty The number of creatures that the population will consist of in every generation.
	 */
	void initialize(Planet* const planet, const int creatureQty,
			const Ogre::Vector3 initialPosition);

	/**
	 * Initializes the population without adding creatures up to the creatureQty.
	 * @param planet The planet the population lives on.
	 * @param creatureQty The number of creatures that the population will consist of in every generation.
	 */
	void initialize(Planet* const planet, const int creatureQty);

	/**
	 * Adds a new creature to the population with the branchiness as a input.
	 * @param branchiness The branchiness determines the number of gene branches a gene has in this creature's genome.
	 */
	void addNewMember(const double branchiness,
			const Ogre::Vector3 rootPosition = Ogre::Vector3::ZERO);

	/**
	 * Adds a creature to the population.
	 */
	void addMember(Creature* const creature);

	/**
	 * Resynchronize this population with its model again.
	 */
	void resyncWithModel();

	/**
	 * Update the population.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Reset all individuals in the population.
	 */
	void reset();

	/**
	 * Add the population to the physics world.
	 */
	void addToPhysicsWorld();

	/**
	 * Add the population to the world.
	 */
	void addToWorld();

	/**
	 * Remove the population from the world.
	 */
	void removeFromWorld();

	//Accessor methods

	std::vector<Creature*>& getCreatures() {
		return mCreatures;
	}

	const std::vector<Creature*>& getCreatures() const {
		return mCreatures;
	}

	PopulationModel* getPopulationModel() {
		return mPopulationModel;
	}

	bool isOutOfSync() const {
		return mPopulationModel->isOutOfSync();
	}

	void setOutOfSync(const bool outOfSync) {
		mPopulationModel->setOutOfSync(outOfSync);
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
					boost::log::attributes::constant<std::string>(
							"Population"));
		}
	} _initializer;

	/**
	 * The planet the population lives on.
	 */
	Planet* mPlanet;

	/**
	 * The creatures living in this population. All creatures in one population can mate together.
	 */
	std::vector<Creature*> mCreatures;

	/**
	 * The state model of the population
	 */
	PopulationModel* mPopulationModel;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_ */
