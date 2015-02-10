/*
 * Genome.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "Genome.h"
/*
 * The genetic representation of this morphology is a directed graph of
 * nodes and connections. Each graph contains the developmental instructions
 * for growing a creature, and provides a way of reusing instructions to
 * make similar or recursive components within the creature. A phenotype
 * hierarchy of parts is made from a graph by starting at a defined
 * root-node and synthesizing parts from the node information while tracing
 * through the connections of the graph. The graph can be recurrent. Nodes
 * can connect to themselves or in cycles to form recursive or fractal like
 * structures. They can also connect to the same child multiple times to
 * make duplicate instances of the same appendage.
 */
Genome::Genome() {
	// TODO Auto-generated constructor stub

}

Genome::~Genome() {
	// TODO Auto-generated destructor stub
}

