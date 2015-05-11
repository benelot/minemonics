#ifndef MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_
#define MODEL_UNIVERSE_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_HPP_

//# corresponding header
//# forward declarations
class Motor;

//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

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
	virtual ~JointBt();

	void initialize(btDynamicsWorld* world, btRigidBody* bodyA,
			btRigidBody* bodyB, btTransform& tframeInA, btTransform& tframeInB);

	void initializeRotationalLimitMotors(btVector3 maxForces,
			btVector3 maxSpeeds);

	void update();

	void addToWorld();

	void removeFromWorld();

	void setLinearLimits(btVector3 linearLowerLimit,
			btVector3 linearUpperLimit) {
		mG6DofJoint->setLinearLowerLimit(linearLowerLimit);
		mG6DofJoint->setLinearUpperLimit(linearUpperLimit);

	}

	void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit) {
		setAngularLimits(OgreBulletUtils::convert(angularLowerLimit),
				OgreBulletUtils::convert(angularUpperLimit));
	}

	void setAngularLimits(btVector3 angularLowerLimit,
			btVector3 angularUpperLimit) {

		mG6DofJoint->setAngularLowerLimit(angularLowerLimit);
		mG6DofJoint->setAngularUpperLimit(angularUpperLimit);
	}

	void setAngularStiffness(double jointPitchStiffness,
			double jointYawStiffness, double jointRollStiffness) {
		setJointStiffness(0, jointPitchStiffness);
		setJointStiffness(1, jointYawStiffness);
		setJointStiffness(2, jointRollStiffness);
	}

	void setAngularDamping(double springPitchDampingCoefficient,
			double springYawDampingCoefficient,
			double springRollDampingCoefficient) {
		setSpringDampingCoefficient(0, springPitchDampingCoefficient);
		setSpringDampingCoefficient(1, springYawDampingCoefficient);
		setSpringDampingCoefficient(2, springRollDampingCoefficient);
	}

	void setBreakingThreshold(double breakingThreshold) {
		mG6DofJoint->setBreakingImpulseThreshold(breakingThreshold);
	}

	void setJointStiffness(int index, double stiffness) {
		mG6DofJoint->setStiffness(index, stiffness);
	}

	void enableSpring(int index, bool enable) {
		mG6DofJoint->enableSpring(index, enable);
	}

	void setSpringDampingCoefficient(int index, double damping) {
		mG6DofJoint->setDamping(index, damping);
	}

	void setRotationalLimitMotorEnabled(int index, bool enable);

	bool isRotationalLimitMotorEnabled(int index) {
		return mG6DofJoint->getRotationalLimitMotor(index)->m_enableMotor;
	}

	void setTargetRotationalVelocity(int index, double targetVelocity) {
		mG6DofJoint->getRotationalLimitMotor(index)->m_targetVelocity =
				targetVelocity;
	}

	double getTargetRotationalVelocity(int index) {
		return mG6DofJoint->getRotationalLimitMotor(index)->m_targetVelocity;
	}

	void setMaxRotationalForce(int index, double maxMotorForce) {
		mG6DofJoint->getRotationalLimitMotor(index)->m_maxMotorForce =
				maxMotorForce;
	}

	double getMaxRotationalForce(int index) {
		return mG6DofJoint->getRotationalLimitMotor(index)->m_maxMotorForce;
	}

	btGeneric6DofSpringConstraint* getG6DofJoint() {
		return mG6DofJoint;
	}

	std::vector<Motor*> getMotors() {
		return mMotors;
	}

private:
	/**
	 * The 6 Degrees of freedom joint that is used as a physical model.
	 */
	btGeneric6DofSpringConstraint* mG6DofJoint;

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
