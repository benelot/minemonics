//# corresponding headers
#include <stddef.h>
#include <cmath>
#include <iterator>

//## controller headers
//## model headers
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <BulletDynamics/Featherstone/btMultiBodyLinkCollider.h>
#include <BulletDynamics/Featherstone/btMultiBodyLink.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointLimitConstraint.h>
#include <BulletDynamics/Featherstone/btMultiBodyJointMotor.h>
#include <BulletDynamics/Featherstone/btMultiBodyPoint2Point.h>
#include <controller/universe/evolution/population/creature/SRBcreature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/SRBcreature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/SRBcreature/SRBCreature.hpp>
#include <controller/universe/evolution/population/Population.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/evolution/population/creature/modelOrganism/snake/Snake.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>
#include <model/universe/evolution/population/PopulationModel.hpp>

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

Snake::Snake(Population* const population, double size,
	const btVector3& positionOffset) :
	integrativeError(0, 0, 0), SRBCreature(population,
		OgreBulletUtils::convert(positionOffset), 0) {
	rotate = -1.0f;
	sign = 1;

	bool damping = true;
	bool gyro = true;
	int numLinks = 10;
	bool spherical = true; //set it to false -to use 1DoF hinges instead of 3DoF sphericals
	bool canSleep = true;
	bool selfCollide = false; //PhysicsConfiguration::SELF_COLLISION;
	bool attachHead = false;
	bool enableMotor = false;

	btVector3 linkHalfExtents(size * 0.05, size * 0.37, size * 0.1);
	btVector3 baseHalfExtents(size * 0.05, size * 0.37, size * 0.1);

	btMultiBody* mb = createFeatherstoneMultiBody(numLinks, positionOffset,
		linkHalfExtents, baseHalfExtents, spherical, attachHead);

	mPhenotype.getPhenotypeModel()->setMultiBody(mb);

	mPhenotype.getPhenotypeModel()->getMultiBody()->setCanSleep(canSleep);
	mPhenotype.getPhenotypeModel()->getMultiBody()->setHasSelfCollision(
		selfCollide);
	mPhenotype.getPhenotypeModel()->getMultiBody()->setUseGyroTerm(gyro);
	//
	if (!damping) {
		mPhenotype.getPhenotypeModel()->getMultiBody()->setLinearDamping(0.f);
		mPhenotype.getPhenotypeModel()->getMultiBody()->setAngularDamping(0.f);
	} else {
		mPhenotype.getPhenotypeModel()->getMultiBody()->setLinearDamping(0.1f);
		mPhenotype.getPhenotypeModel()->getMultiBody()->setAngularDamping(0.9f);
	}

	if (numLinks > 0) {
		btScalar q0 = 150.f * SIMD_PI / 180.f;
		if (!spherical)
			if (mPhenotype.getPhenotypeModel()->getMultiBody()->isMultiDof())
				mPhenotype.getPhenotypeModel()->getMultiBody()->setJointPosMultiDof(
					0, &q0);
			else
				mPhenotype.getPhenotypeModel()->getMultiBody()->setJointPos(0,
					q0);
		else {
			btQuaternion quat0(btVector3(1, 1, 0).normalized(), q0);
			quat0.normalize();
			mPhenotype.getPhenotypeModel()->getMultiBody()->setJointPosMultiDof(
				0, quat0);
		}
	}

	addColliders(mPhenotype.getPhenotypeModel()->getMultiBody(),
		baseHalfExtents, linkHalfExtents);

	mPhenotype.setDeveloped(true);
}

Snake::~Snake() {

	// remove all constraints, bodies and shapes from world
	removeFromWorld();

	// delete all constraints
	for (int i = 0; i < mPhenotype.getJoints().size(); ++i) {
		delete mPhenotype.getJoints()[i];
	}

	mPhenotype.getJoints().clear();

	// delete all bodies and shapes
	for (int i = 0; i < mPhenotype.getLimbs().size(); ++i) {
		delete mPhenotype.getLimbs()[i];
	}

	mPhenotype.getLimbs().clear();
}

