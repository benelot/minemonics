//# corresponding header
#include <model/universe/environments/physics/PhysicsController.hpp>

//# forward declarations
//# system headers
#include <cmath>

//## controller headers
//## model headers
#include <BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>
#include <BulletCollision/BroadphaseCollision/btDispatcher.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/ConstraintSolver/btNNCGConstraintSolver.h>
#include <BulletDynamics/ConstraintSolver/btContactSolverInfo.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletDynamics/Featherstone/btMultiBodyConstraintSolver.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletDynamics/MLCPSolvers/btDantzigSolver.h>
#include <BulletDynamics/MLCPSolvers/btSolveProjectedGaussSeidel.h>
#include <BulletDynamics/MLCPSolvers/btLemkeSolver.h>
#include <BulletDynamics/MLCPSolvers/btMLCPSolver.h>
#include <LinearMath/btMotionState.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers
#include <utils/bullet/BulletUtils.hpp>

BoostLogger PhysicsController::mBoostLogger; /*<! initialize the boost logger*/
PhysicsController::_Init PhysicsController::_initializer;
PhysicsController::PhysicsController() :
	mBroadphase(NULL), mCollisionConfiguration(NULL), mDispatcher(NULL), mDynamicsWorld(
	NULL), mPhysicsPaused(false), mPhysicsStepped(false), mSolver(NULL), mSimulationSpeed(
		pow(2, PhysicsConfiguration::SIMULATION_SPEED_01)), mPhysicsModelType(
		FeatherstoneModel), mEnvironmentType(GroundController) {

}

PhysicsController::PhysicsController(PhysicsModelType physicsModelType,
	EnvironmentType environmentType) :
	mBroadphase(NULL), mCollisionConfiguration(NULL), mDispatcher(NULL), mDynamicsWorld(
	NULL), mPhysicsPaused(false), mPhysicsStepped(false), mSolver(NULL), mSimulationSpeed(
		pow(2, PhysicsConfiguration::SIMULATION_SPEED_01)), mPhysicsModelType(
		physicsModelType), mEnvironmentType(environmentType) {

}

PhysicsController::~PhysicsController() {

	exitBulletPhysics();
}

