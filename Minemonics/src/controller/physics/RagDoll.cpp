/*
 * Ragdoll.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "RagDoll.h"

//# forward declarations
//# system headers
#include <vector>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
#include "SimulationManager.h"

//## configuration headers
#include "configuration/MorphologyConfiguration.h"

//## controller headers
#include "controller/evolution/population/creature/phenome/morphology/Limb.h"
#include "controller/evolution/population/creature/phenome/morphology/joint/Joint.h"

//## model headers
#include "model/evolution/population/creature/phenome/morphology/LimbBt.h"
#include "model/evolution/population/creature/phenome/morphology/joint/JointBt.h"

//## view headers
//## utils headers

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2     1.57079632679489661923
#endif

#ifndef M_PI_4
#define M_PI_4     0.785398163397448309616
#endif

#ifndef CONSTRAINT_DEBUG_SIZE
#define CONSTRAINT_DEBUG_SIZE 0.2f
#endif

RagDoll::RagDoll(SimulationManager* simulationManager, double size,
		const btVector3& positionOffset) :
		mWorld(simulationManager->getPhysicsController().getDynamicsWorld()) {
	btTransform transform;
	btTransform localA, localB;

	btTransform offset;
	offset.setOrigin(positionOffset);

	MorphologyConfiguration::PrimitiveType type =
			MorphologyConfiguration::CAPSULE;
// Setup the geometry
// BODYPART_PELVIS
//	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.),
					btScalar(size * 0.)));
	transform = transform * offset;

	Limb* limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.3, size * 0.2, size * 0.3), 1);
	mLimbs.push_back(limb);

// BODYPART_SPINE
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.2),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.3, size * 0.28, size * 0.3), 1);
	mLimbs.push_back(limb);

//	BODYPART_HEAD
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.6),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.2, size * 0.2, size * 0.2), 1);
	mLimbs.push_back(limb);

//BODYPART_LEFT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.18), btScalar(size * 0.65),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mLimbs.push_back(limb);

//	BODYPART_LEFT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.18), btScalar(size * 0.2),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mLimbs.push_back(limb);

//BODYPART_RIGHT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.18), btScalar(size * 0.65),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mLimbs.push_back(limb);

// BODYPART_RIGHT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.18), btScalar(size * 0.2),
					btScalar(size * 0.)));
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mLimbs.push_back(limb);

// BODYPART_LEFT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.35), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mLimbs.push_back(limb);

//BODYPART_LEFT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.7), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mLimbs.push_back(limb);

//BODYPART_RIGHT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.35), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mLimbs.push_back(limb);

// BODYPART_RIGHT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.7), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);
	transform = transform * offset;

	limb = new Limb();
	limb->initialize(simulationManager, type,
			Ogre::Vector3(transform.getOrigin().x(), transform.getOrigin().y(),
					transform.getOrigin().z()),
			Ogre::Quaternion(transform.getRotation().w(),
					transform.getRotation().x(), transform.getRotation().y(),
					transform.getRotation().z()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mLimbs.push_back(limb);

	std::vector<Limb*>::iterator it = mLimbs.begin();
	for (; it != mLimbs.end(); it++) {
		(*it)->getLimbPhysics()->getRigidBody()->setDamping(0.05, 0.85);
		(*it)->getLimbPhysics()->getRigidBody()->setDeactivationTime(0.8);
		(*it)->getLimbPhysics()->getRigidBody()->setSleepingThresholds(1.6,
				2.5);
		mWorld->addRigidBody((*it)->getLimbPhysics()->getRigidBody());
	}

////	 Now setup the constraints
	JointBt* joint;

//	btTransform localA, localB;

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.15),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.15),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_PELVIS]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_SPINE]->getLimbPhysics()->getRigidBody(), localA,
			localB);
	joint->setAngularLimits(btVector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
			btVector3(0.2 * M_PI, M_PI_2, M_PI_2));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_2);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.30),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_2);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.14),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_SPINE]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_HEAD]->getLimbPhysics()->getRigidBody(), localA,
			localB);
	joint->setAngularLimits(btVector3(-M_PI_4, -M_PI_4, -M_PI_2),
			btVector3(M_PI_4, M_PI_4, M_PI_2));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, -M_PI_4 * 5);
	localA.setOrigin(
			btVector3(btScalar(size * -0.18), btScalar(size * -0.10),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, -M_PI_4 * 5);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.225),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_PELVIS]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_LEFT_UPPER_LEG]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(-M_PI_4, -M_PI_4, 0),
			btVector3(M_PI_4, M_PI_4, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.225),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.185),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(
			mLimbs[BODYPART_LEFT_UPPER_LEG]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_LEFT_LOWER_LEG]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(0, 0, 0), btVector3(0, M_PI_2, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_4);
	localA.setOrigin(
			btVector3(btScalar(size * 0.18), btScalar(size * -0.10),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_4);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.225),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_PELVIS]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_RIGHT_UPPER_LEG]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(-M_PI_4, -M_PI_4, 0),
			btVector3(M_PI_4, M_PI_4, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.225),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.185),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(
			mLimbs[BODYPART_RIGHT_UPPER_LEG]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_RIGHT_LOWER_LEG]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(0, 0, 0), btVector3(0, M_PI_2, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI);
	localA.setOrigin(
			btVector3(btScalar(size * -0.2), btScalar(size * 0.15),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_2);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.18),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_SPINE]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_LEFT_UPPER_ARM]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(-M_PI_2, -M_PI_2, 0),
			btVector3(M_PI_2, M_PI_2, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.18),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.14),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(
			mLimbs[BODYPART_LEFT_UPPER_ARM]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_LEFT_LOWER_ARM]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(0, 0, 0), btVector3(M_PI_2, 0, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.2), btScalar(size * 0.15),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_2);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.18),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(mLimbs[BODYPART_SPINE]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_RIGHT_UPPER_ARM]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(-M_PI_2, -M_PI_2, 0),
			btVector3(M_PI_2, M_PI_2, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 0.18),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * -0.14),
					btScalar(size * 0.)));

	joint = new JointBt();
	joint->initialize(
			mLimbs[BODYPART_RIGHT_UPPER_ARM]->getLimbPhysics()->getRigidBody(),
			mLimbs[BODYPART_RIGHT_LOWER_ARM]->getLimbPhysics()->getRigidBody(),
			localA, localB);
	joint->setAngularLimits(btVector3(0, 0, 0), btVector3(M_PI_2, 0, 0));
	mJoints.push_back(joint);

	mWorld->addConstraint((btTypedConstraint*) joint->getG6DofJoint(), true);
}

RagDoll::~RagDoll() {
	int i;

	// Remove all constraints
	for (i = 0; i < JOINT_COUNT; ++i) {
		mWorld->removeConstraint(
				(btTypedConstraint*) mJoints[i]->getG6DofJoint());
		delete mJoints[i];
	}

	mJoints.clear();

	// Remove all bodies and shapes
	for (i = 0; i < BODYPART_COUNT; ++i) {
		mWorld->removeRigidBody(mLimbs[i]->getLimbPhysics()->getRigidBody());

		delete mLimbs[i];
	}
}

void RagDoll::update() {
	std::vector<Limb*>::iterator it = mLimbs.begin();
	for (; it != mLimbs.end(); it++) {
		(*it)->update();
	}
}