void Snake::update(double timeSinceLastTick) {
	SRBCreature::update(timeSinceLastTick);

	rotate += sign * timeSinceLastTick;
	if (abs(rotate) >= 1) {
		sign *= -1;
	}

	btMultiBody* mMultibody = mPhenotype.getPhenotypeModel()->getMultiBody();
//	for (int joint = 0; joint < mMultibody->getNumLinks(); joint++) {
	int joint = 0;
	int dof1 = 0;
	int dof2 = 1;
	int dof3 = 2;
	btScalar k = 10;
	btScalar kp = 100;
	btScalar ki = 50;
	btScalar kd = 20;
	btScalar maxForce = 1000000000;

	btVector3 position;
//		if (joint % 2 == 0) {
	position.m_floats[dof1] = rotate * 0.1f * SIMD_PI;
//		} else {
//			position.m_floats[dof1]  = -rotate * 0.1f * SIMD_PI;
//		}
//		position.m_floats[dof1] = SIMD_PI;
	position.m_floats[dof2] = 0;
	position.m_floats[dof3] = 0.15;

	btVector3 qActual;
	btVector3 qdActual;
	qActual.m_floats[dof1] = mMultibody->getJointPosMultiDof(joint)[dof1];
	qActual.m_floats[dof2] = mMultibody->getJointPosMultiDof(joint)[dof2];
	qActual.m_floats[dof3] = mMultibody->getJointPosMultiDof(joint)[dof3];

	qdActual.m_floats[dof1] = mMultibody->getJointVelMultiDof(joint)[dof1];
	qdActual.m_floats[dof2] = mMultibody->getJointVelMultiDof(joint)[dof2];
	qdActual.m_floats[dof3] = mMultibody->getJointVelMultiDof(joint)[dof3];

	btVector3 positionError = (position - qActual);

	integrativeError += positionError * timeSinceLastTick * 10.0f;

	btVector3 desiredVelocity(0, 0, 0);
	btVector3 velocityError = (desiredVelocity - qdActual);
	btVector3 force = kp * positionError + ki * integrativeError
		+ kd * velocityError;
	btClamp(force.m_floats[0], -maxForce, maxForce);
	btClamp(force.m_floats[1], -maxForce, maxForce);
	btClamp(force.m_floats[2], -maxForce, maxForce);

	if (0) {
//			mMultibody->addJointTorque(joint, force);
	} else {
		mMultibody->addJointTorqueMultiDof(joint, dof1,
			btScalar(force.m_floats[dof1]));
		mMultibody->addJointTorqueMultiDof(joint, dof2,
			btScalar(force.m_floats[dof2]));
		mMultibody->addJointTorqueMultiDof(joint, dof3,
			btScalar(force.m_floats[dof3]));
	}
	//mMultibody->addJointTorqueMultiDof(joint, 0,  k*(-SIMD_PI-mMultibody->getJointPosMultiDof(joint)[0]));
	int showDof = dof3;
	std::cout << "Desired position: \t" << position.m_floats[showDof]
		<< "position error: \t" << positionError.m_floats[showDof]
		<< "\tvelocity error: \t" << velocityError.m_floats[showDof]
		<< "\tApplied force: " << force.m_floats[showDof] << std::endl;
	//mMultibody->addJointTorqueMultiDof(joint, 2,  k*(-SIMD_PI-mMultibody->getJointPosMultiDof(joint)[2]));
//		m_multiBody->addJointTorque(joint, force);
//	}

}

int Snake::addToWorld() {
	int limbQty = 10;
	if (!mPhenotype.isInWorld()) {
		mPhenotype.addToWorld();
		// Add all limbs
//		std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
//		for (; lit != mPhenotype.getLimbs().end(); lit++) {
//			(*lit)->addToWorld();
//			limbQty++;
//		}

//		// Add all constraints
//		std::vector<Joint*>::iterator jit = mPhenotype.getJoints().begin();
//		for (; jit != mPhenotype.getJoints().end(); jit++) {
//			(*jit)->addToWorld();
//		}

		mPhenotype.setInWorld(true);

	}
	return limbQty;
}

