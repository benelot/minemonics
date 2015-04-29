/*
 * Ragdoll.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <model/evolution/population/creature/phenome/morphology/limb/LimbBt.h>
#include <view/bullet/OgreBulletUtils.h>
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
#include "controller/evolution/population/creature/phenome/morphology/Joint.h"

//## model headers

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

	MorphologyConfiguration::PrimitiveType type =
			MorphologyConfiguration::CAPSULE;

	// Setup the geometry
	// BODYPART_PELVIS
	//	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	Limb* limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.3, size * 0.2, size * 0.3), 1);
	mLimbs.push_back(limb);

	// BODYPART_SPINE
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.2),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.3, size * 0.28, size * 0.3), 1);
	mLimbs.push_back(limb);

	//BODYPART_HEAD
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.), btScalar(size * 1.6),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.2, size * 0.2, size * 0.2), 1);
	mLimbs.push_back(limb);

	//BODYPART_LEFT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.18), btScalar(size * 0.65),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mLimbs.push_back(limb);

	//	BODYPART_LEFT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.18), btScalar(size * 0.2),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mLimbs.push_back(limb);

	//BODYPART_RIGHT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.18), btScalar(size * 0.65),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mLimbs.push_back(limb);

	// BODYPART_RIGHT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.18), btScalar(size * 0.2),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mLimbs.push_back(limb);

	// BODYPART_LEFT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.35), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mLimbs.push_back(limb);

	//BODYPART_LEFT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * -0.7), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mLimbs.push_back(limb);

	//BODYPART_RIGHT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.35), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mLimbs.push_back(limb);

	// BODYPART_RIGHT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(size * 0.7), btScalar(size * 1.45),
					btScalar(size * 0.)));
	transform.setOrigin(transform.getOrigin()+positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new Limb();
	limb->initialize(simulationManager, type,
			OgreBulletUtils::convert(transform.getOrigin()),
					OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mLimbs.push_back(limb);

	std::vector<Limb*>::iterator it = mLimbs.begin();
	for (; it != mLimbs.end(); it++) {
		(*it)->getLimbPhysics()->getRigidBody()->setDamping(0.05, 0.85);
		(*it)->getLimbPhysics()->getRigidBody()->setDeactivationTime(0.8);
		(*it)->getLimbPhysics()->getRigidBody()->setSleepingThresholds(1.6,
				2.5);
	}

////	 Now setup the constraints
	Joint* joint;

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_PELVIS],
			mLimbs[BODYPART_SPINE], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
			Ogre::Vector3(0.2 * M_PI, M_PI_2, M_PI_2));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_SPINE],
			mLimbs[BODYPART_HEAD], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, -M_PI_2),
			Ogre::Vector3(M_PI_4, M_PI_4, M_PI_2));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_PELVIS],
			mLimbs[BODYPART_LEFT_UPPER_LEG], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, 0),
			Ogre::Vector3(M_PI_4, M_PI_4, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_LEFT_UPPER_LEG],
			mLimbs[BODYPART_LEFT_LOWER_LEG], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(0, M_PI_2, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_PELVIS],
			mLimbs[BODYPART_RIGHT_UPPER_LEG], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, 0),
			Ogre::Vector3(M_PI_4, M_PI_4, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_RIGHT_UPPER_LEG],
			mLimbs[BODYPART_RIGHT_LOWER_LEG], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(0, M_PI_2, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_SPINE],
			mLimbs[BODYPART_LEFT_UPPER_ARM], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_2, -M_PI_2, 0),
			Ogre::Vector3(M_PI_2, M_PI_2, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_LEFT_UPPER_ARM],
			mLimbs[BODYPART_LEFT_LOWER_ARM], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(M_PI_2, 0, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_SPINE],
			mLimbs[BODYPART_RIGHT_UPPER_ARM], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_2, -M_PI_2, 0),
			Ogre::Vector3(M_PI_2, M_PI_2, 0));
	mJoints.push_back(joint);

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

	joint = new Joint();
	joint->initialize(simulationManager, mLimbs[BODYPART_RIGHT_UPPER_ARM],
			mLimbs[BODYPART_RIGHT_LOWER_ARM], localA, localB);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(M_PI_2, 0, 0));
	mJoints.push_back(joint);
}

RagDoll::~RagDoll() {

	// remove all constraints, bodies and shapes from world
	removeFromWorld();

	// delete all constraints
	for (int i = 0; i < JOINT_COUNT; ++i) {
		delete mJoints[i];
	}

	mJoints.clear();

	// delete all bodies and shapes
	for (int i = 0; i < BODYPART_COUNT; ++i) {
		delete mLimbs[i];
	}

	mLimbs.clear();
}

void RagDoll::update() {
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->update();
	}

	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->update();
	}
}

void RagDoll::addToWorld() {
	// Add all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->addToWorld();
	}

	// Add all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->addToWorld();
	}
}

void RagDoll::removeFromWorld() {
	// Remove all constraints
	std::vector<Joint*>::iterator jit = mJoints.begin();
	for (; jit != mJoints.end(); jit++) {
		(*jit)->removeFromWorld();
	}

	// Remove all limbs
	std::vector<Limb*>::iterator lit = mLimbs.begin();
	for (; lit != mLimbs.end(); lit++) {
		(*lit)->removeFromWorld();
	}
}

