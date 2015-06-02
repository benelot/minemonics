/*
 * PlaneO3D.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <SimulationManager.hpp>
#include <view/universe/environments/PlaneO3D.hpp>

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

void PlaneO3D::initialize(Ogre::Light* l) {
	EnvironmentO3D::initialize("PlaneO3D",l);
	mTerrainPagedWorldSection->setDefiner(OGRE_NEW PlaneTerrainDefiner);
}

void PlaneO3D::update(){
	EnvironmentO3D::update();
}

