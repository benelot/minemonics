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
#include <model/universe/environments/bullet/PlaneBt.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
#include <view/universe/environments/PlaneO3D.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

Plane::Plane() {
}

Plane::~Plane() {
}

void Plane::initialize(SimulationManager* simulationMgr, Ogre::Light* l,OgreBtDebugDrawer* debugDrawer) {
	Environment::initialize(Environment::PLANE);
	mEnvironmentGraphics = new PlaneO3D(simulationMgr);
	((PlaneO3D*) mEnvironmentGraphics)->initialize(l);
	mEnvironmentModel = new EnvironmentModel();
	mEnvironmentModel->setPhysicsController(new PhysicsController());
	mEnvironmentModel->getPhysicsController()->initBulletPhysics();
	//TODO:Encapsulate debug drawer
	mEnvironmentModel->getPhysicsController()->getDynamicsWorld()->setDebugDrawer(debugDrawer);
	mEnvironmentModel->getPhysicsController()->setPhysicsPaused(true);
	//TODO: Fix the way the planeBt is added
	mEnvironmentModel->setEnvironmentPhysics(new PlaneBt());
	((PlaneBt*)mEnvironmentModel->getEnvironmentPhysics())->initialize();
	//TODO:Refactor getbody
	mEnvironmentModel->getPhysicsController()->addBody(getBody());




}

EnvironmentModel* Plane::getEnvironmentModel() {
	//TODO: Implement environmentmodel
	return mEnvironmentModel;
}
