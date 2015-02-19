/*
 * NeuroMemory.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROMEMORY_H_
#define NEUROMEMORY_H_

#include "NeuronTransferFunction.h"

class NeuroMemory: public NeuronTransferFunction {
public:
	NeuroMemory();
	virtual ~NeuroMemory();
};

#endif /* NEUROMEMORY_H_ */
