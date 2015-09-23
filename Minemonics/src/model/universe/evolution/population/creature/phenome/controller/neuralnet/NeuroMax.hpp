/*
 * NeuroMax.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROMAX_H_
#define NEUROMAX_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroMax: public NeuronTransferFunction {
public:
	NeuroMax();
	virtual ~NeuroMax();
};

#endif /* NEUROMAX_H_ */
