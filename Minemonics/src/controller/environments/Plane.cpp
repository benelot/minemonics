/*
 * Plane.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <controller/environments/Plane.hpp>
#include <model/environments/bullet/PlaneBt.hpp>
#include <view/environments/PlaneO3D.hpp>

//## view headers

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
