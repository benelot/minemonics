//# corresponding headers
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/environments/Plane.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/bullet/PlaneBt.hpp>

//## view headers
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
	mEnvironmentModel = new EnvironmentModel();
	mEnvironmentModel->setEnvironmentPhysics(new PlaneBt());
	mEnvironmentModel->getEnvironmentPhysics()->initialize();
}

EnvironmentModel* Plane::getEnvironmentModel() {
	//TODO: Implement environmentmodel
	return NULL;
}
