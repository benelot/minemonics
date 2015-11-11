#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

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
 * @brief		The chaotic controller gene keeps the parameters for the chaotic controller.
 * @details		Details
 * @date		2015-10-30
 * @author		Benjamin Ellenberger
 */
class ChaoticControllerGene: public ControllerGene {
public:
	ChaoticControllerGene();
	ChaoticControllerGene(const ChaoticControllerGene& gene);
	virtual ~ChaoticControllerGene();

	virtual void initialize();

	/**
	 * Clone the chaotic controller gene.
	 * @return The cloned chaotic controller.
	 */
	virtual ChaoticControllerGene* clone();
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_CONTROLLER_CHAOTICCONTROLLERGENE_HPP_ */
