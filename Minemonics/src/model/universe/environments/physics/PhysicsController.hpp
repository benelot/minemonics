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
public:

	enum PhysicsControllerType {
		GroundController, DeepSeaController
	};

	PhysicsController();
	~PhysicsController();

	/**
	 * Initialize bullet physics.
	 */
	void initBulletPhysics();

	/**
	 * Exit bullet physics.
	 */
	void exitBulletPhysics();

	/**
	 * Step bullet physics forward.
	 * @param timeStep The timestep to move forward.
	 */
	void stepBulletPhysics(const double timeStep);

	/**
	 * Add a bullet rigid body.
	 * @param body The body to be added.
	 */
	void addBody(btRigidBody* const body);

	/**
	 * Add a bullet rigid body.
	 * @param body The body to be added.
	 * @param collisionGroup its collision group
	 * @param collidesWith With which groups it collides.
	 */
	void addBody(btRigidBody* const body,int collisionGroup,int collidesWith);

	/**
	 * Remove a bullet ridig body.
	 * @param body The body to be removed.
	 */
	void removeBody(btRigidBody* const body);


	// Accessor methods
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

	double getSimulationSpeed() const {
		return mSimulationSpeed;
	}

	void setSimulationSpeed(double simulationSpeed) {
		mSimulationSpeed = simulationSpeed;
	}

private:
	//variables for to bullet physics API
	btAlignedObjectArray<btCollisionShape*> mCollisionShapes; //keep the collision shapes, for deletion/cleanup
	btBroadphaseInterface* mBroadphase;
	btCollisionDispatcher* mDispatcher;
	btConstraintSolver* mSolver;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btDynamicsWorld* mDynamicsWorld; //this is the most important class

	/**
	 * Is the physics simulation paused or not?
	 */
	bool mPhysicsPaused;

	/**
	 * Is the physics simulation triggered stepwise?
	 */
	bool mPhysicsStepped;

	/**
	 * The simulation speed
	 */
	int mSimulationSpeed;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_ */
