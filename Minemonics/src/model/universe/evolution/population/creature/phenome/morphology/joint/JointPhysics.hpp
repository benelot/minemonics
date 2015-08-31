#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_

//# corresponding header
//# forward declarations
namespace boost {
namespace serialization {
class access;
} /* namespace serialization */
} /* namespace boost */

//# system headers
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//## view headers
//## utils headers

/**
 * @brief		The joint physics interface defines the methods defining a joint independent of the implementation.
 * @details		Details
 * @date		2015-04-14
 * @author		Benjamin Ellenberger
 */
class JointPhysics {
public:

	/**
	 * From btGeneric6DoFSpringJoint:
	 * /// 0 : translation X
	 * /// 1 : translation Y
	 * /// 2 : translation Z
	 * /// 3 : rotation X (3rd Euler rotational around new position of X axis, range [-PI+epsilon, PI-epsilon] )
	 * /// 4 : rotation Y (2nd Euler rotational around new position of Y axis, range [-PI/2+epsilon, PI/2-epsilon] )
	 * /// 5 : rotation Z (1st Euler rotational around Z axis, range [-PI+epsilon, PI-epsilon] )
	 */
	enum DegreeOfFreedom {
		DOF_TRANSLATION_X,
		DOF_TRANSLATION_Y,
		DOF_TRANSLATION_Z,
		DOF_ROLL,
		DOF_PITCH,
		DOF_YAW
	};

	enum RotationalDegreeOfFreedom {
		RDOF_ROLL, RDOF_PITCH, RDOF_YAW
	};

	enum JointType {
		UNKNOWN_JOINT, HINGE_JOINT, SPHERICAL_JOINT, NUM_JOINTS
	};

	JointPhysics();
	virtual ~JointPhysics();

	virtual JointPhysics* clone() = 0;

	/**
	 * Reset the joint to the place when the creature was born.
	 */
	virtual void reset(Ogre::Vector3 position) = 0;

	/**
	 * Reposition the joint without resetting it.
	 */
	virtual void reposition(const Ogre::Vector3 position) = 0;

	/**
	 * Update the joint physics model
	 */
	virtual void update(double timeSinceLastTick) = 0;

	/**
	 * If the joint physics is in the world.
	 * @return If it is in the world.
	 */
	virtual bool isInWorld() {
		return mInWorld;
	}

	/**
	 * Add the joint physics model to the physics world.
	 */
	virtual void addToWorld() {
		mInWorld = true;
	}

	/**
	 * Remove the joint physics model from the physics world.
	 */
	virtual void removeFromWorld() {
		mInWorld = false;
	}

	/**
	 * Returns if the joint is under tension.
	 * @return If the joint is under tension.
	 */
	virtual bool isStrained() = 0;

	//Accessor methods
	virtual const std::vector<Motor*>& getMotors() const = 0;

	virtual std::vector<Motor*>& getMotors() = 0;

	void setAngularLimits(const Ogre::Vector3 angularLowerLimit,
		const Ogre::Vector3 angularUpperLimit) {
		mJointPitchMinAngle = angularLowerLimit[RDOF_PITCH];
		mJointPitchMaxAngle = angularUpperLimit[RDOF_PITCH];
		mJointRollMinAngle = angularLowerLimit[RDOF_ROLL];
		mJointRollMaxAngle = angularUpperLimit[RDOF_ROLL];
		mJointYawMinAngle = angularLowerLimit[RDOF_YAW];
		mJointYawMaxAngle = angularUpperLimit[RDOF_YAW];
	}

	virtual void setRotationalLimitMotorEnabled(
		const RotationalDegreeOfFreedom index, const bool enable) = 0;

	double getJointPitchMaxAngle() const {
		return mJointPitchMaxAngle;
	}

	void setJointPitchMaxAngle(double jointPitchMaxAngle) {
		mJointPitchMaxAngle = jointPitchMaxAngle;
	}

	double getJointPitchMinAngle() const {
		return mJointPitchMinAngle;
	}

	void setJointPitchMinAngle(double jointPitchMinAngle) {
		mJointPitchMinAngle = jointPitchMinAngle;
	}

	double getJointRollMaxAngle() const {
		return mJointRollMaxAngle;
	}

	void setJointRollMaxAngle(double jointRollMaxAngle) {
		mJointRollMaxAngle = jointRollMaxAngle;
	}

	double getJointRollMinAngle() const {
		return mJointRollMinAngle;
	}

	void setJointRollMinAngle(double jointRollMinAngle) {
		mJointRollMinAngle = jointRollMinAngle;
	}

	double getJointYawMaxAngle() const {
		return mJointYawMaxAngle;
	}

	void setJointYawMaxAngle(double jointYawMaxAngle) {
		mJointYawMaxAngle = jointYawMaxAngle;
	}