int Snake::addToPhysicsWorld() {
	int limbQty = 10;
	if (!mPhenotype.isInWorld()) {
		mPhenotype.addToWorld();
		// Add all limbs
//		std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
//		for (; lit != mPhenotype.getLimbs().end(); lit++) {
//			(*lit)->addToPhysicsWorld();
//			limbQty++;
//		}

		mPhenotype.setInWorld(true);
	}
	return limbQty;
}

void Snake::removeFromWorld() {
	if (mPhenotype.isInWorld()) {
		mPhenotype.removeFromWorld();

		// Remove all limbs
		std::vector<Limb*>::iterator lit = mPhenotype.getLimbs().begin();
		for (; lit != mPhenotype.getLimbs().end(); lit++) {
			(*lit)->removeFromWorld();
		}

		mPhenotype.setInWorld(false);
	}
}

btMultiBody* Snake::createFeatherstoneMultiBody(int numLinks,
	const btVector3 &basePosition, const btVector3 &baseHalfExtents,
	const btVector3 &linkHalfExtents, bool spherical, bool floating) {
	//init the base
	btVector3 baseInertiaDiag(0.f, 0.f, 0.f);
	float baseMass = 1.f;

	if (baseMass) {
		btCollisionShape *pTempBox = new btBoxShape(
			btVector3(baseHalfExtents[0], baseHalfExtents[1],
				baseHalfExtents[2]));
		pTempBox->calculateLocalInertia(baseMass, baseInertiaDiag);
		delete pTempBox;
	}

	bool canSleep = false;
	bool isMultiDof = true;
	btMultiBody *pMultiBody = new btMultiBody(numLinks, btScalar(baseMass),
		baseInertiaDiag, floating, canSleep, isMultiDof);

	btQuaternion baseOriQuat(0.f, 0.f, 0.f, 1.f);
	pMultiBody->setBasePos(basePosition);
	pMultiBody->setWorldToBaseRot(baseOriQuat);
	btVector3 vel(0, 0, 0);
//	pMultiBody->setBaseVel(vel);

	//init the links
	btVector3 hingeJointAxis(1, 0, 0);
	float linkMass = 1.f;
	btVector3 linkInertiaDiag(0.f, 0.f, 0.f);

	btCollisionShape *pTempBox = new btBoxShape(
		btVector3(linkHalfExtents[0], linkHalfExtents[1], linkHalfExtents[2]));
	pTempBox->calculateLocalInertia(linkMass, linkInertiaDiag);
	delete pTempBox;

	//y-axis assumed up
	btVector3 parentComToCurrentCom(0, -linkHalfExtents[1] * 2.f, 0); //par body's COM to cur body's COM offset
	btVector3 currentPivotToCurrentCom(0, -linkHalfExtents[1], 0); //cur body's COM to cur body's PIV offset
	btVector3 parentComToCurrentPivot = parentComToCurrentCom
		- currentPivotToCurrentCom;	//par body's COM to cur body's PIV offset

	//////
	btScalar q0 = 0.f * SIMD_PI / 180.f;
	btQuaternion quat0(btVector3(0, 1, 0).normalized(), q0);
	quat0.normalize();
	/////

	for (int i = 0; i < numLinks; ++i) {
		if (!spherical)
//			if (i == 0) {
			pMultiBody->setupRevolute(i, btScalar(linkMass), linkInertiaDiag,
				i - 1, btQuaternion(0.f, 0.f, 0.f, 1.f), hingeJointAxis,
				parentComToCurrentPivot, currentPivotToCurrentCom, false);
//			} else {
//				pMultiBody->setupFixed(i, linkMass, linkInertiaDiag, i - 1,
//				btQuaternion(0.f, 0.f, 0.f, 1.f), parentComToCurrentPivot,
//				currentPivotToCurrentCom, true);
//			}

		else {
			if (i == 0) {
				//pMultiBody->setupPlanar(i, linkMass, linkInertiaDiag, i - 1, btQuaternion(0.f, 0.f, 0.f, 1.f)/*quat0*/, btVector3(1, 0, 0), parentComToCurrentPivot*2, false);
				pMultiBody->setupSpherical(i, btScalar(linkMass),
					linkInertiaDiag, i - 1, btQuaternion(0.f, 0.f, 0.f, 1.f),
					parentComToCurrentPivot, currentPivotToCurrentCom, true);
			} else {
				pMultiBody->setupFixed(i, btScalar(linkMass), linkInertiaDiag,
					i - 1, btQuaternion(0.f, 0.f, 0.f, 1.f),
					parentComToCurrentPivot, currentPivotToCurrentCom, true);
			}
		}
	}

	pMultiBody->finalizeMultiDof();

	return pMultiBody;
}

