/*
 * NeuroWave.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROWAVE_H_
#define NEUROWAVE_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroWave: public NeuronTransferFunction {
public:
	NeuroWave();
	virtual ~NeuroWave();
};

#endif /* NEUROWAVE_H_ */
