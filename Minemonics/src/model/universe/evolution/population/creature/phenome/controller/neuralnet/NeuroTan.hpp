/*
 * NeuroTan.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROTAN_H_
#define NEUROTAN_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroTan: public NeuronTransferFunction {
public:
	NeuroTan();
	virtual ~NeuroTan();
};

#endif /* NEUROTAN_H_ */
