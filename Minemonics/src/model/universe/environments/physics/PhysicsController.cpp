//# corresponding header
#include <configuration/Definitions.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//# forward declarations
//# system headers
#include <cmath>

//## controller headers
//## model headers
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletDynamics/MLCPSolvers/btDantzigSolver.h>
#include <BulletDynamics/MLCPSolvers/btSolveProjectedGaussSeidel.h>
#include <BulletDynamics/MLCPSolvers/btMLCPSolver.h>
#include <LinearMath/btMotionState.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

PhysicsController::PhysicsController(PhysicsModelType physicsModelType,
	EnvironmentType environmentType) :
	mBroadphase(NULL), mCollisionConfiguration(NULL), mDispatcher(NULL), mDynamicsWorld(
		NULL), mPhysicsPaused(false), mPhysicsStepped(false), mSolver(NULL), mSimulationSpeed(
		pow(2, PhysicsConfiguration::SIMULATION_SPEED_01)), mPhysicsModelType(
		physicsModelType), mEnvironmentType(environmentType) {

}

PhysicsController::~PhysicsController() {
	delete mDynamicsWorld;
	mDynamicsWorld = NULL;

	delete mSolver;
	mSolver = NULL;

	delete mBroadphase;
	mBroadphase = NULL;

	delete mDispatcher;
	mDispatcher = NULL;

	delete mCollisionConfiguration;
	mCollisionConfiguration = NULL;

}

void PhysicsController::initBulletPhysics() {

	mCollisionConfiguration = new btDefaultCollisionConfiguration(); //collision configuration contains default setup for memory, collision setup
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration); //use the default collision dispatcher
	mBroadphase = new btDbvtBroadphase();

	switch (mPhysicsModelType) {
	case PhysicsController::FeatherstoneModel: {
		//Use the btMultiBodyConstraintSolver for Featherstone btMultiBody support
		mSolver = new btMultiBodyConstraintSolver;
		//use btMultiBodyDynamicsWorld for Featherstone btMultiBody support
		mDynamicsWorld = new btMultiBodyDynamicsWorld(mDispatcher, mBroadphase,
			(btMultiBodyConstraintSolver*) mSolver, mCollisionConfiguration);

		mDynamicsWorld->getSolverInfo().m_erp =
			PhysicsConfiguration::SIMULATOR_PHYSICS_FS_ERP;

		mDynamicsWorld->getSolverInfo().m_globalCfm =
			PhysicsConfiguration::SIMULATOR_PHYSICS_FS_CFM;
		break;
	}
	case PhysicsController::RigidbodyModel: {
		bool useMCLPSolver = false;
		if (useMCLPSolver) {
			btDantzigSolver* mlcp = new btDantzigSolver();
//			btSolveProjectedGaussSeidel* mlcp = new btSolveProjectedGaussSeidel();
			btMLCPSolver* sol = new btMLCPSolver(mlcp);
			mSolver = sol;
		} else {
			mSolver = new btSequentialImpulseConstraintSolver();
		}

		mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase,
			mSolver, mCollisionConfiguration);

//		if (useMCLPSolver) {
//			mDynamicsWorld->getSolverInfo().m_minimumSolverBatchSize = 1; //for mlcp solver it is better to have a small A matrix
//		} else {
//			mDynamicsWorld->getSolverInfo().m_minimumSolverBatchSize = 128; //for direct solver, it is better to solve multiple objects together, small batches have high overhead
//		}

		mDynamicsWorld->getSolverInfo().m_erp = 0.00001f;
		//PhysicsConfiguration::SIMULATOR_PHYSICS_SRB_ERP;

		mDynamicsWorld->getSolverInfo().m_globalCfm = 0.9f;
		//PhysicsConfiguration::SIMULATOR_PHYSICS_SRB_CFM;
		break;
	}
	default:
		break;
	}

	mDynamicsWorld->getSolverInfo().m_splitImpulse = 1; //enable split impulse feature
	mDynamicsWorld->getSolverInfo().m_splitImpulsePenetrationThreshold = -0.02;
	mDynamicsWorld->getSolverInfo().m_erp2 =
		PhysicsConfiguration::SIMULATOR_PHYSICS_FS_ERP;
	mDynamicsWorld->getSolverInfo().m_splitImpulseTurnErp =
		PhysicsConfiguration::SIMULATOR_PHYSICS_FS_ERP;
	//TODO: Not sure if helps
	//	mDynamicsWorld->getDispatchInfo().m_useContinuous = true;
	//	mDynamicsWorld->getSolverInfo().m_numIterations = 100;

	mDynamicsWorld->setGravity(
		btVector3(0,
			-PhysicsConfiguration::EARTH_GRAVITY
				* PhysicsConfiguration::REALITY_BULLET_GRAVITY_SCALING_FACTOR,
			0));
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
	mDynamicsWorld = 0;
	delete mSolver;
	mSolver = 0;
	delete mBroadphase;
	mBroadphase = 0;
	delete mDispatcher;
	mDispatcher = 0;
	delete mCollisionConfiguration;
	mCollisionConfiguration = 0;
}

void PhysicsController::stepBulletPhysics(const double timeStep) {
	//step the simulation
	if (mDynamicsWorld && (!mPhysicsPaused || mPhysicsStepped)) {

		if (timeStep) {
			// since we want to see all substeps, we make them by ourselves
			int subSteps = 1;

			mDynamicsWorld->stepSimulation(timeStep, subSteps,
				PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEP_SIZE_SEC);
		}

		//if step trigger is pressed, we pause the simulation and it steps forward every time we press the step trigger
		if (mPhysicsStepped) {
			mPhysicsStepped = false;
			mPhysicsPaused = true;
		}
	}
}

void PhysicsController::addBody(btRigidBody* const body) {
	mCollisionShapes.push_back(body->getCollisionShape());
	mDynamicsWorld->addRigidBody(body); //add the body to the dynamics world
}

void PhysicsController::addBody(btRigidBody* const body, int collisionGroup,
	int collidesWith) {
	mCollisionShapes.push_back(body->getCollisionShape());
	mDynamicsWorld->addRigidBody(body, collisionGroup, collidesWith); //add the body to the dynamics world
}

void PhysicsController::removeBody(btRigidBody* body) {
	mCollisionShapes.remove(body->getCollisionShape());
	mDynamicsWorld->removeRigidBody(body); //remove the body to the dynamics world
}
