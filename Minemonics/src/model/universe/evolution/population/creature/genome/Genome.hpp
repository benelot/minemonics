/*
 * Genome.h
 *
 *  Created on: Apr 27, 2015
 *      Author: leviathan
 */

#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Genome {
public:
	Genome();
	virtual ~Genome();

	// variational genetics
	//# mutations
	void integrateRandomGene();

	void integrateGene();

	void duplicateRandomGene();

	void duplicateGene();

	void splitRandomGene();

	void splitGene();

	void growRandomStub();

	void growStub();

	void mutateRandomGene();

	void mutateGene();

	void mutateRandomBranch();

	void mutateBranch();

	//# crossover

	void crossover();

	/**
	 * Grafting copies a feature of the donator over to the receiver beginning
	 * at the indicated gene by copying the gene and its directed subgraph over,
	 * by following the links up to the maximum link depth and by copying all
	 * the genes that are met on the way. Then the newly added feature is
	 * connected randomly to the other genes to integrate it.
	 *
	 * @param receiver
	 *            receives the new feature donated by the donator
	 * @param donator
	 *            donates the new feature
	 * @param maxLinkDepth
	 *            the maximum link depth to follow
	 * @return returns the receiver genotype with the new feature added.
	 */
	void graft();

private:
	int mLength;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_GENOME_GENOME_HPP_ */
