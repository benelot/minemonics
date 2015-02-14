/*
 * Genome.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENOME_H_
#define GENOME_H_

#include <vector>
#include "Gene.h"

class Genome {
public:
	Genome();
	virtual ~Genome();

	std::vector<Gene> genes;

};

#endif /* GENOME_H_ */
