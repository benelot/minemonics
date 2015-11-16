#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJointBt_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJointBt_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class btDynamicsWorld;
class btRigidBody;
class btTransform;
class btVector3;
class Motor;

//# system headers
//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.hpp>

//## view headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

//## utils headers

//comment this out to compare with original spring constraint

/** bullet physics cone twist constraint - A 3Dof angular joint with symmetric limits */
//#define CONSTRAINT_TYPE btConeTwistConstraint
//#define EXTRAPARAMS

/** bullet physics point 2 point constraint - A 3Dof angular joint without limits*/
//#define CONSTRAINT_TYPE btPoint2PointConstraint
//#define EXTRAPARAMS

/** bullet physics 6 degrees of freedom constraint - A 6 Dof joint with generic limits*/
#define CONSTRAINT_TYPE btGeneric6DofConstraint
#define EXTRAPARAMS ,true

/** bullet physics 6 degrees of freedom with spring constraint (more stable impl)*/
//#define CONSTRAINT_TYPE btGeneric6DofSpring2Constraint
//#define EXTRAPARAMS

/** bullet physics 6 degrees of freedom with spring constraint (first impl)*/
//#define CONSTRAINT_TYPE btGeneric6DofSpringConstraint
//#define EXTRAPARAMS ,true

/**
 * @brief		The Joint Bullet model holds the definition of the joint for the Bullet Physics engine.
 * @details		Details
 * @date		2015-03-25
 * @author		Benjamin Ellenberger
 */
class SRBJointBt: public JointPhysics {
public:
	SRBJointBt();
	SRBJointBt(const SRBJointBt& SRBJointBt);
	SRBJointBt(btDynamicsWorld* const world, btRigidBody* const bodyA,
		btRigidBody* const bodyB, const btTransform& tframeInA,
		const btTransform& tframeInB, JointPhysics::JointType type,
		bool jointPitchEnabled, bool jointYawEnabled, bool jointRollEnabled,
		btVector3 jointPitchAxis, btVector3 jointLowerLimits,
		btVector3 jointUpperLimits,int ownIndex);

	virtual ~SRBJointBt();

	/**
	 * Initialize the joint bullet physics model.
	 * @param world A handle to the bullet dynamics world.
	 * @param bodyA The rigidbody A to be connected.
	 * @param bodyB The rigidbody B to be connected.
	 * @param tframeInA The joint position in reference frame A.
	 * @param tframeInB The joint position in reference frame B.
	 */
	void initialize();

	virtual void applyJointTorque(int jointAxisIndex, double torque);

	virtual double getJointPos(int jointAxisIndex);

	virtual double getJointVel(int jointAxisIndex);

	virtual void setAngularDamping(double jointPitchDamping,double jointYawDamping, double jointRollDamping);

	/**
	 * Initialize the rotational limit motors.
	 * @param maxForces The maximum forces of the joint.
	 * @param maxSpeeds The maximum speeds of the joint.
	 */
	virtual void generateMotors(const btVector3 maxForces,
		const btVector3 lowerLimits, const btVector3 upperLimits);

	/**
	 * Reset the joint to the place when the creature was born.
	 */
	virtual void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the joint without resetting it.
	 */
	virtual void reposition(const Ogre::Vector3 position);

	/**
	 * Update the joint bullet physics model.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Add the joint bullet physics model to the world.
	 */
	void addToWorld();

	/**
	 * Remove the joint bullet physics models from the world.
	 */
	void removeFromWorld();

//	/**
//	 * Returns if the joint is under tension.
//	 * @return If the joint is under tension.
//	 */
//	bool isStrained();

	/**
	 * Compare the joint bullet physics to another joint bullet physics.
	 * @param SRBJointBt Another joint bullet physics model.
	 * @return If the joint bullet physics is equal to the other joint bullet physics.
	 */
	bool equals(const SRBJointBt & SRBJointBt) const;

