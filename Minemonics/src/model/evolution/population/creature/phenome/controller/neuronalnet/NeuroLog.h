/*
 * NeuroLog.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROLOG_H_
#define NEUROLOG_H_

#include "NeuronTransferFunction.h"

class NeuroLog: public NeuronTransferFunction {
public:
	NeuroLog();
	virtual ~NeuroLog();
};

#endif /* NEUROLOG_H_ */
