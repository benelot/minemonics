#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/genome/Gene.hpp>

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

	Genome(GenomeType type);
	virtual ~Genome();

	/**
	 * Add a gene to the genome.
	 * @param gene The gene to add to the genome.
	 */
	void addGene(Gene* gene);

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

	virtual void addRandomGenes(double percentage) = 0;

	/**
	 *  Add a new, randomly generated gene to the genome.
	 */
	virtual void addRandomGene() = 0;

	virtual void repairGenes() = 0;

	virtual void integrateRandomGenes(double percentage) = 0;

	virtual void integrateRandomGene() = 0;

	virtual void integrateGene(int geneIndex) = 0;

	virtual void replaceRandomGenesWithRandomGenes(double percentage) = 0;

	virtual void replaceRandomGeneWithRandomGene() = 0;

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
	 *	copy all real-valued parameters from SS to self
	 *	copy all integer-valued parameters from SS to self
	 *	copy all Boolean-valued parameters from SS to self
	 *	copy desired joint angle GP tree from SS to self
	 *	copy max servo torque GP tree from SS to self
	 *	copy output GP tree from SS to self
	 *	copy state GP tree from SS to self vector vector
	 * // Source segment self-referencing branches should become
	 * // destination segment self-referencing branches
	 * for b = 1 to max_branches do
	 *	if segment type index of branch b of SS = s then
	 *		set segment type index of branch b to d in self
	 *
	 * A self-loop arises when branch specifications dictate that segments of a particular type should have child segments of the same type. The segment copying mutation preserves this direct recursion in the tree structure when copying a segment specification from one index in the segment specification vector to another.
	 */
	virtual void replaceGeneWith(int geneIndex, int replacementIndex) = 0;

	virtual void duplicateRandomGenes(double percentage) = 0;

	virtual void duplicateRandomGene() = 0;

	virtual void duplicateGene(int geneIndex) = 0;

	virtual void splitRandomGenes(double percentage) = 0;

	virtual void splitRandomGene() = 0;

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
	 * copy GP trees from ss[stos] to ss[ovw]
	 *
	 *set servo angle GP tree of ss[ovw] to a tree that outputs zero
	 *clear enabled flag in all branch specifications of ss[ovw]
	 *copy specifications of all enabled branches in ss[stos] to ss[ovw]
	 *clear enabled flag in all branch specifications of ss[stos]
	 *set type of first branch specification in ss[stos] to ovw
	 *set enabled flag in first branch specification of ss[stos]
	 *
	 * // Branch position offset 0,0,1 is the middle
	 * // of face opposite the joint anchor point
	 *set the x,y,z position offsets of the branch to 0,0,1
	 *
	 * // Angular offset zero keeps the branch parallel to the parent
	 *set the z-axis and y-axis angular offsets of the branch to zero set the type to follow repeats to ovw
	 *clear the branch mirror flag
	 *
	 * // Joint anchor offsets of zero place the
	 * // joint anchor in the centre of the face
	 *set joint anchor offsets of ss[ovw] to zero
	 *copy all other parameters from ss[stos] to ss[ovw]
	 *copy sine wave generator parameters from ss[stos] to ss[ovw]
	 *set scaling factor of ss[stos] to 1.0
	 *
	 *
	 *The effect of the segment splitting mutation method is to keep the creature morphology more or less the same, though this is by no means always the outcome, while splitting all segments of the chosen type into segments of half the original length. The split occurs half of the way along the segments' local z-axes, between the face upon which they have a joint anchor point joining them to their parent segments, and the opposite face
	 */
	virtual void splitGene(int geneIndex) = 0;

	virtual void growRandomStubs(double percentage) = 0;

	virtual void growRandomStub() = 0;

	/**
	 * @brief		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches.
	 * @details		The 'stub' growing mutation method causes a segment to sprout a new branch which itself has no branches. Many mutations that result in new branches often produced large
	 complicated structures that, should they appear on a creature already fairly evolved, are almost always extremely detrimental. This mutation was created as a means of providing a more subtle mutation that adds complexity to a creature's morphology with what is intended to be a reduced impact on fitness. The method proceeds as follows.
	 * // Input:int i
	 * //i is the index of the segment specificationto be mutated
	 * // Let:ss[] be the vectorof segment specifications
	 *
	 * //stub-growth(i)
	 * // A segment specification other than i will also be modifiedin
	 * //this mutation, j is its index and is chosen uniformlyat
	 * // random
	 * int j = a randomly chosen segment index other than i
	 * // Since ss[j] we be a ´stub' its max repeats will be set to one.
	 * // Since no segments should followthe repeats, the type to
	 * // to followrepeats will be set to itself
	 *
	 * max repeats for ss[j] = 1
	 * type to follow repeats for ss[j] = j
	 *
	 * // Disable all branches extendingfrom segments of type j
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
	virtual void growStub(int geneIndex,int branchiness) = 0;

	virtual void mutateRandomGenes(double percentage) = 0;

	/**
	 * @brief		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * @details		The segment randomization mutation simply deletes a segment specification and replaces it with a randomly-generated one.
	 * The new segment specification is created by calling a segment specification constructor and passing it a bushiness parameter between 0.1 and 0.9, chosen uniformly at random. The bushiness parameter is used directly as the probability probability that any given branch specification in the segment specification will have its enable flag set to true instead of false. A high bushiness parameter is more likely to produce a segment with many branches.
	 *				The random segment specification constructor is shown by the following pseudocode:
	 *
	 *	// Input: EvolutionSettings s, real b
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
	 * 	scaling factor = 1.0 + rand(-l.0,+l.0) *  scale_varlability
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
	 * 		// to b, the bumpiness parameter passed to the constructor
	 * 		// and is set to false the rest of the time
	 * 		branch bs's enable flag = true or false
	 *
	 * 	// The following two values are parameters of the segment
	 * 	// specification's sine wave generator
	 * 	start value = a random value between 0.0 and 2*pi
	 * 	scale = a random value between -/+max_wave_scale (fixed at 10)
	 * 	angle, torque, output, and state GP trees are generated as described below B.6.2.5.
	 */
	virtual void mutateRandomGene() = 0;

	virtual void mutateGene(int geneIndex) = 0;

	virtual void mutateRandomBranches(double percentage) = 0;

	virtual void mutateRandomBranchOfGene(int geneIndex) = 0;

	virtual void mutateRandomBranch() = 0;

	/**
	 * Mutate random branches.
	 * @param geneIndex
	 * @param branchIndex
	 */
	virtual void mutateBranch(int geneIndex, int branchIndex) = 0;

	/**
	 * # Crossover
	 * -----------
	 * Crossover includes every change in genome involving more than one genome.
	 */

	/**
		 * Crossover randomly with father genome.
		 * @param fatherGenome
		 */
		virtual void crossoverRandomly(Genome* fatherGenome) = 0;


	/**
	 * Crossover with other genome starting after fatherSegmentIndex copying over starting from motherSegmentIndex.
	 * @param fatherGenome
	 * @param motherStartSegmentIndex
	 * @param motherEndSegmentIndex
	 * @param fatherStartSegmentIndex
	 * @param fatherEndSegmentIndex
	 */
	virtual void crossover(Genome* fathergenome,
			int motherSegmentStartIndex, int motherSegmentEndIndex,
			int fatherSegmentStartIndex, int fatherSegmentEndIndex) = 0;

	/**
	 * Grafting copies a feature of the donator over to the receiver beginning
	 * at the indicated gene by copying the gene and its directed subgraph over,
	 * by following the links up to the maximum link depth and by copying all
	 * the genes that are met on the way. Then the newly added feature is
	 * connected randomly to the other genes to integrate it.
	 *
	 * @param donator
	 *            donates the new feature
	 * @param maxLinkDepth
	 *            the maximum link depth to follow
	 */
	virtual void graftFrom(Genome* donator, int maxLinkDepth) = 0;

	std::vector<Gene*>& getGenes() {
		return mGenes;
	}

	const std::vector<Gene*>& getConstGenes() const {
		return mGenes;
	}

	GenomeType getGenomeType() const {
		return mGenomeType;
	}

	int getLength() const {
		return mLength;
	}

protected:
	int mLength;

	std::vector<Gene*> mGenes;

	GenomeType mGenomeType;

	double mBranchiness;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_ */
