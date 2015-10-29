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
#include <utils/logging/Logger.hpp>

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
	void initialize(const double reapPercentage,
		const double crossOverPercentage, const double geneMutationPercentage,
		const double geneSplitPercentage, const double branchMutationPercentage,
		const double growStubPercentage, const double graftPercentage,
		const double sowFreshPercentage);

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
	void mutateGenes(PopulationModel* const population, const int startIndex,
		const int mutatedGeneHeads);

	/**
	 * Mutate creatures in the population and add n mutateGeneHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneHeads Number of mutatedGeneHeads to add.
	 */
	void splitGenes(PopulationModel* const population, const int startIndex,
		const int splitGeneHeads);

	/**
	 * Mutate creatures in the population and add n mutateGeneHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneHeads Number of mutatedGeneHeads to add.
	 */
	void mutateGeneBranches(PopulationModel* const population, const int startIndex,
		const int mutatedGeneBranchHeads);

	/**
	 * Mutate creatures in the population and add n mutateGeneHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneHeads Number of mutatedGeneHeads to add.
	 */
	void growStubs(PopulationModel* const population, const int startIndex,
		const int growStubHeads);

	/**
	 * Mutate creatures in the population and add n mutateGeneHeads.
	 * @param population The population to mutate.
	 * @param mutatedGeneHeads Number of mutatedGeneHeads to add.
	 */
	void graftFeatures(PopulationModel* const population, const int startIndex,
		const int graftedHeads);


	/**
	 * Sow fresh heads in the population.
	 * @param population The population to sow.
	 * @param sowFreshlyHeads Numbe of heads to sow.
	 */
	void sowFreshly(PopulationModel* const population,
		const int sowFreshlyHeads);

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string > ("Reaper"));
		}
	} _initializer;

	double mReapPercentage;
	double mCrossOverPercentage;
	double mGeneMutationPercentage;
	double mGeneSplitPercentage;
	double mBranchMutationPercentage;
	double mGrowStubPercentage;
	double mGraftPercentage;
	double mSowFreshPercentage;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_REAPER_H_ */
