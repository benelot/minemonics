#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_SRBEMBRYOGENESIS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_SRBEMBRYOGENESIS_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class btTransform;
class SRBLimbBt;
class SRBLimbModel;
class SRBPhenomeModel;
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
 * @brief		The SRBEmbryogenesis builds a phenotype according to the specification in the genotype.
 * @details		Details
 * @date		2015-05-20
 * @author		Benjamin Ellenberger
 */
class SRBEmbryogenesis {
public:

	/**
	 * Transcribe a gene into the component it represents.
	 * @param generatorList The generator list in case new generators are added by it.
	 * @param totalSegmentCounter The total segment counter for phenotype elements.
	 * @param phenomeModel The phenome model where the new components are added.
	 * @param generator The generator of that should be transcribed.
	 */
	static void transcribeGene(std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter, SRBPhenomeModel* phenomeModel,
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
		SRBPhenomeModel* phenomeModel, PhenotypeGenerator* generator);

	static void calculateChildPositionRelativeToParent(PhenotypeGenerator* generator,
		btTransform& parentHitTransform, btTransform& childHitTransform,
		Morphogene* childMorphogene, SRBPhenomeModel* phenomeModel,
		Ogre::Vector3& localParentJointInRefParent,
		Ogre::Vector3& localChildJointInRefChild);

	static SRBLimbModel* createLimb(PhenotypeGenerator* generator,Morphogene* childMorphogene,SRBPhenomeModel* phenomeModel);

	static void appendToParentLimb(SRBPhenomeModel* phenomeModel,
		SRBLimbModel* childLimb, PhenotypeGenerator* generator,
		Ogre::Vector3& localParentJointInRefParent,
		Ogre::Vector3& localChildJointInRefChild,
		btTransform& parentHitTransform, btTransform& childHitTransform);

	static void createNewGenerators(SRBPhenomeModel* phenomeModel,
		Morphogene * childMorphogene, SRBLimbModel* childLimb,
		PhenotypeGenerator* generator,
		std::list<PhenotypeGenerator*>& generatorList,
		int& totalSegmentCounter);

	static btTransform getParentIntersection(PhenotypeGenerator* generator,
		SRBLimbBt* parentLimb, MorphogeneBranch* parentMorphogeneBranch,
		Ogre::Vector3 parentLimbCOM,
		Ogre::Vector3 localParentAnchorDirInRefParent);

	static btTransform getOwnIntersection(SRBPhenomeModel* phenomeModel,
		Morphogene* childMorphogene, PhenotypeGenerator* generator,
		Ogre::Vector3 localChildAnchorDirInRefChild);
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENETICS_EMBRYOGENESIS_SRBEMBRYOGENESIS_HPP_ */
