#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_

//# corresponding header
#include <configuration/Definitions.hpp>

//# forward declarations
class btDynamicsWorld;
class btMultiBody;
class btRigidBody;
class btTransform;
class btVector3;

//# system headers
//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//## view headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

//## utils headers

/**
 * @brief		The Joint Bullet model holds the definition of the joint for the Bullet Physics engine.
 * @details		Details
 * @date		2015-03-25
 * @author		Benjamin Ellenberger
 */
class FSJointBt: public FSJointPhysics {
public:
	FSJointBt();
	FSJointBt(const FSJointBt& jointBt);

	/**
	 * Initialize the joint bullet physics model.
	 * @param world A handle to the bullet dynamics world.
	 * @param bodyA The rigidbody A to be connected.
	 * @param bodyB The rigidbody B to be connected.
	 * @param tframeInA The joint position in reference frame A.
	 * @param tframeInB The joint position in reference frame B.
	 */
	void initialize(btDynamicsWorld* const world, btRigidBody* const bodyA,
		btRigidBody* const bodyB, const btTransform& tframeInA,
		const btTransform& tframeInB, FSJointPhysics::JointType type,
		bool jointPitchEnabled, bool jointYawEnabled, bool jointRollEnabled,
		btVector3 jointPitchAxis, btVector3 jointLowerLimits,
		btVector3 jointUpperLimits);
	virtual ~FSJointBt();

	/**
	 * Initialize the rotational limit motors.
	 * @param maxForces The maximum forces of the joint.
	 * @param maxSpeeds The maximum speeds of the joint.
	 */
	void generateMotors(btMultiBody* multiBody,
		const int ownIndex, const btVector3 maxForces,
		const btVector3 maxSpeeds, const btVector3 lowerLimits,
		const btVector3 upperLimits);

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
	 * @param jointBt Another joint bullet physics model.
	 * @return If the joint bullet physics is equal to the other joint bullet physics.
	 */
	bool equals(const FSJointBt & jointBt) const;

	/**
	 * Clone the joint bt.
	 * @return The clone of the joint bt.
	 */
	virtual FSJointBt* clone();

	//Accessor methods

	void setLimits(const Ogre::Vector3 limits) {
		setLimits(OgreBulletUtils::convert(limits));
	}

	void setLimit(JointPhysics::RotationalDegreeOfFreedom dof,
		const double limit) {
//		mJoint->setLimit(dof, limit);
	}

	void setLimits(const btVector3 limits) {
//		mJoint->setLimit(limits.x(),limits.y(),limits.z());
	}

	void setBreakingThreshold(const double breakingThreshold) {
//		mJoint->setBreakingImpulseThreshold(breakingThreshold);
	}

	void setRotationalLimitMotorEnabled(
		const FSJointPhysics::RotationalDegreeOfFreedom index, const bool enable);

	bool isRotationalLimitMotorEnabled(
		const FSJointPhysics::RotationalDegreeOfFreedom index) {
		return true;
//		return mJoint->getRotationalLimitMotor(index)->m_enableMotor;
	}

	void setMaxRotationalForce(
		const FSJointPhysics::RotationalDegreeOfFreedom index,
		const double maxMotorForce) {
//		mJoint->setMaxMotorImpulse(maxMotorForce);

	}

	double getMaxRotationalForce(
		const FSJointPhysics::RotationalDegreeOfFreedom index) {
		return 0;
//		return mJoint->getRotationalLimitMotor(index)->m_maxMotorForce;
	}

	const std::vector<Motor*>& getMotors() const {
		return mMotors;
	}

	std::vector<Motor*>& getMotors() {
		return mMotors;
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the joint bullet physics model to a string.
	 * @param os The ostream.
	 * @param jointBt The joint bullet physics model we want to serialize.
	 * @return A string containing all information about the joint bullet physics model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const FSJointBt & jointBt) {
		for (std::vector<Motor*>::const_iterator it = jointBt.mMotors.begin(); /**!< The motors of the joint bullet physics model*/
		it != jointBt.mMotors.end(); it++) {
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
		ar.register_type(static_cast<FSServoMotor*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(FSJointPhysics); /**!< Serialize the base object */
	}

private:

	/**
	 * The bullet dynamics world of the bullet physics engine. Reference only.
	 */
	btDynamicsWorld* mWorld;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_ */
