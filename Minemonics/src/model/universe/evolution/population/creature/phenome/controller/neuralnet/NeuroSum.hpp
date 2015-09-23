/*
 * NeuroSum.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSUM_H_
#define NEUROSUM_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroSum: public NeuronTransferFunction {
public:
	NeuroSum();
	virtual ~NeuroSum();
};

#endif /* NEUROSUM_H_ */
