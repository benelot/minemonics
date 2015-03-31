/*
 * PopulationConfiguration.h
 *
 *  Created on: Mar 10, 2015
 *      Author: leviathan
 */

#ifndef CONFIGURATION_POPULATIONCONFIGURATION_H_
#define CONFIGURATION_POPULATIONCONFIGURATION_H_

class PopulationConfiguration {
public:

	/**
	 * Initial mean number of genes in a genome.
	 */
	static const unsigned POPULATION_GENES_INITIAL_MEAN = 30;

	/**
	 * Initial variance of genes in a genome.
	 */
	static const unsigned POPULATION_GENES_INITIAL_VAR = 30;
};

#endif /* CONFIGURATION_POPULATIONCONFIGURATION_H_ */
