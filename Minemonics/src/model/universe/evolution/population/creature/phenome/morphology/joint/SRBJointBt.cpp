//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <OgreQuaternion.h>
#include <LinearMath/btMatrix3x3.h>
#include <LinearMath/btScalar.h>
#include <BulletCollision/CollisionDispatch/btCollisionObject.h>
#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/MathUtils.hpp>

BoostLogger SRBJointBt::mBoostLogger; /*<! initialize the boost logger*/
SRBJointBt::_Init SRBJointBt::_initializer;
SRBJointBt::SRBJointBt() :
	mWorld(NULL), mJoint(NULL), mBodyA(NULL), mBodyB(
	NULL) {
}

SRBJointBt::SRBJointBt(const SRBJointBt& SRBJointBt) {
	mWorld = SRBJointBt.mWorld;
	mJoint = SRBJointBt.mJoint;
	mInWorld = SRBJointBt.mInWorld;
	mBodyA = SRBJointBt.mBodyA;
	mBodyB = SRBJointBt.mBodyB;
	mFrameInA = SRBJointBt.mFrameInA;
	mFrameInB = SRBJointBt.mFrameInB;

	for (std::vector<Motor*>::const_iterator mit = SRBJointBt.mMotors.begin();
		mit != SRBJointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

SRBJointBt::SRBJointBt(btDynamicsWorld* const world, btRigidBody* const bodyA,
	btRigidBody* const bodyB, const btVector3& pivotInW,
	JointPhysics::JointType type, btVector3 jointPitchAxis,
	btVector3 jointYawAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits, int ownIndex) :
	mJoint(NULL) {
	mWorld = world;
	mBodyA = bodyA;
	mBodyB = bodyB;

	// build frame basis
	// 6DOF constraint uses Euler angles and to define limits
	// it is assumed that rotational order is :
	// Z - first, allowed limits are (-PI,PI);
	// new position of Y - second (allowed limits are (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
	// used to prevent constraint from instability on poles;
	// new position of X, allowed limits are (-PI,PI);
	// So to simulate ODE Universal joint we should use parent axis as Z, child axis as Y and limit all other DOFs
	// Build the frame in world coordinate system first
	btVector3 zAxis = jointPitchAxis.normalize();
	btVector3 yAxis = jointYawAxis.normalize();
	btVector3 xAxis = yAxis.cross(zAxis); // we want right coordinate system
	btTransform frameInW;
	frameInW.setIdentity();
	frameInW.getBasis().setValue(xAxis[0], yAxis[0], zAxis[0], xAxis[1],
		yAxis[1], zAxis[1], xAxis[2], yAxis[2], zAxis[2]);
	frameInW.setOrigin(pivotInW);
	// now get constraint frame in local coordinate systems
	mFrameInA = bodyA->getCenterOfMassTransform().inverse() * frameInW;
	mFrameInB = bodyB->getCenterOfMassTransform().inverse() * frameInW;

	mLocalAPosition = OgreBulletUtils::convert(mFrameInA.getOrigin());
	mLocalBPosition = OgreBulletUtils::convert(mFrameInB.getOrigin());

	mLocalAOrientation = OgreBulletUtils::convert(mFrameInA.getRotation());
	mLocalBOrientation = OgreBulletUtils::convert(mFrameInB.getRotation());

	if (!MathUtils::isFinite(mLocalAPosition)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb A position: " << mLocalAPosition;
	}

	if (!MathUtils::isFinite(mLocalAPosition)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb B position: " << mLocalBPosition;
	}

	if (!MathUtils::isFinite(mLocalAOrientation)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb A orientation: " << mLocalAOrientation;
	}

	if (!MathUtils::isFinite(mLocalAOrientation)) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::fatal)<< " NaN/Inf detected in limb B orientation: " << mLocalBOrientation;
	}

	mType = type;

	mJointPitchAxis = OgreBulletUtils::convert(jointPitchAxis);
	mJointYawAxis = OgreBulletUtils::convert(jointYawAxis);
	mJointLowerLimits = OgreBulletUtils::convert(jointLowerLimits);
	mJointUpperLimits = OgreBulletUtils::convert(jointUpperLimits);
	mJointIndex = ownIndex;
}

void SRBJointBt::initialize() {
	mFrameInA.setOrigin(OgreBulletUtils::convert(mLocalAPosition));
	mFrameInA.setRotation(OgreBulletUtils::convert(mLocalAOrientation));
	mFrameInB.setOrigin(OgreBulletUtils::convert(mLocalBPosition));
	mFrameInB.setRotation(OgreBulletUtils::convert(mLocalBOrientation));

#if CONSTRAINT_INDEX == HINGECONSTRAINT
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA, mFrameInB, true);
	btVector3 jointPitchAxis = OgreBulletUtils::convert(mJointPitchAxis);
	mJoint->setAxis(jointPitchAxis);
	mJoint->setLimit(mJointLowerLimits.z, mJointUpperLimits.z);

