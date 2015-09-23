/*
 * NeuroThreshold.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROTHRESHOLD_H_
#define NEUROTHRESHOLD_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroThreshold: public NeuronTransferFunction {
public:
	NeuroThreshold();
	virtual ~NeuroThreshold();
};

#endif /* NEUROTHRESHOLD_H_ */
