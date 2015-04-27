
#ifndef REAPER_H_
#define REAPER_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <model/evolution/population/Population.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * Reaper.h
 *
 * @brief		The reaper looks after the populations and keeps them fit by reaping not fit creatures and adding new ones.
 *
 * @details		Before creatures are simulated for fitness evaluation, some simple
 * viability checks are performed, and inappropriate creatures are removed
 * from the population by giving them zero fitness values. Those that have
 * more than a specified number of parts are removed. A subset of genotypes
 * will generate creatures whose parts initially interpenetrate. A short
 * simulation with collision detection and response attempts to repel any
 * intersecting parts, but those creatures with persistent interpenetrations
 * are also discarded.
 *
 *  @date		Dec 19, 2014
 *  @author		leviathan
 */
class Reaper {
public:

	Reaper();
	virtual ~Reaper();

	/**
	 * Reap the less fit creatures from the population.
	 * @param population The population that should be reaped from.
	 */
	void reap(Population population);

	/**
	 * Sow new creatures into the population.
	 * @param population The population that should be sowed into.
	 */
	void sow(Population population);
};

#endif /* REAPER_H_ */
