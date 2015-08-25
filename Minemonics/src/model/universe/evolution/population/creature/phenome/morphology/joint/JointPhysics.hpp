#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
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
	virtual bool isInWorld(){
		return mInWorld;
	}

	/**
	 * Add the joint physics model to the physics world.
	 */
	virtual void addToWorld(){
		mInWorld = true;
	}

	/**
	 * Remove the joint physics model from the physics world.
	 */
	virtual void removeFromWorld(){
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

	virtual void setRotationalLimitMotorEnabled(const RotationalDegreeOfFreedom index,
			const bool enable) = 0;

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

	//TODO: Add serialization to the joint physics
	//Serialization

	/**
	 * Give access to boost serialization
	 */
//	friend class boost::serialization::access;

//	/**
//	 * Serializes the joint physics model to a string.
//	 * @param os The ostream.
//	 * @param jointPhysics The joint physics model we want to serialize.
//	 * @return A string containing all information about the joint physics model.
//	 */
//	virtual friend std::ostream & operator<<(std::ostream &os,
//			const JointPhysics & jointPhysics) = 0;
//
//	/**
//	 * Serializes the creature to an xml file.
//	 * @param ar The archive.
//	 * @param The file version.
//	 */
//	template<class Archive>
//	virtual void serialize(Archive & ar, const unsigned int /* file_version */) = 0;
protected:
	bool mInWorld;

	/**
	 * Joint limits for each degree of freedom
	 */
	double mJointPitchMaxAngle, mJointYawMaxAngle, mJointRollMaxAngle;
	double mJointPitchMinAngle, mJointYawMinAngle, mJointRollMinAngle;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_ */
