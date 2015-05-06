//# corresponding headers
#include <controller/universe/environments/Plane.hpp>
#include <model/universe/environments/bullet/PlaneBt.hpp>
#include <view/universe/environments/PlaneO3D.hpp>

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
