/*
 * NeuroSaw.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSAW_H_
#define NEUROSAW_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroSaw: public NeuronTransferFunction {
public:
	NeuroSaw();
	virtual ~NeuroSaw();
};

#endif /* NEUROSAW_H_ */
