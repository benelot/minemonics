#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_

//# corresponding header
//# forward declarations
class PhenomeModel;

//# system headers
#include <list>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/genetics/embryogenesis/PhenotypeGenerator.hpp>

//## view headers
//## utils headers

/**
 * @brief		The embryogenesis builds a phenotype according to the specification in the gentype.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class Embryogenesis {
public:
	Embryogenesis();
	virtual ~Embryogenesis();

	static void transcribeGene(std::list<PhenotypeGenerator*>& generatorList,
			int& totalSegmentCounter, PhenomeModel* phenomeModel,
			BaseGenerator* generator);

	static void transcribeMorphoGene(
			std::list<PhenotypeGenerator*>& generatorList,
			int& totalSegmentCounter, PhenomeModel* phenomeModel,
			PhenotypeGenerator* generator);
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_ */
