/*
 * Planet.hpp
 *
 *  Created on: May 6, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_UNIVERSE_PLANET_HPP_
#define CONTROLLER_UNIVERSE_PLANET_HPP_

//# corresponding header
//# forward declarations
class Environment;
class Evolution;

//# system headers
//## controller headers
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

class Planet {
public:
	Planet();
	virtual ~Planet();

	void initialize(Evolution* evolution, Environment* environment);

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
};

#endif /* CONTROLLER_UNIVERSE_PLANET_HPP_ */
