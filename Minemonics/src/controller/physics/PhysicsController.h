/*
 * PhysicsController.h
 *
 *  Created on: Mar 3, 2015
 *      Author: leviathan
 */

#ifndef PHYSICSCONTROLLER_H_
#define PHYSICSCONTROLLER_H_

//# corresponding header

//# forward declarations

//# system headers
//## controller headers
#include <btBulletDynamicsCommon.h>

//## model headers

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

class PhysicsController {
private:
	//variables for to bullet physics API
	btAlignedObjectArray<btCollisionShape*> mCollisionShapes; //keep the collision shapes, for deletion/cleanup
	btBroadphaseInterface* mBroadphase;
	btCollisionDispatcher* mDispatcher;
	btConstraintSolver* mSolver;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btDynamicsWorld* mDynamicsWorld; //this is the most important class

public:
	void initBulletPhysics();
	void exitBulletPhysics();
	void stepBulletPhysics(double timeStep);

	void addBody(btRigidBody* body);

	btDynamicsWorld*& getDynamicsWorld() {
		return mDynamicsWorld;
	}
};

#endif /* PHYSICSCONTROLLER_H_ */
