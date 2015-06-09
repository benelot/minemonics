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

	/**
	 * Update the joint physics model
	 */
	virtual void update() = 0;

	/**
	 * Add the joint physics model to the physics world.
	 */
	virtual void addToWorld() = 0;

	/**
	 * Remove the joint physics model from the physics world.
	 */
	virtual void removeFromWorld() = 0;

//	/**
//	 * Compare the joint physics model to another joint physics model.
//	 * @param jointPhysics Another joint physics model.
//	 * @return If the joint physics model is equal to the other joint physics model.
//	 */
//	virtual bool equals(const JointPhysics & jointPhysics) const = 0;

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

	//Accessor methods
	virtual std::vector<Motor*> getMotors() = 0;

	virtual void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit) = 0;

	virtual void setAngularStiffness(double jointPitchStiffness,
			double jointYawStiffness, double jointRollStiffness) = 0;

	virtual void setAngularDamping(double springPitchDampingCoefficient,
			double springYawDampingCoefficient,
			double springRollDampingCoefficient) = 0;

	virtual void setRotationalLimitMotorEnabled(RotationalDegreeOfFreedom index,
			bool enable) = 0;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTPHYSICS_HPP_ */
