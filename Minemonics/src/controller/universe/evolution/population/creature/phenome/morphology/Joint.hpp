#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_

//# corresponding header
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//# forward declarations
class btTransform;
class Creature;
class JointGraphics;
class Limb;
class Motor;
class JointModel;

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//## view headers

//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The joint controller synchronizes the joint graphical representation with the joint model.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Joint: public Component {
public:
	Joint(Creature* const creature, Limb* const limbA, Limb* const limbB,
		const Ogre::Vector3 pivotInW, const int indexA, const int indexB,
		const int ownIndex, JointPhysics::JointType jointType,
		Ogre::Vector3 jointPitchAxis, Ogre::Vector3 jointYawAxis,
		Ogre::Vector3 jointLowerLimits, Ogre::Vector3 jointUpperLimits);
	Joint(const Joint& joint);
	Joint(const JointModel& jointModel);
	Joint(JointModel* const jointModel);
	virtual ~Joint();

	/**
	 * Initialize the joint by adding the joining limbs and the rotation point of the joint in both their local reference frames.
	 * @param creature The creature the joint belongs to.
	 * @param limbA Limb A
	 * @param limbB Limb B
	 * @param localA Local reference frame of limb A.
	 * @param localB Local reference frame of limb B.
	 */
	void initialize(Creature* const creature, Limb* const limbA,
		Limb* const limbB, const btTransform localA, const btTransform localB,
		const int indexA = 0, const int indexB = 0, const int ownIndex = 0);

	/**
	 * Clone the joint.
	 * @return The clone of the joint.
	 */
	Joint* clone();

	/**
	 * Reset the creature to the way it was born.
	 */
	void reset(const Ogre::Vector3 position);

	/**
	 * Reposition the creature without resetting it.
	 */
	void reposition(const Ogre::Vector3 position);

	/**
	 * Initialize the rotational limit motors of the joint.
	 * @param maxForces The maximum forces along the axes.
	 */
	void generateMotors(const Ogre::Vector3 maxForces,
		const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits,bool positionControlled);

	/**
	 * Updates the joint position and orientation.
	 */
	void update(double timeSinceLastTick);

	/**
	 * Add the joint to the graphical and model world.
	 */
	void addToWorld();

	/**
	 * Add the joint to the physics world only.
	 */
	void addToPhysicsWorld();

	/**
	 * Remove the joint from the graphical and model world.
	 */
	void removeFromWorld();

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

	// Accessor methods ##########################

	JointGraphics* const getJointGraphics() const {
		return mJointGraphics;
	}

	JointPhysics* const getJointPhysics() const;

	/**
	 * Get the motors of this joint.
	 * @return The motors of this joint.
	 */
	const std::vector<Motor*>& getMotors() const;

	JointModel* getJointModel() {
		return mJointModel;
	}

	const JointModel* getJointModel() const {
		return mJointModel;
	}

private:
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
				boost::log::attributes::constant<std::string>("Joint"));
		}
	} _initializer;
	/**
	 * Graphical representation of the joint.
	 */
	JointGraphics* mJointGraphics;

	/**
	 * Model representation of the joint.
	 */
	JointModel* mJointModel;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_ */
