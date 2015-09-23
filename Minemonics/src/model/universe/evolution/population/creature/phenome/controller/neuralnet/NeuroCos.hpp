/*
 * NeuroCos.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROCOS_H_
#define NEUROCOS_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroCos: public NeuronTransferFunction {
public:
	NeuroCos();
	virtual ~NeuroCos();
};

#endif /* NEUROCOS_H_ */
