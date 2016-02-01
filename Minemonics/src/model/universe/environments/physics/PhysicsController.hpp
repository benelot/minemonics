#ifndef MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_
#define MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>

//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <LinearMath/btAlignedObjectArray.h>
#include <LinearMath/btVector3.h>

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
#include <utils/logging/Logger.hpp>

/**
 * @brief		The physics controller holds the bullet physics resources of a certain planet.
 * @details		Details
 * @date		2015-03-03
 * @author		Benjamin Ellenberger
 */
class PhysicsController {
public:
	enum PhysicsModelType {
		FeatherstoneModel, RigidbodyModel, MixedBodyModel
	};

	enum EnvironmentType {
		GroundController, DeepSeaController
	};

	PhysicsController();
	PhysicsController(PhysicsModelType solverType,
		EnvironmentType environmentType);
	virtual ~PhysicsController();

	/**
	 * Initialize bullet physics.
	 */
	void initialize();

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
	void addBody(btRigidBody* const body, int collisionGroup, int collidesWith);

	/**
	 * Remove a bullet ridig body.
	 * @param body The body to be removed.
	 */
	void removeBody(btRigidBody* const body);

	// Accessor methods ##########################

	btDynamicsWorld*& getDynamicsWorld() {
		return mDynamicsWorld;
	}

	/**
	 * Set the gravity used in the physics engine
	 * @param gravity The gravity used in the physics simulator.
	 */
	void setGravity(const double gravity) const {
		mDynamicsWorld->setGravity(btVector3(0, -gravity, 0));
	}

	/**
	 * Get the gravitational force of the physics engine.
	 * @return The gravitational force of the physics engine.
	 */
	double getGravity() {
		return -mDynamicsWorld->getGravity().getY();
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

	PhysicsModelType getPhysicsModelType() const {
		return mPhysicsModelType;
	}

	void drawDebugWorld() {
		mDynamicsWorld->debugDrawWorld(); /**!< draws the debug world if it is enabled*/
	}

	// Serialization ##########################
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the planet model to a string.
	 * @param os The ostream.
	 * @param planet The planet we want to serialize.
	 * @return A string containing all information about the planet.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const PhysicsController &physicsController) {
//		os
//
//		<< "/PlanetModel: Name=" << planet.mName /**!< The name of the creature */
//
//		/**The evolutionmodel of the planet*/
//		<< "\n/EvolutionModel=" << planet.mEvolutionModel
//
//		/**!< The environment of the planet */
//		<< "\n/EnvironmentModel=" << planet.mEnvironmentModel;
//
//		/**The epochs of the planet*/
//		for (std::vector<Epoch*>::const_iterator eit = planet.mEpochs.begin();
//			eit != planet.mEpochs.end(); eit++) {
//			os << (**eit) << "||";
//		}
//
//		/** The current epoch of the planet*/
//		os << "\n/Current Epoch=" << planet.mCurrentEpoch;
		return os;
	}

	/**
	 * Serializes the environment to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mPhysicsPaused) /**!< */
		& BOOST_SERIALIZATION_NVP(mPhysicsStepped) /**!< */
		& BOOST_SERIALIZATION_NVP(mSimulationSpeed) /**!< */
		& BOOST_SERIALIZATION_NVP(mPhysicsPaused) /**!< TODO: Duplicate */
		& BOOST_SERIALIZATION_NVP(mPhysicsModelType) /**!< */
		& BOOST_SERIALIZATION_NVP(mEnvironmentType); /**!< */
	}

protected:
	//variables for to bullet physics API
	btBroadphaseInterface* mBroadphase; /**!< The broadphase interface */
	btCollisionDispatcher* mDispatcher; /**!< The Collision dispatcher */
	btDefaultCollisionConfiguration* mCollisionConfiguration;

	btDynamicsWorld* mDynamicsWorld; /**!< The dynamics world defining the physics model of the simulation */
	btConstraintSolver* mSolver; /**!< The constraint solver */

	bool mPhysicsPaused; /**!< Is the physics simulation paused or not?*/

	bool mPhysicsStepped; /**!< Is the physics simulation triggered stepwise? */

	int mSimulationSpeed; /**!< The simulation speed */

	PhysicsModelType mPhysicsModelType; /**!< The physics model type of the controller */

	EnvironmentType mEnvironmentType; /**!< The environment type the physics controller simulates */

	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"PhysicsController"));
		}
	} _initializer;
};
BOOST_CLASS_VERSION(PhysicsController, 1)
#endif /* MODEL_UNIVERSE_ENVIRONMENTS_PHYSICS_PHYSICSCONTROLLER_H_ */