#elif CONSTRAINT_INDEX == GENERIC6DOFCONSTRAINT

	// now create the constraint
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA, mFrameInB, true);
	// linear limits in our case are allowed offset of origin of frameInB in frameInA, so set them to zero
	mJoint->setLinearLowerLimit(btVector3(0., 0., 0.));
	mJoint->setLinearUpperLimit(btVector3(0., 0., 0.));

	// set limits for parent (axis z) and child (axis Y)
	mJoint->setAngularLowerLimit(OgreBulletUtils::convert(mJointLowerLimits));
	mJoint->setAngularUpperLimit(OgreBulletUtils::convert(mJointUpperLimits));
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRING2CONSTRAINT
	// now create the constraint
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA, mFrameInB);

	// linear limits in our case are allowed offset of origin of frameInB in frameInA, so set them to zero
	mJoint->setLinearLowerLimit(btVector3(0., 0., 0.));
	mJoint->setLinearUpperLimit(btVector3(0., 0., 0.));

	// set limits for parent (axis z) and child (axis Y)
	mJoint->setAngularLowerLimit(OgreBulletUtils::convert(mJointLowerLimits));
	mJoint->setAngularUpperLimit(OgreBulletUtils::convert(mJointUpperLimits));
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRINGCONSTRAINT
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA, mFrameInB, true);
	// linear limits in our case are allowed offset of origin of frameInB in frameInA, so set them to zero
	mJoint->setLinearLowerLimit(btVector3(0., 0., 0.));
	mJoint->setLinearUpperLimit(btVector3(0., 0., 0.));

	// set limits for parent (axis z) and child (axis Y)
	mJoint->setAngularLowerLimit(OgreBulletUtils::convert(mJointLowerLimits));
	mJoint->setAngularUpperLimit(OgreBulletUtils::convert(mJointUpperLimits));
#elif CONSTRAINT_INDEX == POINT2POINTCONSTRAINT
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA.getOrigin(), mFrameInB.getOrigin());
#elif CONSTRAINT_INDEX == CONETWISTCONSTRAINT
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA, mFrameInB);
	mJoint->setLimit(mJointUpperLimits.x - mJointLowerLimits.x,
		mJointUpperLimits.y - mJointLowerLimits.y,
		mJointUpperLimits.z - mJointLowerLimits.z);
#endif

#ifdef CONSTRAINT_INDEX
	mJoint->enableFeedback(true);
	mJoint->setJointFeedback(new btJointFeedback());

	//debug drawing
	mJoint->setDbgDrawSize(btScalar(5.f));
#endif

}

SRBJointBt::~SRBJointBt() {
	removeFromWorld();

	// nullify the world reference
	mWorld = NULL;

	//delete and clear the motor vector
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		delete (*motorIterator);
	}

	mMotors.clear();
#ifdef CONSTRAINT_INDEX
	delete mJoint;
	mJoint = NULL;
#endif
}

void SRBJointBt::update(double timeSinceLastTick) {
	//apply motor forces
	//TODO: Turn on when you want to use motors
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
//			(*motorIterator)->apply(timeSinceLastTick);
		}
	}
}

void SRBJointBt::generateMotors(const btVector3 maxForces,
	const btVector3 lowerLimits, const btVector3 upperLimits,
	bool positionControlled) {

	mJointMaxForces = OgreBulletUtils::convert(maxForces);
	mJointUpperLimits = OgreBulletUtils::convert(upperLimits);
	mJointLowerLimits = OgreBulletUtils::convert(lowerLimits);

	//	add pitch servo motor
	SRBServoMotor* servoMotor = new SRBServoMotor(JointPhysics::RDOF_PITCH,
		maxForces.getX(), lowerLimits.x(), upperLimits.x(), positionControlled);
	servoMotor->initialize(NULL);
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new SRBServoMotor(JointPhysics::RDOF_YAW, maxForces.getY(),
		lowerLimits.y(), upperLimits.y(), positionControlled);
	servoMotor->initialize(NULL);
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new SRBServoMotor(JointPhysics::RDOF_ROLL, maxForces.getZ(),
		lowerLimits.z(), upperLimits.z(), positionControlled);
	servoMotor->initialize(NULL);
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);
}

