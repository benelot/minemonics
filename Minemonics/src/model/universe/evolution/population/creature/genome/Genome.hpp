#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <stddef.h>
#include <iostream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The genome is the base class of all subclasses of genomes.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Genome {
public:
	enum GenomeType {
		UnknownGenome, MixedGenome, NUM_GENOMETYPES
	};

	enum SplitAxis {
		X_AXIS, Y_AXIS, Z_AXIS
	};

	Genome(const GenomeType type);
	virtual ~Genome();

	/**
	 * Add a gene to the genome.
	 * @param gene The gene to add to the genome.
	 */
	void addGene(Gene* const gene);

	/**
	 * @brief Compare this genome to another genome.
	 * @param genome another genome.
	 * @return If the genome is equal to the other genome.
	 */
	bool equals(const Genome& genome) const;

	/**
	 * Clone the genome.
	 * @return The clone of the genome.
	 */
	virtual Genome* clone() = 0;

	/**
	 * Variational genetics
	 * -------------------
	 * Variational genetics includes every type of modifying genome operator that usually leads
	 * to a generatable new genome thereby causing new variability.
	 */
	/**
	 * # Mutations
	 * -----------
	 * Mutations include changes in the genome involving only one genome.
	 */

	/**
	 * Add random genes with probability.
	 * @param addProbability The probability of adding a gene.
	 */
	virtual void addRandomGenes(const double addProbability) = 0;

	/**
	 *  Add a new, randomly generated gene to the genome.
	 */
	virtual void addRandomGene() = 0;

	/**
	 * Repair the genes by checking their integrity.
	 */
	virtual void repairGenes() = 0;

	/**
	 * Increases the number of branches to other genes of random genes.
	 * @param integrationProbability
	 * 							The probability of adding new branches.
	 */
	virtual void integrateRandomGenes(const double integrationProbability) = 0;

	/**
	 * Increases the number of branches to other genes of a random gene.
	 */
	virtual void integrateRandomGene() = 0;

	/**
	 * Increases the number of branches to other genes of a gene defined by the gene index in the mixed genome.
	 * @param geneIndex
	 * 				The gene index in the mixed genome.
	 */
	virtual void integrateGene(const int geneIndex) = 0;

	/**
	 * @brief Replaces random genes with other random genes.
	 * @param replacementProbability
	 * 							The probability of replacing genes.
	 */
	virtual void replaceRandomGenesWithRandomGenes(
	const double replacementProbability) = 0;

	/**
	 * Replaces a random gene with another random gene.
	 */
	virtual void replaceRandomGeneWithRandomGene() = 0;

	/**
	 * @brief		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original.
	 * @details		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original. The new segment specification is not an exact copy of the original, but contains adjustments meant to preserve self-loops in the branching pattern of the body tree.
	 * A self-loop arises when branch specifications dictate that segments of a particular type should have child segments of the same type. The segment copying mutation preserves this direct recursion in the tree structure when copying a segment specification from one index in the segment specification vector to another.
	 */
	virtual void replaceGeneWith(const int geneIndex,
	const int replacementIndex) = 0;

	/**
	 * Duplicate random genes with probability.
	 * @param duplicateProbability
	 * 							The probability of one gene to be duplicated.
	 */
	virtual void duplicateRandomGenes(const double duplicateProbability) = 0;

	/**
	 * Duplicates a random gene.
	 */
	virtual void duplicateRandomGene() = 0;

	/**
	 * Duplicate the gene with index.
	 * @param geneIndex
	 * 				The index of the gene to be duplicated.
	 */
	virtual void duplicateGene(const int geneIndex) = 0;

	/**
	 * Splits random genes with probability.
	 * @param splitProbability
	 * 						The probability to split a gene.
	 */
	virtual void splitRandomGenes(const double splitProbability) = 0;

	/**
	 * Split a random gene into two of summated equal size.
	 */
	virtual void splitRandomGene() = 0;

	/**
	 * @brief		The segment splitting mutation method is meant be a conservative means of increasing body complexity. It attempts to replace all segments of a chosen type in the body with two segments connected by a joint but together occupying roughly the same space in the body as the segments they replace.
	 * @details		The segment splitting mutation method is meant be a conservative means of increasing body complexity. It attempts to replace all segments of a chosen type in the body with two segments connected by a joint but together occupying roughly the same space in the body as the segments they replace.
	 * The effect of the segment splitting mutation method is to keep the creature morphology more or less
	 * the same, though this is by no means always the outcome, while splitting all segments of the chosen
	 * type into segments of half the original length. The split occurs half of the way along the segments'
	 * local z-axes, between the face upon which they have a joint anchor point joining them to their parent
	 *  segments, and the opposite face.
	 *  @param geneIndex
	 *  			The gene index of the gene to be split.
	 *  @param axis
	 *  			The axis along which the gene should be split.
	 */
	virtual void splitGene(const int geneIndex, const SplitAxis axis) = 0;

	/**
	 * Grow random stubs in the genome with probability.
	 * @param growProbability
	 * 					The probability of a gene to be grown.
	 */
	virtual void growRandomStubs(const double growProbability) = 0;

	/**
	 * Grow a random stub.
	 */
	virtual void growRandomStub() = 0;

	/**
	 * @brief		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches.
	 * @details		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches. Many mutations that result in new branches often produced large
	 * complicated structures that, should they appear on a creature already fairly evolved, are almost always extremely detrimental. This mutation was created as a means of providing a
	 * more subtle mutation that adds complexity to a creature's morphology with what is intended to be a reduced impact on fitness.
	 *
	 * The check for the 'stub' growing mutation is the final step in mutating a creature's segment specifications.
	 * @param geneIndex
	 * 				The index of the gene to be grown.
	 * @param branchiness
	 * 				A number branches between 0 and branchiness are grown.
	 */
	virtual void growStub(const int geneIndex, const int branchiness) = 0;

	/**
	 * Mutate random genes with probability.
	 * @param mutationProbability
	 * 							The probability to mutate a gene.
	 */
	virtual void mutateRandomGenes(const double mutationProbability) = 0;

	/**
	 * Mutate a random gene.
	 */
	virtual void mutateRandomGene() = 0;

	/**
	 * @brief		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * @details		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * The new segment specification is created by calling a segment specification constructor and passing it a bushiness parameter between 0.1 and 0.9,
	 * chosen uniformly at random. The bushiness parameter is used directly as the probability probability that any given branch specification
	 * in the segment specification will have its enable flag set to true instead of false. A high bushiness parameter is more likely to produce
	 * a segment with many branches.
	 * @param geneIndex
	 * 					The index of the gene to be mutated.
	 */
	virtual void mutateGene(const int geneIndex) = 0;

	/**
	 * Mutate random branches with probability.
	 * @param mutationProbability
	 * 							The probability to mutate a branch.
	 */
	virtual void mutateRandomBranches(const double mutationProbability) = 0;

	/**
	 * Mutate a random branch of a random gene.
	 */
	virtual void mutateRandomBranch() = 0;

	/**
	 * Mutate a random branch of a certain gene.
	 * @param geneIndex
	 * 					The gene index of which a random branch should be mutated.
	 */
	virtual void mutateRandomBranchOfGene(const int geneIndex) = 0;

	/**
	 * Mutate a certain branch of a certain gene.
	 * @param geneIndex
	 * 					The gene index of which a branch should be mutated.
	 * @param branchIndex
	 * 					The branch index of the branch to be mutated.
	 */
	virtual void mutateBranch(const int geneIndex, const int branchIndex) = 0;

	/**
	 * # Crossover
	 * -----------
	 * Crossover includes every change in genome involving more than one genome.
	 */

	/**
	 * Crossover randomly with father genome.
	 * @param fatherGenome
	 * 					The genome of the father.
	 */
	virtual void crossoverRandomly(Genome* const fatherGenome) = 0;

	/**
	 * @brief Crossover with other genome where we keep all genes between motherSegmentStartIndex and motherSegmentEndIndex
	 * and append all between fatherSegmentStartIndex and fatherSegmentEndIndex to this genome.
	 * @param fatherGenome The genome of the father
	 * @param motherSegmentStartIndex
	 * 							The segment index in this genome where the copying starts.
	 * @param motherSegmentEndIndex
	 * 							The segment index in this genome where the copying ends.
	 * @param fatherSegmentStartIndex
	 * 							The segment index in the father genome where the copying starts.
	 * @param fatherSegmentEndIndex
	 * 							The segment index in the father genome where the copying ends.
	 */
	virtual void crossover(Genome* const fathergenome,
	const int motherSegmentStartIndex, const int motherSegmentEndIndex,
	const int fatherSegmentStartIndex, const int fatherSegmentEndIndex) = 0;

	/**
	 * @brief Grafts a random feature from the donor over to this genome.
	 * @param donor The donor of the feature.
	 */
	virtual void graftRandomlyFrom(Genome* const donator) = 0;

	/**
	 * @brief Grafting copies a feature of the donor over to the receiver beginning
	 * at the indicated gene by copying the gene and its directed subgraph over,
	 * by following the links up to the maximum link depth and by copying all
	 * the genes that are met on the way. Then the newly added feature is
	 * connected randomly to the other genes to integrate it.
	 *
	 * @param donor
	 *            Donates the new feature
	 * @param attachmentIndex
	 * 			 The gene at which the graft should be attached.
	 * @param geneIndex
	 * 			 The indicated gene where to start grafting
	 * @param geneQty
	 *            Number of genes to copy
	 */
	virtual void graftFrom(Genome* const donor, const int attachmentIndex,
	const int geneIndex, const int geneQty) = 0;

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization.*/

	/**
	 * @brief Serializes the genome to a string.
	 * @param os
	 * 			The ostream.
	 * @param genome
	 * 			The genome we want to serialize.
	 * @return A string containing all information about the genome.
	 */

	friend std::ostream & operator<<(std::ostream &os, const Genome &genome) {
		os

		<< "MixedGenome: Type: " << genome.mGenomeType /**!< The type of genome*/

		<< "/length=" << genome.mLength; /**!< The length of the genome*/

		os << "/Genes=[";
		for (std::vector<Gene*>::const_iterator it = genome.mGenes.begin(); /**!< The vector of genes.*/
		it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "||";
		}
		os << "]";

		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		//in order to detect a derived class type from a base type for serialization,
		//you have to register the derived class type in beforehand.
		ar.register_type(static_cast<Morphogene*>(NULL));
		ar & BOOST_SERIALIZATION_NVP(mRootIndex) /**!< The root index */
		& BOOST_SERIALIZATION_NVP(mGenomeType) /**!< The type of the genome*/
		& BOOST_SERIALIZATION_NVP(mLength) /**!< The length of the genome*/
		& BOOST_SERIALIZATION_NVP(mBranchiness) /**!< The branchiness of the genome*/
		& BOOST_SERIALIZATION_NVP(mGenes); /**!< The vector of genes.*/
	}

	// Accessor methods ##########################

	std::vector<Gene*>& getGenes() {
		return mGenes;
	}

	const std::vector<Gene*>& getGenes() const {
		return mGenes;
	}

	GenomeType getGenomeType() const {
		return mGenomeType;
	}

	int getLength() const {
		return mLength;
	}

	int getRootIndex() const {
		return mRootIndex;
	}

	void setRootIndex(int rootIndex) {
		mRootIndex = rootIndex;
	}

protected:

	int mRootIndex; /**!< The root index */

	int mLength; /**!< The length of the genome */

	std::vector<Gene*> mGenes; /**!< The genes of the genome */

	GenomeType mGenomeType; /**!< The type of genome */

	double mBranchiness; /**!< The branchiness of the genome */
};
BOOST_CLASS_VERSION(Genome, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Genome)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_ */
