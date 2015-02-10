/*
 * Gene.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef GENE_H_
#define GENE_H_

/**
 * A gene is part of the complete genome of a creature. It encodes for a certain
 * part of it, be it a certain body part, sensor type, an actuator or a neuronal
 * network connection.
 *
 * @author leviathan
 *
 */
#include <vector>
#include "GeneBranch.h"

class Gene {
public:
	Gene();
	virtual ~Gene();
	virtual void print();

	// genetic branches
	std::vector<GeneBranch> branches;
};

#endif /* GENE_H_ */
