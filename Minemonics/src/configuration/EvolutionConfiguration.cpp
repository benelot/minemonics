/*
 * EvolutionConfiguration.cpp
 *
 *  Created on: May 8, 2015
 *      Author: leviathan
 */

#include <configuration/EvolutionConfiguration.hpp>

const double EvolutionConfiguration::REAPER_SOW_OFFSPRING[] = { 0.5, 0.25,
		0.125, 0.075, 0.075 };

const double EvolutionConfiguration::REAPER_SOW_FRESH_PERCENTAGE = 1.0
		- EvolutionConfiguration::REAPER_ATTRIBUTE_MUTATION_PERCENTAGE
		- EvolutionConfiguration::REAPER_CROSSOVER_PERCENTAGE
		- EvolutionConfiguration::REAPER_GENE_MUTATION_PERCENTAGE;
