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
	virtual ~JointModel();

	void initialize(btDynamicsWorld* world, btRigidBody* limbA,
			btRigidBody* limbB, btTransform localA, btTransform localB);

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
	const std::vector<Motor*> getMotors(){
		return mJointPhysics->getMotors();
	}

private:
	JointPhysics* mJointPhysics;


};

#endif /* MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTMODEL_HPP_ */
