#ifndef MODEL_UNIVERSE_EVOLUTION_REAPER_H_
#define MODEL_UNIVERSE_EVOLUTION_REAPER_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/PopulationModel.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The reaper looks after the populations and keeps them fit by reaping not fit creatures and adding new ones.
 * @details		Before creatures are simulated for fitness evaluation, some simple
 * viability checks are performed, and inappropriate creatures are removed
 * from the population by giving them zero fitness values. Those that have
 * more than a specified number of parts are removed. A subset of genotypes
 * will generate creatures whose parts initially interpenetrate. A short
 * simulation with collision detection and response attempts to repel any
 * intersecting parts, but those creatures with persistent interpenetrations
 * are also discarded.
 *
 * @date		2014-12-19
 * @author		Benjamin Ellenberger
 */
class Reaper {
public:

	Reaper();
	virtual ~Reaper();

	/**
	 * Initialize the reaper.
	 * @param reapPercentage The percentage of the population that is culled.
	 * @param crossOverPercentage The percentage of the population that is replaced by cross over.
	 * @param geneMutationPercentage The percentage of the population whose genes are mutated.
	 * @param attributeMutationPercentage The percentage of the population whose gene attributes are mutated.
	 * @param branchMutationPercentage The percentage of the population whose branches are mutated.
	 * @param branchAttributeMutationPercentage The percentage of the population whose branch attributes are mutated.
	 * @param sowFreshPercentage The percentage of the population who is sown freshly.
	 */
	void initialize(double reapPercentage, double crossOverPercentage,
			double geneMutationPercentage, double geneAttributeMutationPercentage,
			double branchMutationPercentage, double branchAttributeMutationPercentage, double sowFreshPercentage);

	/**
	 * Reap the less fit creatures from the population.
	 * @param population The population that should be reaped from.
	 */
	void reap(PopulationModel* population);

	/**
	 * Sow new creatures into the population.
	 * @param population The population that should be sowed into.
	 */
	void sow(PopulationModel* population);

	void crossover(PopulationModel* population,int crossoverHeads);

	void mutateGenes(PopulationModel* population,int mutatedGeneHeads);

	void mutateGeneAttributes(PopulationModel* population,int mutatedGeneAttributeHeads);

	void mutateGeneBranches(PopulationModel* population,int mutatedGeneBranchHeads);

	void mutateGeneBranchAttributes(PopulationModel* population,int mutatedGeneBranchAttributeHeads);

	void sowFreshly(PopulationModel* population,int sowFreshlyHeads);

private:
	double mReapPercentage;
	double mCrossOverPercentage;
	double mGeneMutationPercentage;
	double mAttributeMutationPercentage;
	double mBranchMutationPercentage;
	double mBranchAttributeMutationPercentage;
	double mSowFreshPercentage;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_REAPER_H_ */
