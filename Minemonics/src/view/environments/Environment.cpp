/*
 * Environment.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Environment.h"

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
#include "model/environments/EnvironmentPhysics.h"
#include "model/environments/bullet/PlaneBt.h"
#include "model/environments/bullet/HillsBt.h"

//## view headers
#include "view/environments/EnvironmentGraphics.h"
#include "view/ogre3D/environments/HillsO3D.h"
#include "view/ogre3D/environments/PlaneO3D.h"

//## utils headers

Environment::Environment(SimulationManager* simulationMgr,
		EnvironmentType environmentType) :
		mSimulationMgr(simulationMgr), mEnvironmentType(environmentType), mEnvironmentGraphics(
		NULL), mEnvironmentPhysics(NULL) {
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

void Environment::initialize(Ogre::Light* l) {
	switch (mEnvironmentType) {
	case Environment::HILLS:
		mEnvironmentGraphics = new HillsO3D(mSimulationMgr);
		((HillsO3D*) mEnvironmentGraphics)->initialize(l);
		mEnvironmentPhysics = new HillsBt();

//		Ogre::TerrainGroup * pGroup = ((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup();
//		Ogre::Terrain * terrain = pGroup->getTerrain(0, 0);

		//((HillsBt*) mEnvironmentPhysics)->initialize(((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup()->getTerrain(0, 0));
		break;
	case Environment::PLANE:
		mEnvironmentGraphics = new PlaneO3D(mSimulationMgr);
		((PlaneO3D*) mEnvironmentGraphics)->initialize(l);
		mEnvironmentPhysics = new PlaneBt();
		((PlaneBt*) mEnvironmentPhysics)->initialize();
		break;
	case Environment::OPENSEA:
		//TODO: Implement water environment
		break;
	default:
		break;
	}
}

btRigidBody*& Environment::getBody() {
	return ((EnvironmentBt*) mEnvironmentPhysics)->getBody();
}

