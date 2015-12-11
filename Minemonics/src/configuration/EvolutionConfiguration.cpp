//# corresponding headers
#include <configuration/EvolutionConfiguration.hpp>

//# forward declarations
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
 * Number of elitists (the ones that get carried over to the next generation because they are so successful)
 */
const unsigned EvolutionConfiguration::EVOLUTION_SELECTION_ELITISTS_QTY = 1;

/**
 * This is the number of times that a creature will be evaluated during a fitness
 measurement. This value is set to one in all of the experimental
 setups described in this work although it can be set higher to reduce noise.
 The trade-off is one of noise reduction vs. computation time.
 */
const unsigned EvolutionConfiguration::EVOLUTION_EVALUATION_RUNS = 1;

/**
 * Whenever a parent is needed, this setting dictates the number of individuals to choose
 * at random from the previous generation. These individuals constitute a tournament.
 * The creature with the highest fitness wins and becomes the selected parent. The
 * higher this value is in relation to the population size, the higher the selection pressure
 * will be and the more rapid the loss of diversity will be.
 */
const unsigned EvolutionConfiguration::EVOLUTION_TOURNAMENT_SIZE = 10;

/**
 * This is the probability that a new creature, in any generation other than the first, will
 be produced by the crossing of two parents from the previous generation.
 */
const double EvolutionConfiguration::EVOLUTION_CREATURE_CROSSOVER_RATE = 0.1;

/**
 * This is the mutation rate used in mutation operators affecting the genome.
 */
const double EvolutionConfiguration::EVOLUTION_CREATURE_MUTATION_RATE = 0.1;

// Generation variables
/**
 * Ratios to which the reaper sows offspring as descendants from the best performing creatures.
 * The best performing creature takes part in <ratio> of all cross-overs etc.
 */
const double EvolutionConfiguration::REAPER_SOW_OFFSPRING[] = { 0.5, 0.25,
		0.125, 0.075, 0.075 }; // Initialization in EvolutionConfiguration.cpp

const double EvolutionConfiguration::REAPER_REAP_PERCENTAGE = 0.15f; /**!< First the reaper reaps off a percentage */

const double EvolutionConfiguration::REAPER_CROSSOVER_PERCENTAGE = 0.5f; /**!< Cross over percentage and sow fresh sum up to 1.0*/
const double EvolutionConfiguration::REAPER_SOW_FRESH_PERCENTAGE = 0.5f; /** !< How many creatures should be sown randomly. */

/** The percentage of the population to be affected. The following sum up to 1.0*/
const double EvolutionConfiguration::REAPER_GENE_MUTATION_PERCENTAGE = 0.2f;
const double EvolutionConfiguration::REAPER_GENE_SPLIT_PERCENTAGE = 0.2f;
const double EvolutionConfiguration::REAPER_LINK_MUTATION_PERCENTAGE = 0.2f;
const double EvolutionConfiguration::REAPER_GROW_STUB_PERCENTAGE = 0.2f;
const double EvolutionConfiguration::REAPER_GRAFT_PERCENTAGE = 0.2f;

/** The probability of genome to be affected. The following DO NOT sum up to 1.0*/
const double EvolutionConfiguration::REAPER_GENE_MUTATION_PROBABILITY = 0.2f;
const double EvolutionConfiguration::REAPER_LINK_MUTATION_PROBABILITY = 0.2f;
const double EvolutionConfiguration::REAPER_GENE_SPLIT_PROBABILITY = 0.1f;
const double EvolutionConfiguration::REAPER_GROW_STUB_PROBABILITY = 0.6f;
const int EvolutionConfiguration::REAPER_GROW_STUB_BRANCHINESS = 2;
const double EvolutionConfiguration::REAPER_GRAFT_PROPABILITY = 0.6f;

const Ogre::Vector3 EvolutionConfiguration::ROOT_POSITION = Ogre::Vector3(0, 50,
	30); /**!< The position where creatures are dropped */
