/*
 * NeuroExp.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROEXP_H_
#define NEUROEXP_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroExp: public NeuronTransferFunction {
public:
	NeuroExp();
	virtual ~NeuroExp();
};

#endif /* NEUROEXP_H_ */
