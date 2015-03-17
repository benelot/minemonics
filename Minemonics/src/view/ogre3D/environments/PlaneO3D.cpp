/*
 * PlaneO3D.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "PlaneO3D.h"

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

PlaneO3D::PlaneO3D(SimulationManager* simulationMgr) :
		EnvironmentO3D(simulationMgr), mTerrainsImported(false) {

}

PlaneO3D::~PlaneO3D() {
	// TODO Auto-generated destructor stub
}

void PlaneO3D::initialize(Light* l) {
	EnvironmentO3D::initialize("PlaneO3D",l);
	mTerrainPagedWorldSection->setDefiner(OGRE_NEW PlaneTerrainDefiner);
}


