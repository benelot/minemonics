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

	void initialize(SimulationManager* simulationManager,
			Environment::EnvironmentType type, OgreBtDebugDrawer* debugDrawer);

	void addPopulation(Population* population);

	void drawDebugWorld();

	void stepPhysics(double timeSinceLastFrame);

	void update();

	bool proceedEvaluation();

	//Accessor methods
	Environment*& getEnvironment() {
		return mEnvironment;
	}

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
