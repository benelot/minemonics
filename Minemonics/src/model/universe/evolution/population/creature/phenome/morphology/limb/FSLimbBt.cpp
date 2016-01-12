//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>

//# forward declarations
#include <cstdlib>

//# system headers
//## controller headers
//## model headers
#include <LinearMath/btQuadWord.h>
#include <LinearMath/btScalar.h>
#include <BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include <OgreColourValue.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>
//## utils headers
#include <utils/MathUtils.hpp>
#include <utils/ogre3D/Euler.hpp>
#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger FSLimbBt::mBoostLogger; /*<! initialize the boost logger*/
FSLimbBt::_Init FSLimbBt::_initializer;
FSLimbBt::FSLimbBt() :
	LimbPhysics(), mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(
	NULL), mInertia(0, 0, 0), mLink(NULL), mLimbModel(NULL) {
}

FSLimbBt::FSLimbBt(btDynamicsWorld* const world, LimbModel* const limbModel,
	const LimbPhysics::PrimitiveType type, const Ogre::Vector3 position,
	const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding) :
	mBody(NULL), mCollisionShape(NULL), mMotionState(NULL), mWorld(world), mInertia(
		0, 0, 0), mLink(NULL) {

	mDimensions = dimensions;
	mMass = mass;
	mType = type;
	mFriction = friction;
	mRestitution = restitution;
	mIntraBodyColliding = isIntraBodyColliding;

	mPosition = position;
	mInitialRelativeXPosition = initialRelativePosition.x;
	mInitialRelativeYPosition = initialRelativePosition.y;
	mInitialRelativeZPosition = initialRelativePosition.z;

	mInitialWOrientation = initialOrientation.w;
	mInitialXOrientation = initialOrientation.x;
	mInitialYOrientation = initialOrientation.y;
	mInitialZOrientation = initialOrientation.z;
	mColor = color;
	mIntraBodyColliding = isIntraBodyColliding;
	mLimbModel = limbModel;
}

FSLimbBt::FSLimbBt(const FSLimbBt& limbBt) {
	btTransform startTransform = limbBt.mBody->getWorldTransform();
	FSLimbBt(limbBt.mWorld,
		(LimbModel*) limbBt.mCollisionShape->getUserPointer(), limbBt.mType,
		OgreBulletUtils::convert(startTransform.getOrigin()),
		OgreBulletUtils::convert(startTransform.getRotation()),
		Ogre::Vector3(limbBt.mInitialRelativeXPosition,
			limbBt.mInitialRelativeYPosition, limbBt.mInitialRelativeZPosition),
		Ogre::Quaternion(limbBt.mInitialWOrientation,
			limbBt.mInitialXOrientation, limbBt.mInitialYOrientation,
			limbBt.mInitialZOrientation), limbBt.mDimensions, limbBt.mMass,
		limbBt.mRestitution, limbBt.mFriction, limbBt.mColor,
		limbBt.mIntraBodyColliding);

	mWorld = limbBt.mWorld;
	mInWorld = limbBt.mInWorld;
	mInertia = limbBt.mInertia;
	mLimbModel = limbBt.mLimbModel;
	mBody = limbBt.mBody;
	mMotionState = limbBt.mMotionState;
	mCollisionShape = limbBt.mCollisionShape;
	mLink = limbBt.mLink;
}

FSLimbBt::~FSLimbBt() {
	delete mBody;
	mBody = NULL;

	delete mCollisionShape;
	mCollisionShape = NULL;

	delete mMotionState;
	mMotionState = NULL;

	delete mLink;
	mLink = NULL;

	mWorld = NULL;
}