void Snake::addColliders(btMultiBody *multiBody,
	const btVector3 &baseHalfExtents, const btVector3 &linkHalfExtents) {

	LimbPhysics::PrimitiveType type = LimbPhysics::BLOCK;

	// Setup the geometry
	btAlignedObjectArray < btQuaternion > world_to_local;
	world_to_local.resize(multiBody->getNumLinks() + 1);

	btAlignedObjectArray < btVector3 > local_origin;
	local_origin.resize(multiBody->getNumLinks() + 1);
	world_to_local[0] = multiBody->getWorldToBaseRot();
	local_origin[0] = multiBody->getBasePos();

	// create base limb
	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(local_origin[0]);
	tr.setRotation(
		btQuaternion(-world_to_local[0].x(), -world_to_local[0].y(),
			-world_to_local[0].z(), world_to_local[0].w()));

	Limb* limb = new Limb();
	limb->initialize(this, type, OgreBulletUtils::convert(tr.getOrigin()),
		OgreBulletUtils::convert(tr.getRotation()),
		OgreBulletUtils::convert(tr.getOrigin()),
		OgreBulletUtils::convert(tr.getRotation()),
		OgreBulletUtils::convert(baseHalfExtents * 2.0f), 0);

	limb->generateLink(mPhenotype.getPhenotypeModel()->getMultiBody(),
		tr.getOrigin(), tr.getRotation(), -1);

	multiBody->setBaseCollider(limb->getLink());

	mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
		limb->getLimbModel());
	mPhenotype.getLimbs().push_back(limb);

	//calculate positions of other elements
	for (int i = 0; i < multiBody->getNumLinks(); ++i) {
		const int parent = multiBody->getParent(i);
		world_to_local[i + 1] = multiBody->getParentToLocalRot(i)
			* world_to_local[parent + 1];
		local_origin[i + 1] = local_origin[parent + 1]
			+ (quatRotate(world_to_local[i + 1].inverse(),
				multiBody->getRVector(i)));
	}

	// create other limbs
	for (int i = 0; i < multiBody->getNumLinks(); ++i) {

		btTransform tr;
		tr.setIdentity();
		tr.setOrigin(local_origin[i + 1]);
		tr.setRotation(
			btQuaternion(-world_to_local[i + 1].x(), -world_to_local[i + 1].y(),
				-world_to_local[i + 1].z(), world_to_local[i + 1].w()));
		limb = new Limb();
		limb->initialize(this, type, OgreBulletUtils::convert(tr.getOrigin()),
			OgreBulletUtils::convert(tr.getRotation()),
			OgreBulletUtils::convert(tr.getOrigin()),
			OgreBulletUtils::convert(tr.getRotation()),
			OgreBulletUtils::convert(linkHalfExtents * 2.0f), i);

		limb->generateLink(mPhenotype.getPhenotypeModel()->getMultiBody(),
			tr.getOrigin(), tr.getRotation(), i);

		mPhenotype.getPhenotypeModel()->getMultiBody()->getLink(i).m_collider =
			limb->getLink();
		mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
			limb->getLimbModel());
		mPhenotype.getLimbs().push_back(limb);
	}
}