void PhysicsController::initialize() {

	mCollisionConfiguration = new btDefaultCollisionConfiguration(); //collision configuration contains default setup for memory, collision setup
	//mCollisionConfiguration->setConvexConvexMultipointIterations();
	mDispatcher = new btCollisionDispatcher(mCollisionConfiguration); //use the default collision dispatcher
	mBroadphase = new btDbvtBroadphase();

	switch (mPhysicsModelType) {
	case PhysicsController::FeatherstoneModel: {
		//Use the btMultiBodyConstraintSolver for Featherstone btMultiBody support
		mSolver = new btMultiBodyConstraintSolver;
		//use btMultiBodyDynamicsWorld for Featherstone btMultiBody support
		mDynamicsWorld = new btMultiBodyDynamicsWorld(mDispatcher, mBroadphase,
			(btMultiBodyConstraintSolver*) mSolver, mCollisionConfiguration);

		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet Multibody Contraint Solver=";

		mDynamicsWorld->getSolverInfo().m_erp = BulletUtils::getERP(
			PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 1, 0.01);

		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Bullet DynamicsWorld ERP: " << mDynamicsWorld->getSolverInfo().m_erp;

		mDynamicsWorld->getSolverInfo().m_globalCfm = BulletUtils::getCFM(0,
			PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 1, 1); // approx 0, higher causes the the creature to fall through ground

		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Bullet DynamicsWorld CFM: " << mDynamicsWorld->getSolverInfo().m_globalCfm;

	}
	break;
	case PhysicsController::RigidbodyModel: {
		switch (PhysicsConfiguration::SOLVER_TYPE) {
			case PhysicsConfiguration::SEQUENTIALIMPULSESOLVER: {
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet Sequential Impulse Constraint Solver=";
				mSolver = new btSequentialImpulseConstraintSolver();
				break;
			}
			case PhysicsConfiguration::NNCGSOLVER: {
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet NNCG Constraint Solver=";
				mSolver = new btNNCGConstraintSolver();
				break;
			}
			case PhysicsConfiguration::DANZIGSOLVER: {
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet Danzig Solver=";
				btDantzigSolver* mlcp = new btDantzigSolver();
				mSolver = new btMLCPSolver(mlcp);
				break;
			}
			case PhysicsConfiguration::GAUSSSEIDELSOLVER: {
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet Projected Gauss Seidel Solver=";
				btSolveProjectedGaussSeidel* mlcp = new btSolveProjectedGaussSeidel();
				mSolver = new btMLCPSolver(mlcp);
				break;
			}
			case PhysicsConfiguration::LEMKESOLVER: {
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "=Bullet Lemke Solver=";
				btLemkeSolver* mlcp = new btLemkeSolver();
				mSolver = new btMLCPSolver(mlcp);
				break;
			}
			default:
			break;
		}

		//TODO: Fix parameters for other solvers than multibody

		mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase,mSolver, mCollisionConfiguration);

		if (PhysicsConfiguration::SOLVER_TYPE == PhysicsConfiguration::DANZIGSOLVER || PhysicsConfiguration::SOLVER_TYPE == PhysicsConfiguration::GAUSSSEIDELSOLVER) {
			mDynamicsWorld->getSolverInfo().m_minimumSolverBatchSize = 1; //for mlcp solver it is better to have a small A matrix
		} else {
			mDynamicsWorld->getSolverInfo().m_minimumSolverBatchSize = 128; //for direct solver, it is better to solve multiple objects together, small batches have high overhead
		}

		mDynamicsWorld->getSolverInfo().m_erp = BulletUtils::getERP(PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 100, 1);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Bullet DynamicsWorld ERP: " << mDynamicsWorld->getSolverInfo().m_erp;

		mDynamicsWorld->getSolverInfo().m_globalCfm = BulletUtils::getCFM(0,PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 100, 1);
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Bullet DynamicsWorld CFM: " << mDynamicsWorld->getSolverInfo().m_globalCfm;

		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Using split impulse feature with ERP/TurnERP: (" << mDynamicsWorld->getSolverInfo().m_erp2 << "," << mDynamicsWorld->getSolverInfo().m_splitImpulseTurnErp << ")";

		mDynamicsWorld->getDispatchInfo().m_useContinuous = true;
	}
	break;
	default:
	break;

	mDynamicsWorld->getSolverInfo().m_splitImpulse = 1; //enable split impulse feature
	mDynamicsWorld->getSolverInfo().m_splitImpulsePenetrationThreshold = -0.02;
	mDynamicsWorld->getSolverInfo().m_erp2 = BulletUtils::getERP(
		PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 10, 1);
	mDynamicsWorld->getSolverInfo().m_splitImpulseTurnErp = BulletUtils::getERP(
		PhysicsConfiguration::FIXED_STEP_SIZE_SEC, 10, 1);

	mDynamicsWorld->getSolverInfo().m_numIterations = 50;
}
	mDynamicsWorld->setGravity(
		btVector3(0, -PhysicsConfiguration::EARTH_GRAVITY, 0));
}

void PhysicsController::exitBulletPhysics() {
	//cleanup in the reverse order of creation/initialization

	//TODO: Find out why you get a segfault at obj
//	for (int i = mDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) { //remove the rigidbodies from the dynamics world and delete them
//		btCollisionObject* obj = mDynamicsWorld->getCollisionObjectArray()[i];
//		btRigidBody* body = btRigidBody::upcast(obj);
//		if (body && body->getMotionState())
//			delete body->getMotionState();
//
//		mDynamicsWorld->removeCollisionObject(obj);
//		delete obj;
//	}

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

void PhysicsController::stepBulletPhysics(const double timeStep) {
	//step the simulation
	if (mDynamicsWorld && (!mPhysicsPaused || mPhysicsStepped)) {

		if (timeStep) {
			// since we want to see all substeps, we make them by ourselves
			int subSteps = 1;

			mDynamicsWorld->stepSimulation(btScalar(timeStep),
				btScalar(subSteps),
				btScalar(PhysicsConfiguration::FIXED_STEP_SIZE_SEC));
		}

		//if step trigger is pressed, we pause the simulation and it steps forward every time we press the step trigger
		if (mPhysicsStepped) {
			mPhysicsStepped = false;
			mPhysicsPaused = true;
		}
	}
}

void PhysicsController::addBody(btRigidBody* const body) {
	mDynamicsWorld->addRigidBody(body); //add the body to the dynamics world
}

void PhysicsController::addBody(btRigidBody* const body, int collisionGroup,
	int collidesWith) {
	mDynamicsWorld->addRigidBody(body, collisionGroup, collidesWith); //add the body to the dynamics world
}

void PhysicsController::removeBody(btRigidBody* body) {
	mDynamicsWorld->removeRigidBody(body); //remove the body to the dynamics world
}
