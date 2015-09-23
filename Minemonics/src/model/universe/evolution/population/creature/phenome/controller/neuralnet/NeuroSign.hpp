/*
 * NeuroSign.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSIGN_H_
#define NEUROSIGN_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroSign: public NeuronTransferFunction {
public:
	NeuroSign();
	virtual ~NeuroSign();
};

#endif /* NEUROSIGN_H_ */
