#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_FSEMBRYOGENESIS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_FSEMBRYOGENESIS_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class btTransform;
class FSLimbBt;
class FSLimbModel;
class FSPhenomeModel;
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

/**
 * @brief		The FSEmbryogenesis builds a phenotype according to the specification in the genotype.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class FSEmbryogenesis {
public:
	/**
	 * Transcribe a gene into the component it represents.
	 * @param generatorList The generator list in case new generators are added by it.
	 * @param totalSegmentCounter The total segment counter for phenotype elements.
	 * @param phenomeModel The phenome model where the new components are added.
	 * @param generator The generator of that should be transcribed.
	 */
	static void transcribeGene(std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter, FSPhenomeModel* phenomeModel,
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
		FSPhenomeModel* phenomeModel, PhenotypeGenerator* generator);

	static FSLimbModel* createLimb(PhenotypeGenerator* generator,Morphogene* childMorphogene,FSPhenomeModel* phenomeModel);

	static void appendToParentLimb(FSPhenomeModel* phenomeModel,
		FSLimbModel* childLimb, PhenotypeGenerator* generator,
		Ogre::Vector3& localParentJointInRefParent,
		Ogre::Vector3& localChildJointInRefChild,
		btTransform& parentHitTransform, btTransform& childHitTransform);

	static void createNewGenerators(FSPhenomeModel* phenomeModel,
		Morphogene * childMorphogene, FSLimbModel* childLimb,
		PhenotypeGenerator* generator,
		std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter);

	static btTransform getParentIntersection(PhenotypeGenerator* generator,
		FSLimbBt* parentLimb, MorphogeneBranch* parentMorphogeneBranch,
		Ogre::Vector3 parentLimbCOM,
		Ogre::Vector3 localParentAnchorDirInRefParent);

	static btTransform getOwnIntersection(FSPhenomeModel* phenomeModel,
		Morphogene* childMorphogene, PhenotypeGenerator* generator,
		Ogre::Vector3 localChildAnchorDirInRefChild);
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_FSEMBRYOGENESIS_HPP_ */
