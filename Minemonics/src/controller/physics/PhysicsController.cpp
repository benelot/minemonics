/*
 * PhysicsController.cpp
 *
 *  Created on: Mar 3, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "PhysicsController.h"
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

PhysicsController::PhysicsController() :
		mBroadphase(NULL), mCollisionConfiguration(NULL), mDispatcher(NULL), mDynamicsWorld(
				NULL), mPhysicsPaused(false), mPhysicsStepped(false), mSolver(
				NULL) {

}

PhysicsController::~PhysicsController() {

}

void PhysicsController::initBulletPhysics() {

	mCollisionConfiguration = new btDefaultCollisionConfiguration(); //collision configuration contains default setup for memory, collision setup
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration); //use the default collision dispatcher
	mBroadphase = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver; //the default constraint solver
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase,
			mSolver, mCollisionConfiguration);
	mDynamicsWorld->setGravity(
			btVector3(0,
					-PhysicsConfiguration::EARTH_GRAVITY
							* PhysicsConfiguration::REALITY_BULLET_GRAVITY_SCALING_FACTOR,
					0));

	createBox(1, 1, 1, 1);
}

void PhysicsController::exitBulletPhysics() {
	//cleanup in the reverse order of creation/initialization

	for (int i = mDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) //remove the rigidbodies from the dynamics world and delete them
			{
		btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
			delete body->getMotionState();

		mDynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	for (int j = 0; j < mCollisionShapes.size(); j++) //delete collision shapes
			{
		btCollisionShape* shape = mCollisionShapes[j];
		delete shape;
	}

	mCollisionShapes.clear();
	delete mDynamicsWorld;
	delete mSolver;
	delete mBroadphase;
	delete mDispatcher;
	delete mCollisionConfiguration;
}

void PhysicsController::stepBulletPhysics(double timeStep) {
	if (mDynamicsWorld && (!mPhysicsPaused || (mPhysicsStepped))) //step the simulation
			{
		mDynamicsWorld->stepSimulation(timeStep); //1.0f/60.0f);

		//if step trigger is pressed, we pause the simulation and it steps forward everytime we press the step trigger
		if (mPhysicsStepped) {
			mPhysicsStepped = false;
			mPhysicsPaused = true;
		}
	}
}

void PhysicsController::addBody(btRigidBody* body) {
	mCollisionShapes.push_back(body->getCollisionShape());
	mDynamicsWorld->addRigidBody(body); //add the body to the dynamics world
}

void PhysicsController::createBox(double length, double width, double height,
		btScalar mass) {
	btVector3 bulletBoxSize(
			width * PhysicsConfiguration::OGRE_BULLET_BOX_SCALING_FACTOR,
			height * PhysicsConfiguration::OGRE_BULLET_BOX_SCALING_FACTOR,
			length * PhysicsConfiguration::OGRE_BULLET_BOX_SCALING_FACTOR);
	btVector3 HalfExtents(bulletBoxSize.x() * 0.5f, bulletBoxSize.y() * 0.5f,
			bulletBoxSize.z() * 0.5f);
	btCollisionShape* boxShape = new btBoxShape(HalfExtents);
	mCollisionShapes.push_back(boxShape);

	btVector3 localInertia(0, 0, 0);

	boxShape->calculateLocalInertia(mass, localInertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(5, 20, 0));

	for (int j = 0; j < 100; j++) {
		startTransform.setOrigin(btVector3(0, (j * 20) + 10, j * 10));

		btDefaultMotionState* myMotionState = new btDefaultMotionState(
				startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
				boxShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		mDynamicsWorld->addRigidBody(body);
	}
}
