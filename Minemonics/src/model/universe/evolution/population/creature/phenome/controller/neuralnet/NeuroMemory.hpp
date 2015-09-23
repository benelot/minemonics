/*
 * NeuroMemory.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROMEMORY_H_
#define NEUROMEMORY_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroMemory: public NeuronTransferFunction {
public:
	NeuroMemory();
	virtual ~NeuroMemory();
};

#endif /* NEUROMEMORY_H_ */
