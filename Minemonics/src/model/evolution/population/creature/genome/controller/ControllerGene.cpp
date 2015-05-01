/*
 * ControllerGene.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

//# corresponding headers
#include <model/evolution/population/creature/genome/controller/ControllerGene.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

ControllerGene::ControllerGene():mControllerGeneType(GenericControllerGene) {

}

ControllerGene::~ControllerGene() {
}

bool ControllerGene::equals(const ControllerGene& controllerGene) const {

	if (mControllerGeneType != controllerGene.mControllerGeneType) {
		return false;
	}

	return true;
}