void FSLimbBt::initialize() {
	if (!mCollisionShape) {
		btVector3 halfExtents(mDimensions.x * 0.5f, mDimensions.y * 0.5f,
			mDimensions.z * 0.5f);
		switch (mType) {
		case LimbPhysics::BLOCK:
			mCollisionShape = new btBoxShape(halfExtents);
			break;
		case LimbPhysics::CAPSULE:
			mCollisionShape = new btCapsuleShape(btScalar(mDimensions.x * 0.5f),
				btScalar(mDimensions.y));
			break;
		case LimbPhysics::UNKNOWN:
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " LimbBt received 'Unknown' as a limb type.\n";
			exit(-1);
		}

		mCollisionShape->calculateLocalInertia(btScalar(mMass), mInertia);

		// position the limb in the world
		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(OgreBulletUtils::convert(mPosition));
		startTransform.setRotation(
			btQuaternion(mInitialXOrientation, mInitialYOrientation,
				mInitialZOrientation, mInitialWOrientation));

		mMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(btScalar(mMass),
			mMotionState, mCollisionShape, mInertia);
		mBody = new btRigidBody(rbInfo);
		mBody->setDeactivationTime(
			PhysicsConfiguration::BULLET_DEACTIVATION_TIME);
		mBody->setSleepingThresholds(
			PhysicsConfiguration::BULLET_LINEAR_SLEEPING_TIME,
			PhysicsConfiguration::BULLET_ANGULAR_SLEEPING_TIME);
		mBody->setActivationState(DISABLE_DEACTIVATION);

		//to get custom collision callbacks in collisionhandler
		mBody->setCollisionFlags(
			mBody->getCollisionFlags()
				| btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

		//Set the friction and restitution/elasticity of the rigid body
		mBody->setFriction(btScalar(mFriction));
		mBody->setRollingFriction(btScalar(mFriction));
		mBody->setRestitution(btScalar(mRestitution));
		mBody->setAnisotropicFriction(
			mCollisionShape->getAnisotropicRollingFrictionDirection(),
			btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);

		mBody->setUserPointer(mLimbModel); //Set user pointer for proper return of creature/limb information etc..
		mCollisionShape->setUserPointer(mLimbModel); //add the limb model pointer to the collision shape to get it back if we raycast for this object.
	}
}

btTransform FSLimbBt::getIntersection(btVector3 origin, btVector3 direction) {
	return getPreciseIntersection(origin, direction);
}

btTransform FSLimbBt::getPreciseIntersection(const btVector3 origin,
	const btVector3 direction) {
	btVector3 rayStart = origin + direction.normalized() * 100.0f; // the ray caster currently only finds the intersection
	btVector3 rayEnd = origin; // when hitting the forward face of a triangle therefore, the ray has to come from the outside of the shape

#ifndef EXCLUDE_FROM_TEST
	SimulationManager::getSingleton()->getDebugDrawer().drawLine(rayStart,
		rayEnd, btVector3(1, 1, 0));
#endif

	btVector3 hitPosition = origin;
	btVector3 hitNormal(1, 0, 0);

	btCollisionWorld::ClosestRayResultCallback rayCallback(rayStart, rayEnd);

	//kF_UseGjkConvexRaytest flag is now enabled by default, use the faster but more approximate algorithm
	rayCallback.m_flags |= btTriangleRaycastCallback::kF_KeepUnflippedNormal;
	rayCallback.m_flags &= ~btTriangleRaycastCallback::kF_FilterBackfaces;
	rayCallback.m_collisionFilterGroup =
		PhysicsConfiguration::COL_CREATURE_TESTRAY;
	rayCallback.m_collisionFilterMask =
		PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH;

	mWorld->rayTest(rayStart, rayEnd, rayCallback);

	if (rayCallback.hasHit()) {
		hitPosition = rayStart.lerp(rayEnd, rayCallback.m_closestHitFraction);
		hitNormal = rayCallback.m_hitNormalWorld;
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(
			hitPosition, 1, btVector3(1, 0, 0));
		SimulationManager::getSingleton()->getDebugDrawer().drawLine(
			hitPosition, hitPosition + rayCallback.m_hitNormalWorld,
			btVector3(1, 0, 0));
#endif
	} else {
		//no hit
#ifndef EXCLUDE_FROM_TEST
		SimulationManager::getSingleton()->getDebugDrawer().drawSphere(rayStart,
			1, btVector3(1, 0, 0));
#endif
	}

	btTransform hitLocation;
	hitLocation.setIdentity();
	hitLocation.setOrigin(hitPosition); // set the hit position

	Ogre::Euler euler(0, 0, 0);
	euler.direction(OgreBulletUtils::convert(hitNormal));
	hitLocation.setRotation(OgreBulletUtils::convert(euler.toQuaternion())); // set the hit direction to the surface normal
	return hitLocation;
}

btVector3 FSLimbBt::getLocalFakeIntersection(const btVector3 origin,
	const btVector3 direction) {
	return mDimensions.length() / 2.0f * direction.normalized();
}

btTransform FSLimbBt::getLocalIntersection(const btVector3 origin,
	const btVector3 direction) {
	btTransform intersection = getLocalPreciseIntersection(origin, direction); // find local precise intersection

	if (intersection.getOrigin().isZero()) { // if the local precise intersection can not be found
		intersection.setOrigin(getLocalFakeIntersection(origin, direction)); // we use a local maximum distance to surface estimate
	}
	return intersection;
}

void FSLimbBt::reset(const Ogre::Vector3 position) {
	btTransform initialTransform;
	initialTransform.setIdentity();

	btVector3 initialRelativePosition;
	initialRelativePosition.setValue(getInitialRelativeXPosition(),
		getInitialRelativeYPosition(), getInitialRelativeZPosition());

	btQuaternion initialOrientation;
	initialOrientation.setValue(getInitialXOrientation(),
		getInitialYOrientation(), getInitialZOrientation(),
		getInitialWOrientation());

	initialTransform.setOrigin(
		OgreBulletUtils::convert(position) + initialRelativePosition);
	initialTransform.setRotation(initialOrientation);

	mBody->setWorldTransform(initialTransform);
	if (mLink) {
		mLink->setWorldTransform(initialTransform);
	}
	mMotionState->setWorldTransform(initialTransform);
	calm();
}

void FSLimbBt::reposition(const Ogre::Vector3 position) {
	btTransform initialTransform;

	btVector3 initialRelativePosition;
	initialRelativePosition.setValue(getInitialRelativeXPosition(),
		getInitialRelativeYPosition(), getInitialRelativeZPosition());

	btQuaternion initialOrientation;
	initialOrientation.setValue(getInitialXOrientation(),
		getInitialYOrientation(), getInitialZOrientation(),
		getInitialWOrientation());

	initialTransform.setOrigin(
		OgreBulletUtils::convert(position) + initialRelativePosition);
	initialTransform.setRotation(initialOrientation);

	mBody->setWorldTransform(initialTransform);
	mMotionState->setWorldTransform(initialTransform);
}

btTransform FSLimbBt::getLocalPreciseIntersection(const btVector3 origin,
	const btVector3 direction) {
	btTransform transform = getPreciseIntersection(origin, direction);
	transform.setOrigin(transform.getOrigin() - origin);
	return transform;
}

void FSLimbBt::addToWorld() {
	if (!isInWorld()) {
		if (mLink != NULL) {
			if (mIntraBodyColliding) {
				mWorld->addCollisionObject(mLink);
			} else {
				mWorld->addCollisionObject(mLink,
					PhysicsConfiguration::COL_CREATURE,
					PhysicsConfiguration::CREATURE_COLLIDES_WITH);
			}
		}
		LimbPhysics::addToWorld();
	}
}

void FSLimbBt::removeFromWorld() {
	if (isInWorld()) {
		if (mLink != NULL) {
			mWorld->removeCollisionObject(mLink);
		}
	}
	LimbPhysics::removeFromWorld();
}

FSLimbBt* FSLimbBt::clone() {
	return new FSLimbBt(*this);
}

void FSLimbBt::calm() {
	if (mBody) {
		mBody->clearForces();
		btVector3 zeroVector(0, 0, 0);
		mBody->setLinearVelocity(zeroVector);
		mBody->setAngularVelocity(zeroVector);
	}
}

void FSLimbBt::generateLink(btMultiBody* multiBody, void* const limbModel,
	btVector3 origin, btQuaternion rotation, int index) {
	mLink = new btMultiBodyLinkCollider(multiBody, index);
	mLink->setCollisionShape(mCollisionShape);

	btTransform tr;
	tr.setIdentity();
	tr.setOrigin(origin);
	tr.setRotation(rotation);
	mLink->setDeactivationTime(PhysicsConfiguration::BULLET_DEACTIVATION_TIME);
	mLink->setWorldTransform(tr);
	mLink->setFriction(mFriction);
	mLink->setAnisotropicFriction(
		mCollisionShape->getAnisotropicRollingFrictionDirection(),
		btCollisionObject::CF_ANISOTROPIC_ROLLING_FRICTION);

	mLink->setUserPointer(limbModel); //Set user pointer for proper return of creature/limb information etc..
	mCollisionShape->setUserPointer(limbModel); //add the limbModel pointer to the collision shape to get it back if we raycast for this object.
}

bool FSLimbBt::equals(const FSLimbBt& limbBt) const {
	if (!LimbPhysics::equals(limbBt)) {
		return false;
	}
	return true;
}

const Ogre::Vector3 FSLimbBt::getVelocities() const {
	return OgreBulletUtils::convert(mLink->getInterpolationLinearVelocity());
}

btVector3 FSLimbBt::getPosition() const {
	btTransform transform;
	if (mLink) {
		transform = mLink->getWorldTransform();
	} else {
		transform = mBody->getWorldTransform();
	}

	btVector3 position = transform.getOrigin();
	if (!MathUtils::isFinite(position)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb position: " << MathUtils::print(position);
	}

	return position;
}

btQuaternion FSLimbBt::getOrientation() const {
	btTransform transform;
	if (mLink) {
		transform = mLink->getWorldTransform();
	} else {
		transform = mBody->getWorldTransform();
	}

	btQuaternion orientation = transform.getRotation().normalized();
	if (!MathUtils::isFinite(orientation)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb orientation: " << MathUtils::print(orientation);
	}

	return orientation;
}
