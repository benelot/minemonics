//# corresponding headers
#include <controller/universe/evolution/population/snake/Snake.hpp>
//# forward declarations
//# system headers
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

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/evolution/population/creature/phenome/morphology/Joint.hpp>
#include <controller/universe/evolution/population/creature/phenome/morphology/Limb.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/Population.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/controller/sine/SineController.hpp>
#include <model/universe/PlanetModel.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
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
		Creature(population, OgreBulletUtils::convert(positionOffset), 0) {
	bool damping = true;
	bool gyro = true;
	int numLinks = 10;
	bool spherical = true; //set it to false -to use 1DoF hinges instead of 3DoF sphericals
	bool canSleep = true;
	bool selfCollide = PhysicsConfiguration::SELF_COLLISION;
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
		btScalar q0 = 120.f * SIMD_PI / 180.f;
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
	Creature::update(timeSinceLastTick);
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
	btMultiBody *pMultiBody = new btMultiBody(numLinks, baseMass,
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
			btVector3(linkHalfExtents[0], linkHalfExtents[1],
					linkHalfExtents[2]));
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
			pMultiBody->setupRevolute(i, linkMass, linkInertiaDiag, i - 1,
					btQuaternion(0.f, 0.f, 0.f, 1.f), hingeJointAxis,
					parentComToCurrentPivot, currentPivotToCurrentCom, false);
		else
			//pMultiBody->setupPlanar(i, linkMass, linkInertiaDiag, i - 1, btQuaternion(0.f, 0.f, 0.f, 1.f)/*quat0*/, btVector3(1, 0, 0), parentComToCurrentPivot*2, false);
			pMultiBody->setupSpherical(i, linkMass, linkInertiaDiag, i - 1,
					btQuaternion(0.f, 0.f, 0.f, 1.f), parentComToCurrentPivot,
					currentPivotToCurrentCom, true);
	}

	pMultiBody->finalizeMultiDof();

	return pMultiBody;
}

void Snake::addColliders(btMultiBody *multiBody,
		const btVector3 &baseHalfExtents, const btVector3 &linkHalfExtents) {

	LimbPhysics::PrimitiveType type = LimbPhysics::BLOCK;

	// Setup the geometry
	btAlignedObjectArray<btQuaternion> world_to_local;
	world_to_local.resize(multiBody->getNumLinks() + 1);

	btAlignedObjectArray<btVector3> local_origin;
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
			OgreBulletUtils::convert(baseHalfExtents*2.0f), 0);

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
				btQuaternion(-world_to_local[i + 1].x(),
						-world_to_local[i + 1].y(), -world_to_local[i + 1].z(),
						world_to_local[i + 1].w()));
		limb = new Limb();
		limb->initialize(this, type, OgreBulletUtils::convert(tr.getOrigin()),
				OgreBulletUtils::convert(tr.getRotation()),
				OgreBulletUtils::convert(tr.getOrigin()),
				OgreBulletUtils::convert(tr.getRotation()),
				OgreBulletUtils::convert(linkHalfExtents*2.0f), i);

		limb->generateLink(mPhenotype.getPhenotypeModel()->getMultiBody(),
				tr.getOrigin(), tr.getRotation(), i);

		mPhenotype.getPhenotypeModel()->getMultiBody()->getLink(i).m_collider = limb->getLink();
		mCreatureModel->getPhenotypeModel().getLimbModels().push_back(
				limb->getLimbModel());
		mPhenotype.getLimbs().push_back(limb);
	}
}

