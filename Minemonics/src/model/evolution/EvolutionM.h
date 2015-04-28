/*
 * Evolution.h
 *
 *  Created on: Mar 8, 2015
 *      Author: leviathan
 *
 *      According to Lee Graham Thesis
 *
 *      A particular experimental setup is referred to as an "evolution".
 *      Evolutions consist of one or more independent GA runs, where each
 *      run is identical in terms of settings like population size,
 *      tournament size, mutation rates, and so on.
 *
 *      All creatures in the first generation of any run are produced from randomly-initialized genomes.
 *      Creatures in generations other than the first are produced either by mutation or
 *      crossover of parents selected by tournament from the previous generation. The sole
 *      exception is the first creature in such generations, which is always a copy of the best (or
 *      elite) creature from the previous generation.
 */

#ifndef MODEL_EVOLUTION_EVOLUTIONM_H_
#define MODEL_EVOLUTION_EVOLUTIONM_H_

//# corresponding header
//# forward declarations
class Creature;
class Environment;

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <model/evolution/Reaper.h>
#include <model/evolution/population/Population.h>

//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class EvolutionM {
public:
	EvolutionM();
	~EvolutionM();

	void proceed();

	//accessor methods
	const Reaper& getReaper() const {
		return mReaper;
	}

	void setReaper(const Reaper& reaper) {
		mReaper = reaper;
	}

private:
	Reaper mReaper;

	std::vector<Population> populations;

	// Evolution states
	enum EvolutionState
	{
		EVALUATION, GENERATION, PROCESSING
	};

	EvolutionState state;
};

#endif /* MODEL_EVOLUTION_EVOLUTIONM_H_ */
