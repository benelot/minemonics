/*
 * Hills.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Hills.h"

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
#include "model/environments/bullet/HillsBt.h"

//## view headers
#include "view/ogre3D/environments/HillsO3D.h"

Hills::Hills() {
	// TODO Auto-generated constructor stub

}

Hills::~Hills() {
	// TODO Auto-generated destructor stub
}

void Hills::initialize(SimulationManager* simulationMgr, Ogre::Light* l) {
	Environment::initialize(simulationMgr, Environment::HILLS);

	mEnvironmentGraphics = new HillsO3D(mSimulationMgr);
	((HillsO3D*) mEnvironmentGraphics)->initialize(l);
	mEnvironmentPhysics = new HillsBt();

	//		Ogre::TerrainGroup * pGroup = ((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup();
	//		Ogre::Terrain * terrain = pGroup->getTerrain(0, 0);

	//((HillsBt*) mEnvironmentPhysics)->initialize(((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup()->getTerrain(0, 0));

}

