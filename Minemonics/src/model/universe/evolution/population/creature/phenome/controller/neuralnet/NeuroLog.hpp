/*
 * NeuroLog.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROLOG_H_
#define NEUROLOG_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroLog: public NeuronTransferFunction {
public:
	NeuroLog();
	virtual ~NeuroLog();
};

#endif /* NEUROLOG_H_ */
