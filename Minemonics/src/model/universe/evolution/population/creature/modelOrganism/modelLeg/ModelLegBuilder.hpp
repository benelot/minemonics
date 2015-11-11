#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_MODELLEGBUILDER_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_MODELLEGBUILDER_HPP_

//# corresponding headers
//# forward declarations
class MixedGenome;

//# system headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The model leg builder creates a simple model leg in the genome.
 * @details		Details
 * @date		2015-11-05
 * @author		Benjamin Ellenberger
 */
class ModelLegBuilder {
public:
	static void build(MixedGenome* genome,ControllerGene::ControllerGeneType controllerType);
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_MODELORGANISM_MODELLEG_MODELLEGBUILDER_HPP_ */