	/**
	 * Clone the joint bt.
	 * @return The clone of the joint bt.
	 */
	virtual SRBJointBt* clone();

	//Accessor methods

	void setLimits(const Ogre::Vector3 limits) {
		setLimits(OgreBulletUtils::convert(limits));
	}

	void setLimit(JointPhysics::RotationalDegreeOfFreedom dof,
		const double limit) {
//		mJoint->setLimit(dof, limit);
	}

	void setLimits(const btVector3 limits) {
//		mJoint->setLimit(limits.x(), limits.y(), limits.z());
	}

	void setBreakingThreshold(const double breakingThreshold) {
//		mJoint->setBreakingImpulseThreshold(breakingThreshold);
	}

	void setRotationalLimitMotorEnabled(
		const JointPhysics::RotationalDegreeOfFreedom index, const bool enable);

	bool isRotationalLimitMotorEnabled(
		const JointPhysics::RotationalDegreeOfFreedom index) {
		return true;
//		return mJoint->getRotationalLimitMotor(index)->m_enableMotor;
	}

	void setTargetRotationalVelocity(
		JointPhysics::RotationalDegreeOfFreedom index, double targetVelocity) {
//		mJoint->getRotationalLimitMotor(index)->m_targetVelocity = targetVelocity;
	}

	double getTargetRotationalVelocity(
		const JointPhysics::RotationalDegreeOfFreedom index) {
		return 0;
//		return mJoint->getRotationalLimitMotor(index)->m_targetVelocity;
	}

	void setMaxRotationalForce(
		const JointPhysics::RotationalDegreeOfFreedom index,
		const double maxMotorForce) {
//		mJoint->setMaxMotorImpulse(maxMotorForce);

	}

	double getMaxRotationalForce(
		const JointPhysics::RotationalDegreeOfFreedom index) {
		return 0;
//		return mJoint->getRotationalLimitMotor(index)->m_maxMotorForce;
	}

	CONSTRAINT_TYPE* getJoint() {
		return mJoint;
	}

	virtual const std::vector<Motor*>& getMotors() const {
		return mMotors;
	}

	virtual std::vector<Motor*>& getMotors() {
		return mMotors;
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the joint bullet physics model to a string.
	 * @param os The ostream.
	 * @param SRBJointBt The joint bullet physics model we want to serialize.
	 * @return A string containing all information about the joint bullet physics model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const SRBJointBt & SRBJointBt) {
		for (std::vector<Motor*>::const_iterator it =
			SRBJointBt.mMotors.begin(); /**!< The motors of the joint bullet physics model*/
		it != SRBJointBt.mMotors.end(); it++) {
			os << (**it);
			os << "||";
		}
		return os;
	}

	/**
	 * Serializes the joint bullet physics model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<SRBServoMotor*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointPhysics); /**!< Serialize the base object */
	}

	void setMotorTarget(const btQuaternion motorTarget) {
		mMotorTarget = motorTarget;
	}

	void setBodyA(btRigidBody* bodyA) {
		mBodyA = bodyA;
	}

	void setBodyB(btRigidBody* bodyB) {
		mBodyB = bodyB;
	}

	void setFrameInA(const btTransform& frameInA) {
		mFrameInA = frameInA;
	}

	void setFrameInB(const btTransform& frameInB) {
		mFrameInB = frameInB;
	}

	void setWorld(btDynamicsWorld* world) {
		mWorld = world;
	}

private:

	/**
	 * The 6 Degrees of freedom joint that is used as a physical model.
	 */
	CONSTRAINT_TYPE* mJoint;

	/**
	 * The bullet dynamics world of the bullet physics engine. Reference only.
	 */
	btDynamicsWorld* mWorld;

	btQuaternion mMotorTarget;

	btRigidBody* mBodyA;
	btRigidBody* mBodyB;
	btTransform mFrameInA;
	btTransform mFrameInB;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJOINTBT_HPP_ */
