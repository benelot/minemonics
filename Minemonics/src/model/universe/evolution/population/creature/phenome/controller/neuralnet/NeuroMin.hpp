/*
 * NeuroMin.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROMIN_H_
#define NEUROMIN_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroMin: public NeuronTransferFunction {
public:
	NeuroMin();
	virtual ~NeuroMin();
};

#endif /* NEUROMIN_H_ */
