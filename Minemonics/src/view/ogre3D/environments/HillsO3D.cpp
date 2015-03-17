/*
 * HillsO3D.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "HillsO3D.h"

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

HillsO3D::HillsO3D(SimulationManager* simulationMgr) :
		EnvironmentO3D(simulationMgr), mTerrainsImported(false) {
}

HillsO3D::~HillsO3D() {
	// TODO Auto-generated destructor stub
}

void HillsO3D::initialize(Light* l) {
	EnvironmentO3D::initialize("HillsO3D",l);
	mPerlinNoiseTerrainGenerator = OGRE_NEW PerlinNoiseTerrainGenerator;
			mTerrainPagedWorldSection->setDefiner(mPerlinNoiseTerrainGenerator);
}

