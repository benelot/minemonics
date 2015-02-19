/*
 * NeuroSigmoid.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSIGMOID_H_
#define NEUROSIGMOID_H_

#include "NeuronTransferFunction.h"

class NeuroSigmoid: public NeuronTransferFunction {
public:
	NeuroSigmoid();
	virtual ~NeuroSigmoid();
};

#endif /* NEUROSIGMOID_H_ */
