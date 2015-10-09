#ifndef MODEL_UNIVERSE_EVOLUTION_REAPER_H_
#define MODEL_UNIVERSE_EVOLUTION_REAPER_H_

//# corresponding header
//# forward declarations
class PopulationModel;
class CreatureModel;

//# system headers
//## controller headers
//## model headers
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
	void initialize(const double reapPercentage, const double crossOverPercentage,
			const double geneMutationPercentage,
			const double geneAttributeMutationPercentage,
			const double branchMutationPercentage,
			const double branchAttributeMutationPercentage,
			const double sowFreshPercentage);

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 * @return if the second creature's fitness is higher.
	 */
	static bool compareCreatureFitnessAsc(CreatureModel* const creature1, CreatureModel* const creature2);

	/**
	 * Comparator for the creature sort function
	 * @param creature1 First creature.
	 * @param creature2 Second creature.
	 * @return if the second creature's fitness is higher.
	 */
	static bool compareCreatureFitnessDsc(CreatureModel* const creature1, CreatureModel* const creature2);


	/**
	 * Reap the less fit creatures from the population.
	 * @param population The population that should be reaped from.
	 */
	void reap(PopulationModel* const population);

	/**
	 * Sow new creatures into the population.
	 * @param population The population that should be sowed into.
	 */
	void sow(PopulationModel* const population);

	/**
	 * Crossover creatures in the population and add n crossoverHeads.
	 * @param population The population to crossover.
	 * @param crossoverHeads Number of crossoverHeads to add.
	 */
	void crossover(PopulationModel* const population, const int crossoverHeads);

	/**
	 * Mutate creatures in the population and add n mutateGeneHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneHeads Number of mutatedGeneHeads to add.
	 */
	void mutateGenes(PopulationModel* const population,const int mutatedGeneHeads);

	/**
	 * Mutate gene attributes in the population and add n mutatedGeneBranchHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneAttributeHeads Number of mutatedGeneBranchHeands to add.
	 */
	void mutateGeneAttributes(PopulationModel* const population,
			const int mutatedGeneAttributeHeads);

	/**
	 * Mutate gene branch in the population and add n mutatedGeneBranchAttributeHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneBranchHeads Number of mutatedGeneBranchAttributeHeads to add.
	 */
	void mutateGeneBranches(PopulationModel* const population,
			const int mutatedGeneBranchHeads);

	/**
	 * Mutate gene branch attributes in the population and add n mutatedGeneBranchAttributeHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneBranchAttributeHeads Number of mutatedGeneBranchAttributeHeads to add.
	 */
	void mutateGeneBranchAttributes(PopulationModel* const population,
			const int mutatedGeneBranchAttributeHeads);

	/**
	 * Sow fresh heads in the population.
	 * @param population The population to sow.
	 * @param sowFreshlyHeads Numbe of heads to sow.
	 */
	void sowFreshly(PopulationModel* const population, const int sowFreshlyHeads);

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
