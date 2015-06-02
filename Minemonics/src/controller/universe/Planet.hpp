#ifndef CONTROLLER_UNIVERSE_PLANET_HPP_
#define CONTROLLER_UNIVERSE_PLANET_HPP_

//# corresponding header
//# forward declarations
class Environment;
class Evolution;

//# system headers
//## controller headers
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/environments/Environment.hpp>

//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

/**
 * @brief		The planet controller holds an evolution together with a certain environment in which it is evaluated.
 * @details		Details
 * @date		2015-05-06
 * @author		Benjamin Ellenberger
 */
class Planet {
public:
	Planet();
	virtual ~Planet();

	/**
	 * Initialize the planet.
	 * @param simulationManager The simulation manager.
	 * @param type The type of the environment.
	 * @param debugDrawer The debug drawer of this simulation.
	 */
	void initialize(SimulationManager* simulationManager,
			Environment::EnvironmentType type, OgreBtDebugDrawer* debugDrawer);

	/**
	 * Add a population to the planet.
	 * @param population The population to be added to the planet.
	 */
	void addPopulation(Population* population);

	/**
	 * Draw the debug world if debug drawing is enabled.
	 */
	void drawDebugWorld();

	/**
	 * Step the universe physics forward.
	 * @param timeSinceLastFrame The size of the time step.
	 */
	void stepPhysics(double timeSinceLastFrame);

	/**
	 * Update the model of the planet.
	 */
	void update();

	/**
	 * Proceed with the evaluation. In in serial mode, this just goes on to the next evaluation, in parallel, this schedules one more evaluation.
	 * @return If true then this means it proceeded successfully, if false this means that the generation is over and evaluated.
	 */
	bool proceedEvaluation();

	//Accessor methods
	/**
	 * Get the environment of the planet.
	 * @return The environment of the planet.
	 */
	Environment*& getEnvironment() {
		return mEnvironment;
	}

	/**
	 * Set the environment of the planet.
	 * @param environment The environment of the planet.
	 */
	void setEnvironment(Environment*& environment) {
		mEnvironment = environment;
	}

	Evolution*& getEvolution() {
		return mEvolution;
	}

	void setEvolution(Evolution*& evolution) {
		mEvolution = evolution;
	}

	PlanetModel& getPlanetModel() {
		return mPlanetModel;
	}

private:

	/**
	 * The model of this planet.
	 */
	PlanetModel mPlanetModel;

	/**
	 * The evolution on this planet.
	 */
	Evolution* mEvolution;

	/**
	 * The environment of this planet.
	 */
	Environment* mEnvironment;
};

#endif /* CONTROLLER_UNIVERSE_PLANET_HPP_ */