bool SRBJointBt::equals(const SRBJointBt& jointBt) const {

	if (!JointPhysics::equals(jointBt)) {
		return false;
	}

	/**Comparison of motors*/
	if (mMotors.size() != jointBt.mMotors.size()) {
		return false;
	}
	std::vector<Motor*>::const_iterator it = mMotors.begin();
	std::vector<Motor*>::const_iterator it2 = jointBt.mMotors.begin();
	for (; it != mMotors.end(), it2 != jointBt.mMotors.end(); it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	return true;
}

void SRBJointBt::reset(const Ogre::Vector3 position) {
	//nothing to be reset
}

void SRBJointBt::reposition(const Ogre::Vector3 position) {
	//nothing to be repositioned
}

void SRBJointBt::setAngularStiffness(double jointPitchStiffness,
	double jointYawStiffness, double jointRollStiffness) {
#if CONSTRAINT_INDEX == HINGECONSTRAINT
	// no stiffness available
#elif CONSTRAINT_INDEX == GENERIC6DOFCONSTRAINT
// no stiffness available
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRING2CONSTRAINT
	mJoint->setStiffness(0,btScalar(jointPitchStiffness));
	mJoint->setStiffness(1,btScalar(jointYawStiffness));
	mJoint->setStiffness(2,btScalar(jointRollStiffness));
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRINGCONSTRAINT
	mJoint->setStiffness(0,btScalar(jointPitchStiffness));
	mJoint->setStiffness(1,btScalar(jointYawStiffness));
	mJoint->setStiffness(2,btScalar(jointRollStiffness));
#elif CONSTRAINT_INDEX == POINT2POINTCONSTRAINT
	// no stiffness available
#elif CONSTRAINT_INDEX == CONETWISTCONSTRAINT
//	mJoint->setStiffness(btScalar(jointPitchStiffness));
#endif
}

void SRBJointBt::setAngularDamping(double jointPitchDamping,
	double jointYawDamping, double jointRollDamping) {
#if CONSTRAINT_INDEX == HINGECONSTRAINT

#elif CONSTRAINT_INDEX == GENERIC6DOFCONSTRAINT
// no damping available
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRING2CONSTRAINT
	mJoint->setDamping(0,btScalar(jointPitchDamping));
	mJoint->setDamping(1,btScalar(jointYawDamping));
	mJoint->setDamping(2,btScalar(jointRollDamping));
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRINGCONSTRAINT
	mJoint->setDamping(0,btScalar(jointPitchDamping));
	mJoint->setDamping(1,btScalar(jointYawDamping));
	mJoint->setDamping(2,btScalar(jointRollDamping));
#elif CONSTRAINT_INDEX == POINT2POINTCONSTRAINT
	// no damping available
#elif CONSTRAINT_INDEX == CONETWISTCONSTRAINT
	mJoint->setDamping(btScalar(jointPitchDamping));
#endif
}

void SRBJointBt::setRotationalLimitMotorEnabled(
	const JointPhysics::RotationalDegreeOfFreedom index, const bool enable) {
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->getIndex() == index) {
			(*motorIterator)->setEnabled(true);
			break;
		}
	}
}

void SRBJointBt::addToWorld() {
	if (!isInWorld()) {
#ifdef CONSTRAINT_INDEX
		mWorld->addConstraint((btTypedConstraint*) mJoint, true);
#endif
		JointPhysics::addToWorld();
	}
}

void SRBJointBt::removeFromWorld() {
	if (isInWorld()) {
#ifdef CONSTRAINT_INDEX
		mWorld->removeConstraint((btTypedConstraint*) mJoint);
#endif
		JointPhysics::removeFromWorld();
	}
}

SRBJointBt* SRBJointBt::clone() {
	return new SRBJointBt(*this);
}

void SRBJointBt::applyJointTorque(int jointAxisIndex, double torque) {

#ifdef CONSTRAINT_INDEX
	// this is consistent with pitch = z, yaw = y, roll = x
	// Check constructor if that is still the way it is defined
	int col;
	switch (jointAxisIndex) {
	case 0:
		col = 2;
		break;
	case 1:
		col = 1;
		break;
	case 2:
		col = 0;
		break;
	default:
		return;
	}

	// z-axis of constraint frame
	btVector3 hingeAxisLocalA = mJoint->getFrameOffsetA().getBasis().getColumn(
		col);

	btVector3 hingeAxisLocalB = mJoint->getFrameOffsetB().getBasis().getColumn(
		col);

	btVector3 hingeAxisWorldA =
		mJoint->getRigidBodyA().getWorldTransform().getBasis()
			* hingeAxisLocalA;

	btVector3 hingeAxisWorldB =
		mJoint->getRigidBodyB().getWorldTransform().getBasis()
			* hingeAxisLocalB;

	btVector3 hingeTorqueA = torque * hingeAxisWorldA;
	btVector3 hingeTorqueB = torque * hingeAxisWorldB;

	mBodyA->applyTorque(-hingeTorqueA);
	mBodyB->applyTorque(hingeTorqueB);
#endif
}

double SRBJointBt::getJointPos(int jointAxisIndex) {

#if CONSTRAINT_INDEX == HINGECONSTRAINT
	return mJoint->getHingeAngle();
#elif CONSTRAINT_INDEX == GENERIC6DOFCONSTRAINT
	return mJoint->getAngle(jointAxisIndex);
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRING2CONSTRAINT
	return mJoint->getAngle(jointAxisIndex);
#elif CONSTRAINT_INDEX == GENERIC6DOFSPRINGCONSTRAINT
	return mJoint->getAngle(jointAxisIndex);
#elif CONSTRAINT_INDEX == POINT2POINTCONSTRAINT
	return 0; //TODO: It seems this joint does not even have getAngle mJoint->getAngle(jointAxisIndex);
#elif CONSTRAINT_INDEX == CONETWISTCONSTRAINT
	//TODO There must be more angles than only that
	return mJoint->getTwistAngle();
#else
	return 0;
#endif
}

double SRBJointBt::getJointVel(int jointAxisIndex) {
//TODO: Find a way to get joint velocity in SRB
	return 0;
//	mJoint->get
}
