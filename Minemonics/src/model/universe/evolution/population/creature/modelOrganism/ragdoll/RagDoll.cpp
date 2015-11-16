//# corresponding headers
#include <stddef.h>
#include <cmath>
#include <iterator>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
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
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/ragdoll/RagDoll.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbBt.hpp>
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

RagDoll::RagDoll(PopulationModel* const population, double size,
	const btVector3& positionOffset) :
	CreatureModel(population, PhysicsController::RigidbodyModel,
		OgreBulletUtils::convert(positionOffset), 0) {

	btTransform transform;
	btTransform localA, localB;

	LimbPhysics::PrimitiveType type = LimbPhysics::CAPSULE;

	bool attachHead = false;
	bool enableMotor = true;
	int gapSize = size * 1.0f;

	// Setup the geometry
	// BODYPART_ABDOMENPELVIS
	//	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	LimbModel* limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.3, size * 0.2, size * 0.3),
		RAGDOLL_ABDOMENPELVIS);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	// BODYPART_THORAX
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.2),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.3, size * 0.28, size * 0.3), RAGDOLL_THORAX);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//BODYPART_HEAD
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.), btScalar(gapSize * 1.6),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.2, size * 0.2, size * 0.2),
		(attachHead) ? 0 : RAGDOLL_HEAD);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//BODYPART_LEFT_THIGH
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * -0.18), btScalar(gapSize * 0.65),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), RAGDOLL_THIGH);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//	BODYPART_LEFTLEG
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * -0.18), btScalar(gapSize * 0.2),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), RAGDOLL_LEG);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//BODYPART_RIGHT_THIGH
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.18), btScalar(gapSize * 0.65),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.14, size * 0.45, size * 0.14), RAGDOLL_THIGH);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	// BODYPART_RIGHT_LEG
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.18), btScalar(gapSize * 0.2),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.1, size * 0.37, size * 0.1), RAGDOLL_LEG);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	// BODYPART_LEFT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * -0.35), btScalar(gapSize * 1.45),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), RAGDOLL_UPPER_ARM);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//BODYPART_LEFT_FOREARM
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * -0.7), btScalar(gapSize * 1.45),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, M_PI_2);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), RAGDOLL_FOREARM);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	//BODYPART_RIGHT_UPPER_ARM
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.35), btScalar(gapSize * 1.45),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.1, size * 0.33, size * 0.1), RAGDOLL_UPPER_ARM);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	// BODYPART_RIGHT_LOWER_ARM
	transform.setIdentity();
	transform.setOrigin(
		btVector3(btScalar(gapSize * 0.7), btScalar(gapSize * 1.45),
			btScalar(gapSize * 0.)));
	transform.setOrigin(transform.getOrigin() + positionOffset);
	transform.getBasis().setEulerZYX(0, 0, -M_PI_2);

	limb = new SRBLimbModel();
	limb->initialize(this, type,
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		OgreBulletUtils::convert(transform.getOrigin()),
		OgreBulletUtils::convert(transform.getRotation()),
		Ogre::Vector3(size * 0.08, size * 0.25, size * 0.08), RAGDOLL_FOREARM);
//	((LimbBt*)limb->getLimbPhysics())->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
	mPhenotypeModel->getLimbModels().push_back(limb);

	std::vector<LimbModel*>::iterator it =
		mPhenotypeModel->getLimbModels().begin();
	for (; it != mPhenotypeModel->getLimbModels().end(); it++) {
		((SRBLimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setDamping(0.05,
			0.85);
		((SRBLimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setDeactivationTime(
			0.8);
		((SRBLimbBt*) (*it)->getLimbPhysics())->getRigidBody()->setSleepingThresholds(
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

	joint = new SRBJointModel(this,
		mPhenotypeModel->getLimbModels()[BODYPART_ABDOMENPELVIS],
		mPhenotypeModel->getLimbModels()[BODYPART_THORAX], localA, localB, 0, 0, 0,
		Ogre::Vector3(-0.2 * M_PI, -M_PI_2, -0.1 * M_PI),
		Ogre::Vector3(0.2 * M_PI, M_PI_2, M_PI_2));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this, mPhenotypeModel->getLimbModels()[BODYPART_THORAX],
		mPhenotypeModel->getLimbModels()[BODYPART_HEAD], localA, localB, 0, 0, 0,
		Ogre::Vector3(-M_PI_4, -M_PI_4, -M_PI_2),
		Ogre::Vector3(M_PI_4, M_PI_4, M_PI_2));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this,
		mPhenotypeModel->getLimbModels()[BODYPART_ABDOMENPELVIS],
		mPhenotypeModel->getLimbModels()[BODYPART_LEFT_THIGH], localA, localB, 0, 0, 0,
		Ogre::Vector3(-M_PI_4, -M_PI_4, 0), Ogre::Vector3(M_PI_4, M_PI_4, 0));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this,
		mPhenotypeModel->getLimbModels()[BODYPART_ABDOMENPELVIS],
		mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_THIGH], localA, localB, 0, 0, 0,
		Ogre::Vector3(-M_PI_4, -M_PI_4, 0), Ogre::Vector3(M_PI_4, M_PI_4, 0));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this, mPhenotypeModel->getLimbModels()[BODYPART_LEFT_THIGH],
		mPhenotypeModel->getLimbModels()[BODYPART_LEFT_LEG], localA, localB, 0, 0, 0,
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 3 * M_PI_4));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this,mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_THIGH],
		mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_LEG], localA, localB, 0, 0, 0,
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(0, 0, 3 * M_PI_4));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.1f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(0, M_PI, 0);
	localA.setOrigin(
		btVector3(btScalar(gapSize * -0.2), btScalar(gapSize * 0.15),
			btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI, 0);
	localB.setOrigin(
		btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
			btScalar(gapSize * 0.)));

	joint = new SRBJointModel(this, mPhenotypeModel->getLimbModels()[BODYPART_THORAX],
		mPhenotypeModel->getLimbModels()[BODYPART_LEFT_UPPER_ARM], localA, localB, 0, 0, 0,
		Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2));
	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
	}

	localA.setIdentity();
	localB.setIdentity();
	localA.getBasis().setEulerZYX(M_PI, 0, 0);
	localA.setOrigin(
		btVector3(btScalar(gapSize * 0.2), btScalar(gapSize * 0.15),
			btScalar(gapSize * 0.)));
	localB.getBasis().setEulerZYX(0, M_PI, 0);
	localB.setOrigin(
		btVector3(btScalar(gapSize * 0.), btScalar(gapSize * -0.18),
			btScalar(gapSize * 0.)));

	joint = new SRBJointModel(this, mPhenotypeModel->getLimbModels()[BODYPART_THORAX],
		mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_UPPER_ARM], localA, localB, 0, 0,
		0, Ogre::Vector3(-M_PI_2, -M_PI_2, -M_PI_2),
		Ogre::Vector3(M_PI_2, M_PI_2, M_PI_2));

	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
