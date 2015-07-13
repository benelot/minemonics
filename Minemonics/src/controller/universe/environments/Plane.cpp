//# corresponding headers
//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/environments/Plane.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/PlaneModel.hpp>
#include <model/universe/environments/bullet/PlaneBt.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

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

void Plane::initialize(SimulationManager* const simulationMgr, const Ogre::Light* const l,
		OgreBtDebugDrawer* const debugDrawer) {
	Environment::initialize(Environment::PLANE);

	// setup the plane view
	mEnvironmentGraphics = new PlaneO3D(simulationMgr);
	getPlaneView()->initialize(l);

	// setup the planet model
	mEnvironmentModel = new PlaneModel();
	getPlaneModel()->initialize();

	// set up the physics controller
	mEnvironmentModel->setPhysicsController(new PhysicsController());
	mEnvironmentModel->getPhysicsController()->initBulletPhysics();
	mEnvironmentModel->getPhysicsController()->setDebugDrawer(debugDrawer);
}

void Plane::update() {
	getPlaneModel()->update();
	getPlaneView()->update();
}
