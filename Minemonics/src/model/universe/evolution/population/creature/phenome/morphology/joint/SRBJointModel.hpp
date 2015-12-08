#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJointModel_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJointModel_HPP_

//# corresponding headers
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//# forward declarations
class SRBLimbModel;
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
#include <LinearMath/btVector3.h>
#include <OgreVector3.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>
#include <utils/logging/Logger.hpp>

/**
 * @brief		The joint model holds all the state information of the joint.
 * @details		Details
 * @date		2015-04-29
 * @author		Benjamin Ellenberger
 */
class SRBJointModel: public JointModel {
public:
	SRBJointModel();
	SRBJointModel(const SRBJointModel& SRBJointModel);
	SRBJointModel(const SRBJointModel* SRBJointModel);
	SRBJointModel(btDynamicsWorld* const world,
		SRBLimbModel* const limbA, SRBLimbModel* const limbB,
		const Ogre::Vector3 pivotInW, const std::vector<LimbModel*>::size_type indexA,
		const std::vector<LimbModel*>::size_type indexB,
		const std::vector<LimbModel*>::size_type ownIndex,
		JointPhysics::JointType type, Ogre::Vector3 jointPitchAxis,
		Ogre::Vector3 jointYawAxis, Ogre::Vector3 jointMinAngle,
		Ogre::Vector3 jointMaxAngle);

	virtual ~SRBJointModel();

	virtual void initialize();

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
	 * Compare the joint model to another joint model.
	 * @param SRBJointModel Another joint model.
	 * @return If the joint model is equal to the other joint model.
	 */
	bool equals(const SRBJointModel & SRBJointModel) const;

	/**
	 * Clone the joint model.
	 * @return The clone of the joint model.
	 */
	SRBJointModel* clone();

	// Accessor methods ##########################

	JointPhysics* const getJointPhysics() const {
		return mJointPhysics;
	}

	void setJointPhysics(JointPhysics* const jointPhysics) {
		mJointPhysics = jointPhysics;
	}

	void generateMotors(const Ogre::Vector3 maxForces,
		const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits,bool positionControlled);

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

	Ogre::Vector3 getLowerLimits() {
		return mJointPhysics->getJointMinAngle();
	}

	Ogre::Vector3 getUpperLimits() {
		return mJointPhysics->getJointMaxAngle();
	}

	const JointPhysics::JointType getType() const {
		return mJointPhysics->getType();
	}

	const btVector3 getJointPitchAxis() const {
		return OgreBulletUtils::convert(mJointPhysics->getJointPitchAxis());
	}

	void setBodyA(btRigidBody* bodyA) {
		((SRBJointBt*)mJointPhysics)->setBodyA(bodyA);
	}

	void setBodyB(btRigidBody* bodyB) {
		((SRBJointBt*)mJointPhysics)->setBodyB(bodyB);
	}

	void setFrameInA(const btTransform& frameInA) {
		((SRBJointBt*)mJointPhysics)->setFrameInA(frameInA);
	}

	void setFrameInB(const btTransform& frameInB) {
		((SRBJointBt*)mJointPhysics)->setFrameInB(frameInB);
	}

	void setWorld(btDynamicsWorld* world) {
		((SRBJointBt*)mJointPhysics)->setWorld(world);
	}

	// Serialization
	friend class boost::serialization::access; /**!< Give access to boost serialization .*/

	/**
	 * Serializes the joint model to a string.
	 * @param os The ostream.
	 * @param SRBjointModel The joint model we want to serialize.
	 * @return A string containing all information about the joint model.
	 */
	friend std::ostream & operator<<(std::ostream &os,
		const SRBJointModel &SRBJointModel) {
		return os;
//		/**The physics component of the joint model*/
//		<< "SRBJointModel: JointPhysics=(" << *SRBJointModel.mJointPhysics << ")";
	}

	/**
	 * Serializes the joint model to an xml file.
	 * @param ar The archive.
	 * @param The file version.
	 */
	template<class Archive>
	void serialize(Archive & ar, const unsigned int /* file_version */) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(JointModel); /**!< Serialize the base object */
	}

private:
	static BoostLogger mBoostLogger; /**!< The boost logger. */

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant < std::string > ("SRBJointModel"));
		}
	} _initializer;
};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_SRBJOINTMODEL_HPP_ */
