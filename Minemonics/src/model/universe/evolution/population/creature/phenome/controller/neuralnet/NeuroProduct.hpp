/*
 * NeuroProduct.h
 *
 *  Created on: Dec 19, 2014
 *      Author: leviathan
 */

#ifndef NEUROPRODUCT_H_
#define NEUROPRODUCT_H_

#include <model/universe/evolution/population/creature/phenome/controller/neuralnet/NeuronTransferFunction.hpp>

class NeuroProduct: public NeuronTransferFunction {
public:
	NeuroProduct();
	virtual ~NeuroProduct();
};

#endif /* NEUROPRODUCT_H_ */
