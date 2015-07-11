#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_

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
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

/**
 * @brief		The physics controller holds the bullet physics resources of a certain planet.
 * @details		Details
 * @date		2015-03-03
 * @author		Benjamin Ellenberger
 */
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

	enum PhysicsControllerType {
		GroundController, DeepSeaController
	};

	PhysicsController();
	~PhysicsController();

	void initBulletPhysics();
	void exitBulletPhysics();
	void stepBulletPhysics(double timeStep);

	void addBody(btRigidBody* body);

	void removeBody(btRigidBody* body);

	btDynamicsWorld*& getDynamicsWorld() {
		return mDynamicsWorld;
	}

	/**
	 * Set the gravity used in the physics engine
	 * @param gravity The gravity used in the physics simulator.
	 */
	void setGravity(const double gravity) const {
		mDynamicsWorld->setGravity(
				btVector3(0,
						-gravity
								* PhysicsConfiguration::REALITY_BULLET_GRAVITY_SCALING_FACTOR,
						0));
	}

	/**
	 * Get the gravitational force of the physics engine.
	 * @return The gravitational force of the physics engine.
	 */
	double getGravity() {
		return -mDynamicsWorld->getGravity().getY()
				/ PhysicsConfiguration::REALITY_BULLET_GRAVITY_SCALING_FACTOR;
	}

	bool isPhysicsPaused() const {
		return mPhysicsPaused;
	}

	void setPhysicsPaused(bool physicsPaused) {
		mPhysicsPaused = physicsPaused;
	}

	void setDebugDrawer(OgreBtDebugDrawer* debugDrawer) {
		mDynamicsWorld->setDebugDrawer(debugDrawer);
	}

	/**
	 * Is the physics simulation paused or not?
	 */
	bool mPhysicsPaused;

	/**
	 * Is the physics simulation triggered stepwise?
	 */
	bool mPhysicsStepped;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_ */
