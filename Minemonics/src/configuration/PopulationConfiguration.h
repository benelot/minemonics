#ifndef CONFIGURATION_POPULATIONCONFIGURATION_H_
#define CONFIGURATION_POPULATIONCONFIGURATION_H_

//# corresponding header
//# forward declarations
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

/**
 * @brief		The configuration of populations that are subject to the evolutionary algorithms.
 * @details		Details
 * @date		2015-03-10
 * @author		Benjamin Ellenberger
 */
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
