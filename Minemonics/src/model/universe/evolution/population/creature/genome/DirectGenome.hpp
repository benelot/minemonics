#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/Genome.hpp>

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
 * @brief		The directly encoded genome is a one-to-one mapping from genotype to phenotype.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class DirectGenome: public Genome {
public:
	DirectGenome();
	virtual ~DirectGenome();
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_DIRECTGENOME_HPP_ */
