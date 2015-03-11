/*
 * ControllerGene.cpp
 *
 *  Created on: Mar 9, 2015
 *      Author: leviathan
 */

#include <model/evolution/population/creature/genome/controller/ControllerGene.h>

ControllerGene::ControllerGene() {

}

ControllerGene::~ControllerGene() {
	// TODO Auto-generated destructor stub
}

bool ControllerGene::equals(const ControllerGene& controllerGene) {
	if (mControllerGeneType != controllerGene.mControllerGeneType)
		return false;

	return true;
}

