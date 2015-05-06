/*
 * Hills.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <controller/universe/environments/Hills.hpp>
#include <model/universe/environments/bullet/HillsBt.hpp>
#include <view/universe/environments/HillsO3D.hpp>

//## view headers

Hills::Hills() {
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

