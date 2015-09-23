/*
 * NeuroSin.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROSIN_H_
#define NEUROSIN_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroSin: public NeuronTransferFunction {
public:
	NeuroSin();
	virtual ~NeuroSin();
};

#endif /* NEUROSIN_H_ */
