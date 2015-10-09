//# corresponding headers
#include <controller/universe/environments/Plane.hpp>

//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/PlaneModel.hpp>
#include <model/universe/environments/bullet/PlaneBt.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/environments/physics/GroundController.hpp>

//## view headers
#include <view/universe/environments/PlaneO3D.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

BoostLogger Plane::mBoostLogger; /*<! initialize the boost logger*/
Plane::_Init Plane::_initializer;
Plane::Plane() :
	Environment() {
}

Plane::~Plane() {
//	They are all deleted in environment
}

void Plane::initialize(
	EnvironmentModel* const environmentModel,
	const Ogre::Light* const l) {
	Environment::initialize();

	// setup the planet model
	mEnvironmentModel = environmentModel;

	// setup the plane view
	mEnvironmentGraphics = new PlaneO3D((PlaneModel*) mEnvironmentModel);
	getPlaneView()->initialize(l);
}

void Plane::update(double timeSinceLastTick) {
	getPlaneModel()->update(timeSinceLastTick);
	getPlaneView()->update(timeSinceLastTick);
}
