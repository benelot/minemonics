/*
 * Plane.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "Plane.h"

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
#include "model/environments/bullet/PlaneBt.h"

//## view headers
#include "view/ogre3D/environments/PlaneO3D.h"

Plane::Plane() {
	// TODO Auto-generated constructor stub

}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

void Plane::initialize(SimulationManager* simulationMgr, Ogre::Light* l) {
	Environment::initialize(simulationMgr, Environment::PLANE);
	mEnvironmentGraphics = new PlaneO3D(mSimulationMgr);
	((PlaneO3D*) mEnvironmentGraphics)->initialize(l);
	mEnvironmentPhysics = new PlaneBt();
	((PlaneBt*) mEnvironmentPhysics)->initialize();
}
