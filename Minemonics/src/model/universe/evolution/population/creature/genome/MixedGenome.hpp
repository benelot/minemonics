#ifndef GENOME_H_
#define GENOME_H_

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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/IndirectGenome.hpp>
#include <model/universe/evolution/population/creature/genome/morphology/Morphogene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The mixed genome is an genome type that encodes the morphology and the neural network in a compact/indirect encoding.
 * @details		 A creature's genotype dictates a potentially-recursive (both indirectly and directly recursive)
 * branching pattern. The genome encodes properties for a fixed number of segment types, and associated
 * with each type is a fixed number of branch specifications that dictate the way in which a segment of
 * a given type sprouts branches of other segment types. The encoded information also specifies the scaling,
 * positioning, and other aspects of the branching.
 *  * The genetic representation of this morphology is a directed graph of
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
	virtual ~MixedGenome();

	void createRandomGenome(double branchiness);

	bool equals(const MixedGenome & genome) const;

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the genome to a string.
	 * @param os The ostream.
	 * @param genome The genome we want to serialize.
	 * @return A string containing all information about the genome.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const MixedGenome &genome) {
		std::vector<Gene*>::const_iterator it;
		for (it = genome.mGenes.begin(); it != genome.mGenes.end(); it++) {
			os << (**it);
			os << "//";
		}
		return os;
	}

	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
				& BOOST_SERIALIZATION_NVP(
						mGenes) & BOOST_SERIALIZATION_NVP(mTotalSegmentQtyLimit) & BOOST_SERIALIZATION_NVP(mSegmentsDepthLimit);
	}

	int getSegmentsDepthLimit() const {
		return mSegmentsDepthLimit;
	}

	void setSegmentsDepthLimit(int segmentsDepthLimit) {
		mSegmentsDepthLimit = segmentsDepthLimit;
	}

	int getTotalSegmentQtyLimit() const {
		return mTotalSegmentQtyLimit;
	}

	void setTotalSegmentQtyLimit(int totalSegmentQtyLimit) {
		mTotalSegmentQtyLimit = totalSegmentQtyLimit;
	}

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

	virtual void addRandomGenes(double percentage);

	/**
	 * Add a new, randomly generated gene to the genome.
	 */
	virtual void addRandomGene();

	virtual void repairGenes();

	virtual void integrateRandomGenes(double percentage);

	virtual void integrateRandomGene();

	virtual void integrateGene(int geneIndex);

	virtual void replaceRandomGenesWithRandomGenes(double percentage);

	virtual void replaceRandomGeneWithRandomGene();

	/**
	 * @brief		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original.
	 * @details		The segment copying mutation replaces the entire segment specification entry in the vector with a copy of another chosen uniformly at random from the vector, but excluding the original. The new segment specification is not an exact copy of the original, but contains adjustments meant to preserve self-loops in the branching pattern of the body tree. This mutation is represented by the following pseudocode:
	 *
	 * // Inputs: SegmentSpec SS, int d, int s
	 * // SS is the segment specification to be copied
	 * //d is the destination index in the specification
	 * //s is the source index (of SS) in the specification
	 * // The destination specification is the self object whose
	 * // become_special_copy() member is called
	 * // become_special_copy (SS, d, s)
	 *	copy all parameters from SS to self
	 * // Source segment self-referencing branches should become
	 * // destination segment self-referencing branches
	 * for b = 1 to max_branches do
	 *	if segment type index of branch b of SS = s then
	 *		set segment type index of branch b to d in self
	 *
	 * A self-loop arises when branch specifications dictate that segments of a particular type should have child segments of the same type. The segment copying mutation preserves this direct recursion in the tree structure when copying a segment specification from one index in the segment specification vector to another.
	 */
	virtual void replaceGeneWith(int geneIndex, int replacementIndex);

	virtual void duplicateRandomGenes(double percentage);

	virtual void duplicateRandomGene();

	virtual void duplicateGene(int geneIndex);

	virtual void splitRandomGenes(double percentage);

	virtual void splitRandomGene();

	/**
	 * @brief		The segment splitting mutation method is meant be a conservative means of increasing body complexity. It attempts to replace all segments of a chosen type in the body with two segments connected by a joint but together occupying roughly the same space in the body as the segments they replace.
	 * @details		The segment splitting mutation method is meant be a conservative means of increasing body complexity. It attempts to replace all segments of a chosen type in the body with two segments connected by a joint but together occupying roughly the same space in the body as the segments they replace. The mutation proceeds according to the following pseudocode.
	 *
	 * // Input: int stos
	 * // Let:  stos is the index of the segment to be split
	 * ss[] be the vector of segment specifications
	 * // min_dim be the minimum allowable cuboid dimension length
	 * //segment-split(stos)
	 * // Halve the z dimension
	 * int halfz = max(ss[stos].z,min_dim)
	 * ss[stos].z = halfz
	 * ss[ovw].z = halfz
	 *
	 * clear enabled flag in all branch specifications of ss[ovw]
	 * copy specifications of all enabled branches in ss[stos] to ss[ovw]
	 * clear enabled flag in all branch specifications of ss[stos]
	 * set type of first branch specification in ss[stos] to ovw
	 * set enabled flag in first branch specification of ss[stos]
	 *
	 * // Branch position offset 0,0,1 is the middle
	 * // of face opposite the joint anchor point
	 * set the x,y,z position offsets of the branch to 0,0,1
	 *
	 * // Angular offset zero keeps the branch parallel to the parent
	 * set the z-axis and y-axis angular offsets of the branch to zero set the type to follow repeats to ovw
	 * clear the branch mirror flag
	 *
	 * // Joint anchor offsets of zero place the
	 * // joint anchor in the centre of the face
	 * set joint anchor offsets of ss[ovw] to zero
	 * copy all other parameters from ss[stos] to ss[ovw]
	 * copy sine wave generator parameters from ss[stos] to ss[ovw]
	 * set scaling factor of ss[stos] to 1.0
	 *
	 *
	 * The effect of the segment splitting mutation method is to keep the creature morphology more or less
	 * the same, though this is by no means always the outcome, while splitting all segments of the chosen
	 * type into segments of half the original length. The split occurs half of the way along the segments'
	 * local z-axes, between the face upon which they have a joint anchor point joining them to their parent
	 *  segments, and the opposite face.
	 */
	virtual void splitGene(int geneIndex, SplitAxis axis);

	virtual void growRandomStubs(double percentage);

	virtual void growRandomStub();

	/**
	 * @brief		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches.
	 * @details		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches. Many mutations that result in new branches often produced large
	 complicated structures that, should they appear on a creature already fairly evolved, are almost always extremely detrimental. This mutation was created as a means of providing a more subtle mutation that adds complexity to a creature's morphology with what is intended to be a reduced impact on fitness. The method proceeds as follows.
	 * // Input:int i
	 * //i is the index of the segment specification to be mutated
	 * // Let:ss[] be the vector of segment specifications
	 *
	 * //stub-growth(i)
	 * // A segment specification other than i will also be modified in
	 * //this mutation, j is its index and is chosen uniformly at
	 * // random
	 * int j = a randomly chosen segment index other than i
	 * // Since ss[j] we be a ´stub' its max repeats will be set to one.
	 * // Since no segments should follow the repeats, the type to
	 * // to follow repeats will be set to itself
	 *
	 * max repeats for ss[j] = 1
	 * type to follow repeats for ss[j] = j
	 *
	 * // Disable all branches extending from segments of type j
	 * for bs = 1 to the number of branch specifications(5) do
	 * 	clearthe enable flagof ss[j]'sbranch specification #bs
	 * // Pick a branch index in ss[i] to pointto ss[j](uniform random)
	 * int k = a number from 1 to the number of branch specifications(5)
	 *
	 * // Connect segment j as a branch from segment i and enable it
	 * set the type of ss[i]'s branch #k to j
	 * set the enable flag of ss[i]'s branch #k
	 * // The 'stub' should only be a single branch, not a mirrored pair
	 * clear the mirror flag of ss[i]'s branch #k
	 *
	 * The check for the 'stub' growing mutation is the final step in mutating a creature's segment specifications.
	 */
	virtual void growStub(int geneIndex, int branchiness);

	virtual void mutateRandomGenes(double percentage);

	/**
	 * @brief		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * @details		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * The new segment specification is created by calling a segment specification constructor and passing it a bushiness parameter between 0.1 and 0.9, chosen uniformly at random. The bushiness parameter is used directly as the probability probability that any given branch specification in the segment specification will have its enable flag set to true instead of false. A high bushiness parameter is more likely to produce a segment with many branches.
	 *				The random segment specification constructor is shown by the following pseudocode:
	 *
	 * // Input: EvolutionSettings s, real b
	 * // s is an object containing important evolution parameters
	 * // b is the bushiness parameter
	 * // Let: biased_log(i,j) be a function which generates two
	 * // values, lO^m and 10"n, both between i and j with
	 * // exponents m and n chosen uniformly at random from the
	 * // range [loglO(i)..loglO(j)], and returning whichever
	 * // of the two values is closer to j .
	 * // rand(i,j) be a function that returns a value chosen
	 * // uniformly at random in the range [i..j]
	 * //

	 * SegmentSpecification(s,b)
	 * 	// Choose the dimensions of the segment,
	 * 	// with a bias toward larger dimensions
	 * 	x = biased_log(min_cuboid_dimension,max_cuboid_dimension)
	 * 	y = biased_log(min_cuboid_dimension,max_cuboid_dimension)
	 * 	z = biased_log(min_cuboid_dimension,max_cuboid_dimension)
	 * 	// scale_variability is a fixed constant (0.5)
	 *
	 * 	scaling factor = 1.0 + rand(-l.0,+l.0) *  scale_variability
	 * 	 joint anchor offset x = rand(-1.0,+l.0)
	 * 	joint anchor offset y = rand(-1. 0,+1.0)
	 * 	colour = colour chosen uniformly at random from available colours
	 * 	max repeats = a number chosen uniformly at random between zero and a fixed constant (12)
	 * 	type to follow repeats = a segment specification index chosen uniformly at random between one and s.num__seg_specs
	 * 	for bs = 1 to the number of branch specifications (5) do
	 * 		// The following values are chosen uniformly at random
	 * 		branch bs's z-axis angular offset = an int between 0 and 359
	 * 		branch bs's y-axis angular offset = a real between -/+15.0
	 * 		branch bs's type = an int between 1 and s.num__seg_specs
	 * 		branch bs's position offsets (x,y,z) = -1, 0, or +1
	 * 		illegal branch position offsets (0,0,0) are repaired as per the method described above
	 * 		 branch bs's mirror and flip flags = true or false
	 *
	 * 		// The enable flag is set to true with a probability equal
	 * 		// to b, the bumpyness parameter passed to the constructor
	 * 		// and is set to false the rest of the time
	 * 		branch bs's enable flag = true or false
	 *
	 * 	// The following two values are parameters of the segment
	 * 	// specification's sine wave generator
	 * 	start value = a random value between 0.0 and 2*pi
	 * 	scale = a random value between -/+max_wave_scale (fixed at 10)
	 */
	virtual void mutateRandomGene();

	virtual void mutateGene(int geneIndex);

	virtual void mutateRandomBranches(double percentage);

	virtual void mutateRandomBranchOfGene(int geneIndex);

	virtual void mutateRandomBranch();

	/**
	 * Mutate random branches.
	 * @param geneIndex
	 * @param branchIndex
	 */
	virtual void mutateBranch(int geneIndex, int branchIndex);

	/**
	 * # Crossover
	 * -----------
	 * Crossover includes every change in genome involving more than one genome.
	 */

	/**
	 * Crossover randomly with father genome.
	 * @param fatherGenome
	 */
	virtual void crossoverRandomly(Genome* fatherGenome);

	/**
	 * Crossover with other genome starting after fatherSegmentIndex copying over starting from motherSegmentIndex.
	 * @param fatherGenome
	 * @param motherStartSegmentIndex
	 * @param motherEndSegmentIndex
	 * @param fatherStartSegmentIndex
	 * @param fatherEndSegmentIndex
	 */
	virtual void crossover(Genome* fathergenome, int motherSegmentStartIndex,
			int motherSegmentEndIndex, int fatherSegmentStartIndex,
			int fatherSegmentEndIndex);

	virtual void graftRandomlyFrom(Genome* donator);

	/**
		 * Grafting copies a feature of the donor over to the receiver beginning
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
	virtual void graftFrom(Genome* donor, int attachmentIndex, int geneIndex,
			int geneQty);

private:

	/**
	 * A hard limit on the total number of body segments allowed.
	 */
	int mTotalSegmentQtyLimit;

	/**
	 * A bound on the depth of the body's tree structure (the number of segments along any root-to-leaf path).
	 * This bound is iteratively adjusted until both it and the segment quantity limit are satisfied.
	 * First, the creature is instantiated using the depth bound provided
	 * in the evolution configuration. If, during that process, the total number of body
	 * segments exceeds the segment count limit, the body is deleted, the depth bound is
	 * decreased, and the body is constructed again. This process will repeat, decreasing the
	 * depth bound each time, until the segment count falls within the specific limit.
	 */
	int mSegmentsDepthLimit;

};
BOOST_CLASS_VERSION(MixedGenome, 1)

#endif /* GENOME_H_ */
