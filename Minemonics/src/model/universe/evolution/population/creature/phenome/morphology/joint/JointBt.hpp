#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_

//# corresponding header
//# forward declarations
class Motor;

//# system headers
//## controller headers
//## model headers
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

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
class JointBt: public JointPhysics {
public:
	JointBt();
	JointBt(const JointBt& jointBt);

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
		const btTransform& tframeInB, JointPhysics::JointType type,
		bool jointPitchEnabled, bool jointYawEnabled, bool jointRollEnabled,
		btVector3 jointPitchAxis, btVector3 jointLowerLimits,
		btVector3 jointUpperLimits);
	virtual ~JointBt();

	/**
	 * Initialize the rotational limit motors.
	 * @param maxForces The maximum forces of the joint.
	 * @param maxSpeeds The maximum speeds of the joint.
	 */
	void initializeRotationalLimitMotors(const btVector3 maxForces,
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

	/**
	 * Returns if the joint is under tension.
	 * @return If the joint is under tension.
	 */
	bool isStrained();

	/**
	 * Compare the joint bullet physics to another joint bullet physics.
	 * @param jointBt Another joint bullet physics model.
	 * @return If the joint bullet physics is equal to the other joint bullet physics.
	 */
	bool equals(const JointBt & jointBt) const;

	/**
	 * Clone the joint bt.
	 * @return The clone of the joint bt.
	 */
	virtual JointBt* clone();

	//Accessor methods

//	void setAngularLimits(const Ogre::Vector3 angularLowerLimit,
//			const Ogre::Vector3 angularUpperLimit) {
//		setAngularLimits(OgreBulletUtils::convert(angularLowerLimit),
//				OgreBulletUtils::convert(angularUpperLimit));
//	}
//
//	void setAngularLimits(const btVector3 angularLowerLimit,
//			const btVector3 angularUpperLimit) {
//
////		mG6DofJoint->setAngularLowerLimit(angularLowerLimit);
////		mG6DofJoint->setAngularUpperLimit(angularUpperLimit);
//	}

//	void setBreakingThreshold(const double breakingThreshold) {
//		mJoint->setBreakingImpulseThreshold(breakingThreshold);
//	}

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
		const JointBt & jointBt) {
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
		ar.register_type(static_cast<ServoMotor*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointPhysics) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mMotors); /**!< The motors of the joint bullet physics model*/
	}

private:

	/**
	 * The bullet dynamics world of the bullet physics engine. Reference only.
	 */
	btDynamicsWorld* mWorld;

	/**
	 * The vector of motors that are working across this joint.
	 * Be it servo motors acting directly on the DoF or be it muscles acting on attachment points on the limb.
	 */
	std::vector<Motor*> mMotors;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_ */
