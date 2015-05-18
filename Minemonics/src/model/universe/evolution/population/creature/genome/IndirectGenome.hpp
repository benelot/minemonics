#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_

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
 * @brief		The indirectly encoded genome encodes the phenotype in classes.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class IndirectGenome: public Genome {
public:
	IndirectGenome();
	virtual ~IndirectGenome();
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_INDIRECTGENOME_HPP_ */
