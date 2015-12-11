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
	static const unsigned GENE_QTY_INITIAL_MEAN = 20; /**!< Initial mean number of genes in a genome. */

	static const unsigned GENE_QTY_INITIAL_VAR = 5; /**!< Initial variance of genes in a genome. */

	static const double GENE_BRANCH_INITIAL_MEAN = 2.5f; /**!< The initial branch number mean */

	static const double GENE_BRANCH_INITIAL_VAR = 1.0f; /**!< The initial branch number variance */

};

#endif /* CONFIGURATION_GENETICSCONFIGURATION_H_ */
