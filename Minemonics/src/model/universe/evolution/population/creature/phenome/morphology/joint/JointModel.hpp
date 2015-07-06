#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//# forward declarations
class btDynamicsWorld;
class btRigidBody;
class btTransform;

//# system headers
#include <vector>

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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//## view headers
//## utils headers

/**
 * @brief		The joint model holds all the state information of the joint.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class JointModel: public ComponentModel {
public:
	JointModel();
	JointModel(const JointModel& jointModel);

	virtual ~JointModel();

	void initialize(btDynamicsWorld* world, btRigidBody* limbA,
			btRigidBody* limbB, btTransform localA, btTransform localB);

	/**
	 * Reset the joint to the place when the creature was born.
	 */
	void reset(Ogre::Vector3 position);

	/**
	 * Reposition the joint without resetting it.
	 */
	void reposition(Ogre::Vector3 position);

	/**
	 * Compare the joint model to another joint model.
	 * @param jointModel Another joint model.
	 * @return If the joint model is equal to the other joint model.
	 */
	bool equals(const JointModel & jointModel) const;

	/**
	 * Clone the joint model.
	 * @return The clone of the joint model.
	 */
	JointModel* clone();

	/**
	 * Give access to boost serialization
	 */
	friend class boost::serialization::access;

	/**
	 * Serializes the joint model to a string.
	 * @param os The ostream.
	 * @param jointModel The joint model we want to serialize.
	 * @return A string containing all information about the joint model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
			const JointModel &jointModel) {
		return os;
//		/**The physics component of the joint model*/
//		<< "JointModel: JointPhysics=(" << *jointModel.mJointPhysics << ")";
	}

	/**
	 * Serializes the creature to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar
		/**The physics component of the joint model*/
		& BOOST_SERIALIZATION_NVP(mJointPhysics);
	}

	//Accessor methods

	JointPhysics* getJointPhysics() {
		return mJointPhysics;
	}

	void setJointPhysics(JointPhysics* jointPhysics) {
		mJointPhysics = jointPhysics;
	}

	void initializeRotationalLimitMotors(Ogre::Vector3 maxForces,
			Ogre::Vector3 maxSpeeds);

	/**
	 * Set the angular limits for pitch, yaw and roll.
	 * @param angularLowerLimit Lower angular limits.
	 * @param angularUpperLimit Upper angular limits.
	 */
	void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit);

	/**
	 * Set angular joint stiffness.
	 * @param jointPitchStiffness Joint stiffness in pitch direction.
	 * @param jointYawStiffness Joint stiffness in yaw direction.
	 * @param jointRollStiffness Joint stiffness in roll direction.
	 */
	void setAngularStiffness(double jointPitchStiffness,
			double jointYawStiffness, double jointRollStiffness);

	/**
	 * Set the spring damping coefficients.
	 * @param springPitchDampingCoefficient Damping coefficient of the spring in pitch direction.
	 * @param springYawDampingCoefficient Damping coefficient of the spring in yaw direction.
	 * @param springRollDampingCoefficient Damping coefficient of the spring in roll direction.
	 */
	void setAngularDamping(double springPitchDampingCoefficient,
			double springYawDampingCoefficient,
			double springRollDampingCoefficient);

	/**
	 * Enable angular motors.
	 * @param pitchEnable Enable pitch motor.
	 * @param yawEnable Enable yaw motor.
	 * @param rollEnable Enable roll motor.
	 */
	void enableAngularMotor(bool pitchEnable, bool yawEnable, bool rollEnable);

	/**
	 * Get the motors of this joint.
	 * @return The motors of this joint.
	 */
	const std::vector<Motor*> getMotors() {
		return mJointPhysics->getMotors();
	}

private:
	/**
	 * The physical model representation of the joint.
	 */
	JointPhysics* mJointPhysics;

};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_ */