	double getJointYawMinAngle() const {
		return mJointYawMinAngle;
	}

	void setJointYawMinAngle(double jointYawMinAngle) {
		mJointYawMinAngle = jointYawMinAngle;
	}

	//Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization */

	/**
	 * Serializes the joint physics model to a string.
	 * @param os The ostream.
	 * @param jointPhysics The joint physics model we want to serialize.
	 * @return A string containing all information about the joint physics model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const JointPhysics &jointPhysics) {
		os << "JointPhysics: inWorld=" << jointPhysics.mInWorld /**!< If the joint is in the world*/
		<< "JointPitchLimit=[" /**!< Joint Pitch limit */
		<< jointPhysics.mJointPitchMinAngle << ","
			<< jointPhysics.mJointPitchMaxAngle

			<< "]/JointYawLimit=[" /**!< Joint Yaw limit */
			<< jointPhysics.mJointYawMinAngle << ","
			<< jointPhysics.mJointYawMaxAngle

			<< "]/JointRollLimit=[" /**!< Joint Roll limit */
			<< jointPhysics.mJointRollMinAngle << ","
			<< jointPhysics.mJointRollMaxAngle << "]";
		return os;
	}

	bool isJointPitchEnabled() const {
		return mJointPitchEnabled;
	}

	void setJointPitchEnabled(bool jointPitchEnabled) {
		mJointPitchEnabled = jointPitchEnabled;
	}

	bool isJointRollEnabled() const {
		return mJointRollEnabled;
	}

	void setJointRollEnabled(bool jointRollEnabled) {
		mJointRollEnabled = jointRollEnabled;
	}

	bool isJointYawEnabled() const {
		return mJointYawEnabled;
	}

	void setJointYawEnabled(bool jointYawEnabled) {
		mJointYawEnabled = jointYawEnabled;
	}

	JointType getType() const {
		return mType;
	}

	void setType(JointType type) {
		mType = type;
	}

	double getJointPitchAxisX() const {
		return mJointPitchAxisX;
	}

	void setJointPitchAxisX(double jointPitchAxisX) {
		mJointPitchAxisX = jointPitchAxisX;
	}

	double getJointPitchAxisY() const {
		return mJointPitchAxisY;
	}

	void setJointPitchAxisY(double jointPitchAxisY) {
		mJointPitchAxisY = jointPitchAxisY;
	}

	double getJointPitchAxisZ() const {
		return mJointPitchAxisZ;
	}

	void setJointPitchAxisZ(double jointPitchAxisZ) {
		mJointPitchAxisZ = jointPitchAxisZ;
	}

	/**
	 * Serializes the joint physics model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_NVP(mType) /**!< The type of joint */
		& BOOST_SERIALIZATION_NVP(mJointPitchEnabled) /**!< If Joint Dof are enabled */
		& BOOST_SERIALIZATION_NVP(mJointYawEnabled)
			& BOOST_SERIALIZATION_NVP(mJointRollEnabled)

			& BOOST_SERIALIZATION_NVP(mJointPitchAxisX) /**!< The direction of the joint pitch axis */
			& BOOST_SERIALIZATION_NVP(mJointPitchAxisY)
			& BOOST_SERIALIZATION_NVP(mJointPitchAxisZ)

			& BOOST_SERIALIZATION_NVP(mJointPitchMinAngle) /**!< Joint Pitch limit */
			& BOOST_SERIALIZATION_NVP(mJointPitchMaxAngle)

			& BOOST_SERIALIZATION_NVP(mJointYawMinAngle) /**!< Joint Yaw limit */
			& BOOST_SERIALIZATION_NVP(mJointYawMaxAngle)

			& BOOST_SERIALIZATION_NVP(mJointRollMinAngle) /**!< Joint Roll limit */
			& BOOST_SERIALIZATION_NVP(mJointRollMaxAngle);
	}
protected:

	bool mJointPitchEnabled, mJointYawEnabled, mJointRollEnabled; /**!< If Joint Dof are enabled. */

	JointType mType; /**!< The type of joint */

	double mJointPitchAxisX, mJointPitchAxisY, mJointPitchAxisZ; /**!< The direction of the joint pitch axis*/
	double mJointPitchMaxAngle, mJointYawMaxAngle, mJointRollMaxAngle; /**!< Joint limits for each degree of freedom */
	double mJointPitchMinAngle, mJointYawMinAngle, mJointRollMinAngle;

	// should not be serialized
	bool mInWorld; /**!< If the joint physics is in the world or not. */
};
BOOST_CLASS_VERSION(JointPhysics, 1)
BOOST_SERIALIZATION_ASSUME_ABSTRACT(JointPhysics)
#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_ */
