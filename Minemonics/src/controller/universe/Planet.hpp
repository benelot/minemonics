#ifndef CONTROLLER_UNIVERSE_PLANET_HPP_
#define CONTROLLER_UNIVERSE_PLANET_HPP_

//# corresponding header
//# forward declarations
class Environment;
class Evolution;

//# system headers
//## controller headers
#include <controller/physics/PhysicsController.hpp>

//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/PlanetModel.hpp>

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

	void initialize(Evolution* evolution, Environment* environment,PhysicsController::PhysicsControllerType type);

	void initialize(Evolution* evolution, Environment* environment,PhysicsController* physicsController);

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

	/**
	 * The physics controller of this planet
	 */
	PhysicsController* mPhysicsController;
};

#endif /* CONTROLLER_UNIVERSE_PLANET_HPP_ */
