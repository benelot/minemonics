#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class btTransform;
class LimbPhysics;
class LimbModel;
class PhenomeModel;
class Morphogene;
class MorphogeneBranch;

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
#include <model/universe/evolution/population/creature/genome/genetics/PhenotypeGenerator.hpp>

//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The Embryogenesis builds a phenotype according to the specification in the genotype.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class Embryogenesis {
public:
	/**
	 * Transcribe a gene into the component it represents.
	 * @param generatorList The generator list in case new generators are added by it.
	 * @param totalSegmentCounter The total segment counter for phenotype elements.
	 * @param phenomeModel The phenome model where the new components are added.
	 * @param generator The generator of that should be transcribed.
	 */
	static void transcribeGene(std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter, PhenomeModel* phenomeModel,
		BaseGenerator* generator);

	/**
	 * Transcribe a morphogene into the component it represents.
	 * @param generatorList The generator list in case new generators are added by it.
	 * @param totalSegmentCounter The total segment counter for phenotype elements.
	 * @param phenomeModel The phenome model where the new components are added.
	 * @param generator The generator of that should be transcribed.
	 */
	static void transcribeMorphogene(
		std::list<PhenotypeGenerator*>& generatorList, int& totalSegmentCounter,
		PhenomeModel* phenomeModel, PhenotypeGenerator* generator);

	static void createNewGenerators(PhenomeModel* phenomeModel,
		Morphogene* childMorphogene, LimbModel* childLimb,
		PhenotypeGenerator* generator,
		std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter);

private:
	/**
		 * The boost logger.
		 */
		static BoostLogger mBoostLogger;

		/**
		 * Initializer of the boost logger to include the class name into the logging messages.
		 */
		static class _Init {
		public:
			_Init() {
				mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant < std::string
						> ("Embryogenesis"));
			}
		} _initializer;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_EMBRYOGENESIS_HPP_ */
