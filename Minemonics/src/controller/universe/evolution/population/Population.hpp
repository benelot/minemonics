#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_

//# corresponding headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//# forward declarations
class SimulationManager;
class Creature;

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
 * @brief		The population controller holds a certain amount of creatures together from which a we cull after evaluation.
 * @details		Details
 * @date		2015-03-09
 * @author		Benjamin Ellenberger
 */
class Population {
public:
	Population();
	virtual ~Population();

	/**
	 * Initializes the population and adds creatures up to the creatureQty. Each creature gets a bushiness value around an predefined mean with a predefined variance.
	 * @param simulationManager The simulation manager handle
	 * @param creatureQty The number of creatures that the population will consist of in every generation.
	 */
	void initialize(SimulationManager* simulationManager,int creatureQty);

	/**
	 * Adds a new creature to the population with the bushiness as a input.
	 * @param bushiness The bushiness determines the number of gene branches a gene has in this creature's genome.
	 */
	void addNewMember(double bushiness,Ogre::Vector3 rootPosition=Ogre::Vector3::ZERO);

	void update();

	void addToWorld();

	void removeFromWorld();

	std::vector<Creature*>& getCreatures() {
		return mCreatures;
	}

private:

	/**
	 * The simulation manager handle.
	 */
	SimulationManager* mSimulationManager;

	/**
	 * The creatures living in this population. All creatures in one population can mate together.
	 */
	std::vector<Creature*> mCreatures;

	/**
	 * The state model of the population
	 */
	PopulationModel mPopulationModel;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_POPULATION_HPP_ */
