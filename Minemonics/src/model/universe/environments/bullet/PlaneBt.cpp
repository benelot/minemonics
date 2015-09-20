//# corresponding header
#include <model/universe/environments/bullet/PlaneBt.hpp>

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
//## view headers
//## utils headers

BoostLogger PlaneBt::mBoostLogger; /*<! initialize the boost logger*/
PlaneBt::_Init PlaneBt::_initializer;
PlaneBt::PlaneBt() {

}

PlaneBt::~PlaneBt() {
}

void PlaneBt::initialize() {
	/* Another primitive collision shape, an infinite plane.
	 To create a plane you have to pass both the plane's
	 normal vector (Vec3(nx, ny, nz)) and the plane constant
	 (d, which is the distance of the plane's origin.
	 Planes can only be used for static objects.
	 */
	mGroundShape = new btStaticPlaneShape(btVector3(0, 1, 0), btScalar(50.0f));

	btScalar mass = 0; //rigidbody is static if mass is zero, otherwise dynamic
	btVector3 localInertia(0, 0, 0);

	mGroundShape->calculateLocalInertia(mass, localInertia);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -50, 0));

	//motionstate provides interpolation capabilities, and only synchronizes 'active' objects
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,
		new btDefaultMotionState(groundTransform), mGroundShape, localInertia);
	mGroundBody = new btRigidBody(rbInfo);

	// disable debug visualization
	mGroundBody->setCollisionFlags(
		mGroundBody->getCollisionFlags()
			| btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
}

void PlaneBt::update(double timeSinceLastTick) {
}
