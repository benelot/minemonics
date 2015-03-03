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

void PhysicsController::initBulletPhysics() {

	mCollisionConfiguration = new btDefaultCollisionConfiguration(); //collision configuration contains default setup for memory, collision setup
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration); //use the default collision dispatcher
	mBroadphase = new btDbvtBroadphase();
	mSolver = new btSequentialImpulseConstraintSolver; //the default constraint solver
	mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase,
			mSolver, mCollisionConfiguration);
	mDynamicsWorld->setGravity(btVector3(0, -1000, 0));

	//Creating a static shape which will act as ground
	{
		//btCollisionShape* groundShape = new btBoxShape(btVector3(50,50,50));
		btCollisionShape* groundShape = new btStaticPlaneShape(
				btVector3(0, 1, 0), 50);
		mCollisionShapes.push_back(groundShape);

		btScalar mass = 0; //rigidbody is static if mass is zero, otherwise dynamic
		btVector3 localInertia(0, 0, 0);

		groundShape->calculateLocalInertia(mass, localInertia);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -50, 0));

		btDefaultMotionState* myMotionState = new btDefaultMotionState(
				groundTransform); //motionstate provides interpolation capabilities, and only synchronizes 'active' objects
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
				groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		mDynamicsWorld->addRigidBody(body); //add the body to the dynamics world
	}

	//Creating some dynamic boxes
	{
		btVector3 ogreBoxSize(96.9, 96.9, 96.9);
		btVector3 HalfExtents(ogreBoxSize.x()*0.5f,ogreBoxSize.y()*0.5f,ogreBoxSize.z()*0.5f);
		btCollisionShape* boxShape = new btBoxShape(HalfExtents);
		mCollisionShapes.push_back(boxShape);

		btScalar mass = 1.0f;
		btVector3 localInertia(0, 0, 0);

		boxShape->calculateLocalInertia(mass, localInertia);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(5, 20, 0));

		for (int j = 0; j < 1000; j++) {
			startTransform.setOrigin(btVector3(0, (j * 20) + 10, j*10));

			btDefaultMotionState* myMotionState = new btDefaultMotionState(
					startTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState,
					boxShape, localInertia);
			btRigidBody* body = new btRigidBody(rbInfo);

			mDynamicsWorld->addRigidBody(body);
		}

	}

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
	if (mDynamicsWorld) //step the simulation
		mDynamicsWorld->stepSimulation(timeStep); //1.0f/60.0f);
}
