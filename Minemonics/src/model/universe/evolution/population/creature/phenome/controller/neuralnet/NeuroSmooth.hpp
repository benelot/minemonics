/*
 * NeuroSmooth.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSMOOTH_H_
#define NEUROSMOOTH_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroSmooth: public NeuronTransferFunction {
public:
	NeuroSmooth();
	virtual ~NeuroSmooth();
};

#endif /* NEUROSMOOTH_H_ */