//	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this,
		mPhenotypeModel->getLimbModels()[BODYPART_LEFT_UPPER_ARM],
		mPhenotypeModel->getLimbModels()[BODYPART_LEFT_FOREARM], localA, localB, 0, 0, 0,
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(3 * M_PI_4, 0, 0));
	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
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

	joint = new SRBJointModel(this,
		mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_UPPER_ARM],
		mPhenotypeModel->getLimbModels()[BODYPART_RIGHT_FOREARM], localA, localB, 0, 0, 0,
		Ogre::Vector3(0, 0, 0), Ogre::Vector3(3 * M_PI_4, 0, 0));
	joint->generateMotors(Ogre::Vector3(10, 10, 10), Ogre::Vector3(10, 10, 10),
		Ogre::Vector3(3, 3, 3));
	mPhenotypeModel->getJointModels().push_back(joint->getJointModel());

	enableMotor = false;
	enableMotor = true;
	for (std::vector<Motor*>::const_iterator motorIterator =
		joint->getMotors().begin(); motorIterator != joint->getMotors().end();
		motorIterator++) {
		SineController* controller = new SineController();
		controller->initialize(0.5f, 0.5f, 0, 0.5f);
		controller->addControlOutput((*motorIterator));
		(*motorIterator)->setEnabled(enableMotor);
		mPhenotypeModel->getControllers().push_back(controller);
	}
	mPhenotypeModel->setDeveloped(true);

}

RagDoll::~RagDoll() {

	// remove all constraints, bodies and shapes from world
	removeFromWorld();

	// delete all constraints
	for (int i = 0; i < JOINT_COUNT; ++i) {
		delete mPhenotypeModel->getJointModels()[i];
	}

	mPhenotypeModel->getJointModels().clear();

	// delete all bodies and shapes
	for (int i = 0; i < BODYPART_COUNT; ++i) {
		delete mPhenotypeModel->getLimbModels()[i];
	}

	mPhenotypeModel->getLimbModels().clear();
}

void RagDoll::update(double timeSinceLastTick) {
	CreatureModel::update(timeSinceLastTick);
}

int RagDoll::addToWorld() {
	int limbQty = 0;
	if (!mPhenotypeModel->isInWorld()) {
		// Add all limbs
		std::vector<Limb*>::iterator lit = mPhenotypeModel->getLimbModels().begin();
		for (; lit != mPhenotypeModel->getLimbModels().end(); lit++) {
			(*lit)->addToWorld();
			limbQty++;
		}

		// Add all constraints
		std::vector<Joint*>::iterator jit = mPhenotypeModel->getJointModels().begin();
		for (; jit != mPhenotypeModel->getJointModels().end(); jit++) {
			(*jit)->addToWorld();
		}

		mPhenotypeModel->setInWorld(true);

	}
	return limbQty;
}

int RagDoll::addToPhysicsWorld() {
	int limbQty = 0;
	if (!mPhenotypeModel->isInWorld()) {
		// Add all limbs
		std::vector<Limb*>::iterator lit = mPhenotypeModel->getLimbModels().begin();
		for (; lit != mPhenotypeModel->getLimbModels().end(); lit++) {
			(*lit)->addToPhysicsWorld();
			limbQty++;
		}

		// Add all constraints
		std::vector<Joint*>::iterator jit = mPhenotypeModel->getJointModels().begin();
		for (; jit != mPhenotypeModel->getJointModels().end(); jit++) {
			(*jit)->addToPhysicsWorld();
		}

		mPhenotypeModel->setInWorld(true);
	}
	return limbQty;
}

void RagDoll::removeFromWorld() {
	if (mPhenotypeModel->isInWorld()) {
		// Remove all constraints
		std::vector<Joint*>::iterator jit = mPhenotypeModel->getJointModels().begin();
		for (; jit != mPhenotypeModel->getJointModels().end(); jit++) {
			(*jit)->removeFromWorld();
		}

		// Remove all limbs
		std::vector<Limb*>::iterator lit = mPhenotypeModel->getLimbModels().begin();
		for (; lit != mPhenotypeModel->getLimbModels().end(); lit++) {
			(*lit)->removeFromWorld();
		}

		mPhenotypeModel->setInWorld(false);
	}
}

