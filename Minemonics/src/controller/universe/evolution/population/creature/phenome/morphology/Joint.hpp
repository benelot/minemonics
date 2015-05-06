#ifndef CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_
#define CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_

//# corresponding header
#include <controller/universe/evolution/population/creature/phenome/Component.hpp>

//# forward declarations
class SimulationManager;
class Limb;
class btTransform;
class btVector3;
class JointGraphics;

//# system headers
#include <vector>
//## controller headers
//## model headers
#include <bullet/LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//## view headers
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointGraphics.hpp>

//## utils headers

/**
 * @brief		The joint controller synchronizes the joint graphical representation with the joint model.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class Joint: public Component {
public:
	Joint();
	virtual ~Joint();

	/**
	 * Initialize the joint by adding the joining limbs and the rotation point of the joint in both their local reference frames.
	 * @param simulationManager The simulation manager of this application.
	 * @param limbA Limb A
	 * @param limbB Limb B
	 * @param localA Local reference frame of limb A.
	 * @param localB Local reference frame of limb B.
	 */
	void initialize(SimulationManager* simulationManager, Limb* limbA,
			Limb* limbB, btTransform localA, btTransform localB);

	void initializeRotationalLimitMotors(btVector3 maxForces, btVector3 maxSpeeds);

	/**
	 * Updates the joint position and orientation.
	 */
	void update();

	/**
	 * Add the joint to the graphical and model world.
	 */
	void addToWorld();

	/**
	 * Remove the joint from the graphical and model world.
	 */
	void removeFromWorld();

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
	std::vector<Motor*> getMotors(){
		return mJointPhysics->getMotors();
	}


	// Accessor methods

	JointGraphics*& getJointGraphics() {
		return mJointGraphics;
	}

	JointPhysics*& getJointPhysics() {
		return mJointPhysics;
	}

private:
	/**
	 * Graphical representation of the joint.
	 */
	JointGraphics* mJointGraphics;

	/**
	 * Physics model representation of the joint.
	 */
	JointPhysics* mJointPhysics;
};

#endif /* CONTROLLER_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_HPP_ */
