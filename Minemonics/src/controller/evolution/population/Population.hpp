/*
 * Population.hpp
 *
 *  Created on: Apr 29, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_EVOLUTION_POPULATION_POPULATION_HPP_
#define CONTROLLER_EVOLUTION_POPULATION_POPULATION_HPP_

#include <model/evolution/population/PopulationModel.hpp>

/*
 *
 */
class Population {
public:
	Population();
	virtual ~Population();

private:
	/**
	 * The state model of the population
	 */
	PopulationModel mPopulationModel;
};

#endif /* CONTROLLER_EVOLUTION_POPULATION_POPULATION_HPP_ */
