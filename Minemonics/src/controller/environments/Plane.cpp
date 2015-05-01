//# corresponding headers
#include <controller/environments/Plane.hpp>

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
#include <model/environments/bullet/PlaneBt.hpp>

//## view headers
#include <view/environments/PlaneO3D.hpp>

//## utils headers

Plane::Plane() {
}

Plane::~Plane() {
}

void Plane::initialize(SimulationManager* simulationMgr, Ogre::Light* l) {
	Environment::initialize(simulationMgr, Environment::PLANE);
	mEnvironmentGraphics = new PlaneO3D(mSimulationMgr);
	((PlaneO3D*) mEnvironmentGraphics)->initialize(l);
	mEnvironmentPhysics = new PlaneBt();
	((PlaneBt*) mEnvironmentPhysics)->initialize();
}
