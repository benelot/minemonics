#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_

//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//# forward declarations
class btDynamicsWorld;
class btRigidBody;
class btMultiBody;
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
#include <boost/serialization/vector.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <LinearMath/btTransform.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>

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
	JointModel(const JointModel* jointModel);

	virtual ~JointModel();

	void initialize(btDynamicsWorld* const world, btRigidBody* const limbA,
		btRigidBody* const limbB, const btTransform localA,
		const btTransform localB,
		const std::vector<LimbModel*>::size_type indexA,
		const std::vector<LimbModel*>::size_type indexB,
		const std::vector<JointModel*>::size_type ownIndex,
		JointPhysics::JointType type, bool jointPitchEnabled,
		bool jointYawEnabled, bool jointRollEnabled,
		Ogre::Vector3 jointPitchAxis, Ogre::Vector3 jointLowerLimits,
		Ogre::Vector3 jointUpperLimits);

	/**
	 * Update the joint model.
	 * @param timeSinceLastTick
	 */
	void update(double timeSinceLastTick);

	/**
	 * Reset the joint to the place when the creature was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the joint without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Returns if the joint is under tension.
	 * @return If the joint is under tension.
	 */
	bool isStrained();

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

	//Accessor methods

	JointPhysics* const getJointPhysics() const {
		return mJointPhysics;
	}

	void setJointPhysics(JointPhysics* const jointPhysics) {
		mJointPhysics = jointPhysics;
	}

	void generateMotors(const Ogre::Vector3 maxForces,
		const Ogre::Vector3 maxSpeeds);

	/**
	 * Set the angular limits for pitch, yaw and roll.
	 * @param angularLowerLimit Lower angular limits.
	 * @param angularUpperLimit Upper angular limits.
	 */
	void setAngularLimits(const Ogre::Vector3 angularLowerLimit,
		const Ogre::Vector3 angularUpperLimit);

	/**
	 * Set angular joint stiffness.
	 * @param jointPitchStiffness Joint stiffness in pitch direction.
	 * @param jointYawStiffness Joint stiffness in yaw direction.
	 * @param jointRollStiffness Joint stiffness in roll direction.
	 */
	void setAngularStiffness(const double jointPitchStiffness,
		const double jointYawStiffness, const double jointRollStiffness);

	/**
	 * Set the spring damping coefficients.
	 * @param springPitchDampingCoefficient Damping coefficient of the spring in pitch direction.
	 * @param springYawDampingCoefficient Damping coefficient of the spring in yaw direction.
	 * @param springRollDampingCoefficient Damping coefficient of the spring in roll direction.
	 */
	void setAngularDamping(const double springPitchDampingCoefficient,
		const double springYawDampingCoefficient,
		const double springRollDampingCoefficient);

	/**
	 * Enable angular motors.
	 * @param pitchEnable Enable pitch motor.
	 * @param yawEnable Enable yaw motor.
	 * @param rollEnable Enable roll motor.
	 */
	void enableAngularMotor(const bool pitchEnable, const bool yawEnable,
		const bool rollEnable);

	/**
	 * Get the motors of this joint.
	 * @return The motors of this joint.
	 */
	const std::vector<Motor*>& getMotors() const {
		return mJointPhysics->getMotors();
	}

	std::vector<Motor*>& getMotors() {
		return mJointPhysics->getMotors();
	}

	const std::vector<LimbModel*>::size_type getParentIndex() const {
		return mParentIndex;
	}

	const std::vector<LimbModel*>::size_type getChildIndex() const {
		return mChildIndex;
	}

	const btTransform& getParentComToPivot() const {
		return mLocalA;
	}

	void setLocalA(const btTransform& localA) {
		mLocalA = localA;
	}

	const btTransform& getPivotToChildCom() const {
		return mLocalB;
	}

	void setLocalB(const btTransform& localB) {
		mLocalB = localB;
	}

	Ogre::Vector3 getLowerLimits() {
		return mJointPhysics->getJointMinAngle();
	}

	Ogre::Vector3 getUpperLimits() {
		return mJointPhysics->getJointMaxAngle();
	}

	const bool getJointPitchEnabled() const {
		return mJointPhysics->isJointPitchEnabled();
	}

	const bool getJointYawEnabled() const {
		return mJointPhysics->isJointYawEnabled();
	}

	const bool getJointRollEnabled() const {
		return mJointPhysics->isJointRollEnabled();
	}

	const JointPhysics::JointType getType() const {
		return mJointPhysics->getType();
	}

	const btVector3 getJointPitchAxis() const {
		return OgreBulletUtils::convert(mJointPhysics->getJointPitchAxis());
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization .*/

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
	 * Serializes the joint model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar.register_type(static_cast<JointBt*>(NULL));
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ComponentModel) /**!< Serialize the base object */
		& BOOST_SERIALIZATION_NVP(mJointPhysics) /**!< The physics component of the joint model*/
		& BOOST_SERIALIZATION_NVP(mOwnIndex) /**!< The joint's own index */
		& BOOST_SERIALIZATION_NVP(mParentIndex) /**!< The joint's parent limb index */
		& BOOST_SERIALIZATION_NVP(mChildIndex) /**!< The joint's child limb index */
		& BOOST_SERIALIZATION_NVP(mAngleceptors) /**!< The angle measuring sensors of the joint */
		& BOOST_SERIALIZATION_NVP(mForceceptors) /**!< The force measuring sensors of the joint */
		& BOOST_SERIALIZATION_NVP(mLimitceptors); /**!< The limit measuring sensors of the joint */
	}

private:

	/**
	 * The indices of limbA and limbB.
	 */
	std::vector<LimbModel*>::size_type mParentIndex, mChildIndex;

	btTransform mLocalA, mLocalB;

	/**
	 * The joint's own index.
	 */
	std::vector<JointModel*>::size_type mOwnIndex;

	/**
	 * The physical model representation of the joint.
	 */
	JointPhysics* mJointPhysics;

	/**
	 * All the sensors of the joint.
	 */
	std::vector<Sensor*> mSensors;

	/**
	 * The angleceptors of the joint.
	 */
	std::vector<JointAngleceptor*> mAngleceptors;

	/**
	 * The forceceptors of the joint.
	 */
	std::vector<JointForceceptor*> mForceceptors;

	/**
	 * The limitceptors of the joint.
	 */
	std::vector<JointLimitceptor*> mLimitceptors;

};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_ */
