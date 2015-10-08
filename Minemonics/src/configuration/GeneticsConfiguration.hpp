#ifndef CONFIGURATION_GENETICSCONFIGURATION_H_
#define CONFIGURATION_GENETICSCONFIGURATION_H_

//# corresponding headers
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
//## utils headers

/**
 * @brief		The configuration of the genetic algorithms.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class GeneticsConfiguration {
public:
	static const unsigned GENES_INITIAL_MEAN = 15; /**!< Initial mean number of genes in a genome. */

	static const unsigned GENES_INITIAL_VAR = 5; /**!< Initial variance of genes in a genome. */

};

#endif /* CONFIGURATION_GENETICSCONFIGURATION_H_ */
