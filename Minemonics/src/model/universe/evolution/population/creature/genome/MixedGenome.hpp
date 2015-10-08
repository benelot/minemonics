#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_MIXEDGENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_MIXEDGENOME_HPP_

//# corresponding headers
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <fstream>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>
#include <model/universe/evolution/population/creature/genome/IndirectGenome.hpp>

//## view headers
//## utils headers

/**
 * @brief		The mixed genome is an genome type that encodes the morphology and the neural network in a compact/indirect encoding.
 * @details		 A creature's genotype dictates a potentially-recursive (both indirectly and directly recursive)
 * branching pattern. The genome encodes properties for a fixed number of segment types, and associated
 * with each type is a fixed number of branch specifications that dictate the way in which a segment of
 * a given type sprouts branches of other segment types. The encoded information also specifies the scaling,
 * positioning, and other aspects of the branching.
 * The genetic representation of this morphology is a directed graph of
 * nodes and connections. Each graph contains the developmental instructions
 * for growing a creature, and provides a way of reusing instructions to
 * make similar or recursive components within the creature. A phenotype
 * hierarchy of parts is made from a graph by starting at a defined
 * root-node and synthesizing parts from the node information while tracing
 * through the connections of the graph. The graph can be recurrent. Nodes
 * can connect to themselves or in cycles to form recursive or fractal like
 * structures. They can also connect to the same child multiple times to
 * make duplicate instances of the same appendage.
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class MixedGenome: public IndirectGenome {
public:

	MixedGenome();
	MixedGenome(const MixedGenome& mixedGenome);

	virtual ~MixedGenome();

	/**
	 * @brief Create a randomly generated genome with the branchiness factor defining average number of gene branches.
	 * @param branchiness The branchiness factor defining average number of gene branches.
	 */
	void createRandomGenome(const double branchiness);

	/**
	 * @brief Compare this mixed genome to another mixed genome.
	 * @param genome another mixed genome.
	 * @return If the mixed genome is equal to the other mixed genome.
	 */
	bool equals(const MixedGenome& genome) const;

	/**
	 * Clone the mixed genome.
	 * @return The clone of the mixed genome.
	 */
	MixedGenome* clone();

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
	virtual void addRandomGenes(const double addProbability);

	/**
	 * Add a new, randomly generated gene to the genome.
	 */
	virtual void addRandomGene();

	virtual void addRandomGeneBranches(double percentage);

	virtual void addRandomGeneBranch();

	virtual void addGeneBranch(const int geneIndex1,const int geneIndex2);

	/**
	 * Repair the genes by checking their integrity.
	 */
	virtual void repairGenes();

	/**
	 * Increases the number of branches to other genes of random genes.
	 * @param integrationProbability
	 * 							The probability of adding new branches.
	 */
	virtual void integrateRandomGenes(const double integrationProbability);

	/**
	 * Increases the number of branches to other genes of a random gene.
	 */
	virtual void integrateRandomGene();

	/**
	 * Increases the number of branches to other genes of a gene defined by the gene index in the mixed genome.
	 * @param geneIndex
	 * 				The gene index in the mixed genome.
	 */
	virtual void integrateGene(const int geneIndex);

	/**
	 * @brief Replaces random genes with other random genes.
	 * @param replacementProbability
	 * 							The probability of replacing genes.
	 */
	virtual void replaceRandomGenesWithRandomGenes(
	const double replacementProbability);

	/**
	 * Replaces a random gene with another random gene.
	 */
	virtual void replaceRandomGeneWithRandomGene();

	/**
	 * @brief		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original.
	 * @details		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original.
	 * The new segment specification is not an exact copy of the original, but contains adjustments meant to preserve self-loops in the branching pattern of the body tree.
	 * A self-loop arises when branch specifications dictate that segments of a particular type should have child segments of the same type. The segment copying mutation preserves this direct recursion in the tree structure when copying a segment specification from one index in the segment specification vector to another.
	 */
	virtual void replaceGeneWith(const int geneIndex,
	const int replacementIndex);

	/**
	 * Duplicate random genes with probability.
	 * @param duplicateProbability
	 * 							The probability of one gene to be duplicated.
	 */
	virtual void duplicateRandomGenes(const double duplicateProbability);

	/**
	 * Duplicates a random gene.
	 */
	virtual void duplicateRandomGene();

	/**
	 * Duplicate the gene with index.
	 * @param geneIndex
	 * 				The index of the gene to be duplicated.
	 */
	virtual void duplicateGene(const int geneIndex);

	/**
	 * Splits random genes with probability.
	 * @param splitProbability
	 * 						The probability to split a gene.
	 */
	virtual void splitRandomGenes(const double splitProbability);

	/**
	 * Split a random gene into two of summated equal size.
	 */
	virtual void splitRandomGene();

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
	virtual void splitGene(const int geneIndex, const SplitAxis axis);

	/**
	 * Grow random stubs in the genome with probability.
	 * @param growProbability
	 * 					The probability of a gene to be grown.
	 */
	virtual void growRandomStubs(const double growProbability);

	/**
	 * Grow a random stub.
	 */
	virtual void growRandomStub();

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
	virtual void growStub(const int geneIndex, const int branchiness);

	/**
	 * Mutate random genes with probability.
	 * @param mutationProbability
	 * 							The probability to mutate a gene.
	 */
	virtual void mutateRandomGenes(const double mutationProbability);

	/**
	 * Mutate a random gene.
	 */
	virtual void mutateRandomGene();

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
	virtual void mutateGene(const int geneIndex);

	/**
	 * Mutate random branches with probability.
	 * @param mutationProbability
	 * 							The probability to mutate a branch.
	 */
	virtual void mutateRandomBranches(const double mutationProbability);

	/**
	 * Mutate a random branch of a random gene.
	 */
	virtual void mutateRandomBranch();

	/**
	 * Mutate a random branch of a certain gene.
	 * @param geneIndex
	 * 					The gene index of which a random branch should be mutated.
	 */
	virtual void mutateRandomBranchOfGene(const int geneIndex);

	/**
	 * Mutate a certain branch of a certain gene.
	 * @param geneIndex
	 * 					The gene index of which a branch should be mutated.
	 * @param branchIndex
	 * 					The branch index of the branch to be mutated.
	 */
	virtual void mutateBranch(const int geneIndex, const int branchIndex);

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
	virtual void crossoverRandomly(Genome* const fatherGenome);

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
	const int fatherSegmentStartIndex, const int fatherSegmentEndIndex);

	/**
	 * @brief Grafts a random feature from the donor over to this genome.
	 * @param donor The donor of the feature.
	 */
	virtual void graftRandomlyFrom(Genome* const donor);

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
	const int geneIndex, const int geneQty);

	//Accessor methods

	int getSegmentsDepthLimit() const {
		return mSegmentsDepthLimit;
	}

	void setSegmentsDepthLimit(const int segmentsDepthLimit) {
		mSegmentsDepthLimit = segmentsDepthLimit;
	}

	int getTotalSegmentQtyLimit() const {
		return mTotalSegmentQtyLimit;
	}

	void setTotalSegmentQtyLimit(const int totalSegmentQtyLimit) {
		mTotalSegmentQtyLimit = totalSegmentQtyLimit;
	}

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

	friend std::ostream & operator<<(std::ostream &os,
	const MixedGenome &genome) {
		os << "MixedGenome: Type=" << genome.mGenomeType /**!< The type of genome*/

		<< "/length=" << genome.mLength /**!< The length of the genome*/

		<< "/Genes=["; /**!< The vector of genes.*/
		for (std::vector<Gene*>::const_iterator it = genome.mGenes.begin();
		it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "||";
		}

		os << "]";

		os << "/TotalSegmentQtyLimit=" << genome.mTotalSegmentQtyLimit /**!< The total segment quantity limit*/

		<< "/SegmentsDepthLimit=" << genome.mTotalSegmentQtyLimit; /**!< The segments depth limit*/
		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(IndirectGenome) /**!< Serialize the base object */

		& BOOST_SERIALIZATION_NVP(mTotalSegmentQtyLimit) /**!< The total segment quantity limit*/

		& BOOST_SERIALIZATION_NVP(mSegmentsDepthLimit); /**!< The segments depth limit*/
	}

private:
	int mTotalSegmentQtyLimit; /**!< A hard limit on the total number of body segments allowed.*/

	int mSegmentsDepthLimit; /**!< A bound on the depth of the body's tree structure (the number of segments along any root-to-leaf path).*/

};
BOOST_CLASS_VERSION(MixedGenome, 1)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_MIXEDGENOME_HPP_ */
