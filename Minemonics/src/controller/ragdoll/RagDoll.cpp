/*
 * Ragdoll.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

//# corresponding headers
//# forward declarations
//# system headers
#include <stddef.h>
#include <cmath>
#include <iterator>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <controller/ragdoll/RagDoll.hpp>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

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

RagDoll::RagDoll(Population* const population, double size,
		const btVector3& positionOffset) :
		Creature(population, OgreBulletUtils::convert(positionOffset), 0) {

	btTransform transform;
	btTransform localA, localB;

	LimbModel::PrimitiveType type = LimbModel::CAPSULE;

	bool enableMotor = false;
	int gapSize = size * 1.3f;

	// Setup the geometry
	// BODYPART_PELVIS
	//	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	Limb* limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.3, size * 0.2, size * 0.3), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	// BODYPART_SPINE
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.2),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.3, size * 0.28, size * 0.3), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//BODYPART_HEAD
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.6),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.2, size * 0.2, size * 0.2), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//BODYPART_LEFT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * -0.18), btScalar(gapSize * 0.65),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//	BODYPART_LEFT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * -0.18), btScalar(gapSize * 0.2),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//BODYPART_RIGHT_UPPER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.18), btScalar(gapSize * 0.65),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	// BODYPART_RIGHT_LOWER_LEG
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.18), btScalar(gapSize * 0.2),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	// BODYPART_LEFT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * -0.35), btScalar(gapSize * 1.45),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//BODYPART_LEFT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * -0.7), btScalar(gapSize * 1.45),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//BODYPART_RIGHT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.35), btScalar(gapSize * 1.45),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	// BODYPART_RIGHT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
			btVector3(btScalar(gapSize * 0.7), btScalar(gapSize * 1.45),
					btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new Limb();
	limb->initialize(this, type,
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			OgreBulletUtils::convert(transform.getOrigin()),
			OgreBulletUtils::convert(transform.getRotation()),
			Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), 1);
	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	std::vector<Limb*>::iterator it = mPhenotype.getLimbs().begin();
	for (; it != mPhenotype.getLimbs().end(); it++) {
		((LimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setDamping(0.05,
				0.85);
		((LimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setDeactivationTime(
				0.8);
		((LimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setSleepingThresholds(
				1.6, 2.5);
	}

////	 Now setup the constraints
	Joint* joint;

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.15),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.15),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_PELVIS],
			mPhenotype.getLimbs()[BODYPART_SPINE], localA, localB, 0, 0, 0);
	joint->setAngularLimits(Ogre::Vector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
			Ogre::Vector3(0.2 * M_PI, M_PI_2, M_PI_2));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_2);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.30),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_2);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.14),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_SPINE],
			mPhenotype.getLimbs()[BODYPART_HEAD], localA, localB, 0, 0, 0);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, -M_PI_2),
			Ogre::Vector3(M_PI_4, M_PI_4, M_PI_2));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_4);
	localA.setOrigin(
			btVector3(btScalar(gapSize * -0.18), btScalar(gapSize * -0.10),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_4);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.225),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_PELVIS],
			mPhenotype.getLimbs()[BODYPART_LEFT_UPPER_LEG], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, 0),
			Ogre::Vector3(M_PI_4, M_PI_4, 0));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.225),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.185),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_LEFT_UPPER_LEG],
			mPhenotype.getLimbs()[BODYPART_LEFT_LOWER_LEG], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(0, 0, M_PI_2));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI_4);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.18), btScalar(gapSize * -0.10),
					btScalar(size * 0.)));
	localB.getBasis().setEulerZYX(0, 0, M_PI_4);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.225),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_PELVIS],
			mPhenotype.getLimbs()[BODYPART_RIGHT_UPPER_LEG], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_4, -M_PI_4, 0),
			Ogre::Vector3(M_PI_4, M_PI_4, 0));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI_2, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.225),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI_2, 0);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.185),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_RIGHT_UPPER_LEG],
			mPhenotype.getLimbs()[BODYPART_RIGHT_LOWER_LEG], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(0, 0, M_PI_2));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(M_PI, 0, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * -0.2), btScalar(gapSize * 0.15),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, -M_PI_4);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_SPINE],
			mPhenotype.getLimbs()[BODYPART_LEFT_UPPER_ARM], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
			Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.18),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, 0);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.14),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_LEFT_UPPER_ARM],
			mPhenotype.getLimbs()[BODYPART_LEFT_LOWER_ARM], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(M_PI_2, 0, 0));
	joint->initializeRotationalLimitMotors(Ogre::Vector3(1, 1, 1),
			Ogre::Vector3(1000, 1000, 1000));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, M_PI);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.2), btScalar(gapSize * 0.15),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, -M_PI_4);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_SPINE],
			mPhenotype.getLimbs()[BODYPART_RIGHT_UPPER_ARM], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
			Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, 0, 0);
	localA.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 0.18),
					btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, 0, 0);
	localB.setOrigin(
			btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.14),
					btScalar(gapSize * 0.)));

	joint = new Joint(this, mPhenotype.getLimbs()[BODYPART_RIGHT_UPPER_ARM],
			mPhenotype.getLimbs()[BODYPART_RIGHT_LOWER_ARM], localA, localB, 0,
			0, 0);
	joint->setAngularLimits(Ogre::Vector3(0, 0, 0),
			Ogre::Vector3(M_PI_2, 0, 0));
	mCreatureModel->getPhenotypeModel().getJointModels().push_back(
			joint->getJointModel());
	mPhenotype.getJoints().push_back(joint);
	for (std::vector<Motor*>::const_iterator motorIterator =
			joint->getMotors().begin();
			motorIterator != joint->getMotors().end(); motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotype.getPhenotypeModel()->getControllers().push_back(controller);
	}
	mPhenotype.getPhenotypeModel()->getControllers().clear();
	mPhenotype.getPhenotypeModel()->setDeveloped(true);

}

RagDoll::~RagDoll() {

	// remove all constraints, bodies and shapes from world
	removeFromWorld();

	// delete all constraints
	for (int i = 0; i < JOINT_COUNT; ++i) {
		delete mPhenotype.getJoints()[i];
	}

	mPhenotype.getJoints().clear();

	// delete all bodies and shapes
	for (int i = 0; i < BODYPART_COUNT; ++i) {
		delete mPhenotype.getLimbs()[i];
	}

	mPhenotype.getLimbs().clear();
}

void RagDoll::update(double timeSinceLastTick) {
	Creature::update(timeSinceLastTick);
}

void RagDoll::addToWorld() {
	// Add all limbs
	std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
	for (; lit != mPhenotype.getLimbs().end(); lit++) {
		(*lit)->addToWorld();
	}

	// Add all constraints
	std::vector<Joint*>::iterator jit = mPhenotype.getJoints().begin();
	for (; jit != mPhenotype.getJoints().end(); jit++) {
		(*jit)->addToWorld();
	}

	mPhenotype.setInWorld(true);
}

void RagDoll::addToPhysicsWorld() {
	// Add all limbs
	std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
	for (; lit != mPhenotype.getLimbs().end(); lit++) {
		(*lit)->addToPhysicsWorld();
	}

	// Add all constraints
	std::vector<Joint*>::iterator jit = mPhenotype.getJoints().begin();
	for (; jit != mPhenotype.getJoints().end(); jit++) {
		(*jit)->addToPhysicsWorld();
	}

	mPhenotype.setInWorld(true);
}

void RagDoll::removeFromWorld() {
	// Remove all constraints
	std::vector<Joint*>::iterator jit = mPhenotype.getJoints().begin();
	for (; jit != mPhenotype.getJoints().end(); jit++) {
		(*jit)->removeFromWorld();
	}

	// Remove all limbs
	std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
	for (; lit != mPhenotype.getLimbs().end(); lit++) {
		(*lit)->removeFromWorld();
	}

	mPhenotype.setInWorld(false);
}

