/*
 * JointBt.h
 *
 *  Created on: Mar 25, 2015
 *      Author: leviathan
 */

#ifndef MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_H_
#define MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_H_

//# corresponding header
//# forward declarations
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
#include "model/evolution/population/creature/phenome/morphology/JointPhysics.h"

//## view headers
//## utils headers

class JointBt: public JointPhysics {
public:
	JointBt();
	virtual ~JointBt();

	void initialize(btDynamicsWorld* world,btRigidBody* bodyA, btRigidBody* bodyB, btVector3 frameInA,
			btVector3 frameInB);

	void initialize(btDynamicsWorld* world,btRigidBody* bodyA, btRigidBody* bodyB,
			btTransform& tframeInA, btTransform& tframeInB);

	void addToWorld();

	void removeFromWorld();

	void setLinearLimits(btVector3 linearLowerLimit,
			btVector3 linearUpperLimit) {
		mG6DofJoint->setLinearLowerLimit(linearLowerLimit);
		mG6DofJoint->setLinearUpperLimit(linearUpperLimit);

	}

	void setAngularLimits(Ogre::Vector3 angularLowerLimit,
			Ogre::Vector3 angularUpperLimit) {
		setAngularLimits(
				btVector3(angularLowerLimit.x, angularLowerLimit.y,
						angularLowerLimit.z),
				btVector3(angularUpperLimit.x, angularUpperLimit.y,
						angularUpperLimit.z));
	}

	void setAngularLimits(btVector3 angularLowerLimit,
			btVector3 angularUpperLimit) {

		mG6DofJoint->setAngularLowerLimit(angularLowerLimit);
		mG6DofJoint->setAngularUpperLimit(angularUpperLimit);
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

	void setDamping(int index, double damping) {
		mG6DofJoint->setDamping(index, damping);
	}

	void setRotationalLimitMotorEnabled(int index, bool enable) {
		mG6DofJoint->getRotationalLimitMotor(index)->m_enableMotor = enable;
	}

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

private:
	btGeneric6DofSpringConstraint* mG6DofJoint;
	btDynamicsWorld* mWorld;
};

#endif /* MODEL_EVOLUTION_POPULATION_CREATURE_PHENOME_MORPHOLOGY_JOINT_JOINTBT_H_ */
