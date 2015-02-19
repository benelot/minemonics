/*
 * NeuroSumThreshold.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSUMTHRESHOLD_H_
#define NEUROSUMTHRESHOLD_H_

#include "NeuronTransferFunction.h"

class NeuroSumThreshold: public NeuronTransferFunction {
public:
	NeuroSumThreshold();
	virtual ~NeuroSumThreshold();
};

#endif /* NEUROSUMTHRESHOLD_H_ */
