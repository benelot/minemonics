//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/SRBServoMotor.hpp>

//## view headers
//## utils headers

SRBJointBt::SRBJointBt() :
	mWorld(NULL), mJoint(NULL), mMotorTarget(0, 0, 0, 1), mBodyA(NULL), mBodyB(
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
	btRigidBody* const bodyB, const btTransform& tframeInA,
	const btTransform& tframeInB, JointPhysics::JointType type,
	bool jointPitchEnabled, bool jointYawEnabled, bool jointRollEnabled,
	btVector3 jointPitchAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits) :
	mJoint(NULL) {
	mWorld = world;
	mBodyA = bodyA;
	mBodyB = bodyB;
	mFrameInA = tframeInA;
	mFrameInB = tframeInB;
	mType = type;
	mJointPitchEnabled = jointPitchEnabled;
	mJointYawEnabled = jointYawEnabled;
	mJointRollEnabled = jointRollEnabled;

	mJointPitchAxis = OgreBulletUtils::convert(jointPitchAxis);
	mJointMinAngle = OgreBulletUtils::convert(jointLowerLimits);
	mJointMaxAngle = OgreBulletUtils::convert(jointUpperLimits);
}

void SRBJointBt::initialize() {
#ifndef EXCLUDE_FROM_TEST
	mJoint = new CONSTRAINT_TYPE(*mBodyA, *mBodyB, mFrameInA,
		mFrameInB EXTRAPARAMS);

//	mJoint->setDamping(10000);

	mJoint->enableFeedback(true);
	mJoint->setJointFeedback(new btJointFeedback());

//debug drawing
	mJoint->setDbgDrawSize(btScalar(5.f));

//#if CONSTRAINT_TYPE == btGeneric6DofConstraint
//	// 6DOF constraint uses Euler angles and to define limits
//	// it is assumed that rotational order is :
//	// Z - first, allowed limits are (-PI,PI);
//	// new position of Y - second (allowed limits are
//	// (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
//	// used to prevent constraint from instability on poles;
//	// new position of X, allowed limits are (-PI,PI);
//	// So to simulate ODE Universal joint we should use parent
//	// axis as Z, child axis as Y and limit all other DOFs
//	// Build the frame in world coordinate system first
//	mJoint->setAngularLowerLimit(OgreBulletUtils::convert(mJointMinAngle));
//	mJoint->setAngularUpperLimit(OgreBulletUtils::convert(mJointMaxAngle));
//
//	//	add pitch servo motor
//	((SRBServoMotor*) mMotors[0])->initialize(
//		mJoint->getRotationalLimitMotor(RDOF_PITCH));
//
//	// add yaw servo motor
//	((SRBServoMotor*) mMotors[1])->initialize(
//		mJoint->getRotationalLimitMotor(RDOF_YAW));
//
//	//add roll servo motor
//	((SRBServoMotor*) mMotors[2])->initialize(
//		mJoint->getRotationalLimitMotor(RDOF_ROLL));
//#elif CONSTRAINT_TYPE == btGeneric6DofSpring2Constraint
//	mJoint->setDamping(0,jointPitchDamping);
//	mJoint->setDamping(1,jointYawDamping);
//	mJoint->setDamping(2,jointRollDamping);
//#elif CONSTRAINT_TYPE == btGeneric6DofSpringConstraint
//	mJoint->setDamping(0,jointPitchDamping);
//	mJoint->setDamping(1,jointYawDamping);
//	mJoint->setDamping(2,jointRollDamping);
//#elif CONSTRAINT_TYPE == btPoint2PointConstraint
//	// no damping available
//#elif CONSTRAINT_TYPE == btConeTwistConstraint
//	mJoint->setLimit(mJointMaxAngle.x - mJointMinAngle.x,
//		mJointMaxAngle.y - mJointMinAngle.y,
//		mJointMaxAngle.z - mJointMinAngle.z);
//
//	//	add pitch servo motor
//	((SRBServoMotor*) mMotors[0])->initialize(NULL);
//
//	// add yaw servo motor
//	((SRBServoMotor*) mMotors[1])->initialize(NULL);
//
//	//add roll servo motor
//	((SRBServoMotor*) mMotors[2])->initialize(NULL);
//#endif

	// 6DOF constraint uses Euler angles and to define limits
	// it is assumed that rotational order is :
	// Z - first, allowed limits are (-PI,PI);
	// new position of Y - second (allowed limits are
	// (-PI/2 + epsilon, PI/2 - epsilon), where epsilon is a small positive number
	// used to prevent constraint from instability on poles;
	// new position of X, allowed limits are (-PI,PI);
	// So to simulate ODE Universal joint we should use parent
	// axis as Z, child axis as Y and limit all other DOFs
	// Build the frame in world coordinate system first
	mJoint->setAngularLowerLimit(OgreBulletUtils::convert(mJointMinAngle));
	mJoint->setAngularUpperLimit(OgreBulletUtils::convert(mJointMaxAngle));

	//	add pitch servo motor
	((SRBServoMotor*) mMotors[0])->initialize(
		mJoint->getRotationalLimitMotor(RDOF_PITCH));

	// add yaw servo motor
	((SRBServoMotor*) mMotors[1])->initialize(
		mJoint->getRotationalLimitMotor(RDOF_YAW));

	//add roll servo motor
	((SRBServoMotor*) mMotors[2])->initialize(
		mJoint->getRotationalLimitMotor(RDOF_ROLL));
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

	delete mJoint;
	mJoint = NULL;
}

void SRBJointBt::update(double timeSinceLastTick) {

	//apply motor forces
	//TODO: Turn on when you want to use motors
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
			(*motorIterator)->apply(timeSinceLastTick);
		}
	}
}

void SRBJointBt::generateMotors(const btVector3 maxForces,
	const btVector3 lowerLimits, const btVector3 upperLimits) {

	mJointMaxForces = OgreBulletUtils::convert(maxForces);
	mJointMaxAngle = OgreBulletUtils::convert(upperLimits);
	mJointMinAngle = OgreBulletUtils::convert(lowerLimits);

//	add pitch servo motor
	SRBServoMotor* servoMotor = new SRBServoMotor(JointPhysics::RDOF_PITCH,
		maxForces.getX(), lowerLimits.x(), upperLimits.x());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new SRBServoMotor(JointPhysics::RDOF_YAW, maxForces.getY(),
		lowerLimits.y(), upperLimits.y());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new SRBServoMotor(JointPhysics::RDOF_ROLL, maxForces.getZ(),
		lowerLimits.z(), upperLimits.z());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);
}

bool SRBJointBt::equals(const SRBJointBt& SRBJointBt) const {

	if (!JointPhysics::equals(SRBJointBt)) {
		return false;
	}

	/**Comparison of motors*/
	if (mMotors.size() != SRBJointBt.mMotors.size()) {
		return false;
	}
	std::vector<Motor*>::const_iterator it = mMotors.begin();
	std::vector<Motor*>::const_iterator it2 = SRBJointBt.mMotors.begin();
	for (; it != mMotors.end(), it2 != SRBJointBt.mMotors.end(); it++, it2++) {
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

void SRBJointBt::setAngularDamping(double jointPitchDamping,
	double jointYawDamping, double jointRollDamping) {
#if CONSTRAINT_TYPE == btGeneric6DofConstraint
	// no damping available
#elif CONSTRAINT_TYPE == btGeneric6DofSpring2Constraint
	mJoint->setDamping(0,jointPitchDamping);
	mJoint->setDamping(1,jointYawDamping);
	mJoint->setDamping(2,jointRollDamping);
#elif CONSTRAINT_TYPE == btGeneric6DofSpringConstraint
	mJoint->setDamping(0,jointPitchDamping);
	mJoint->setDamping(1,jointYawDamping);
	mJoint->setDamping(2,jointRollDamping);
#elif CONSTRAINT_TYPE == btPoint2PointConstraint
	// no damping available
#elif CONSTRAINT_TYPE == btConeTwistConstraint
	mJoint->setDamping(jointPitchDamping);
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

//	mJoint->enableMotor(true);

}

void SRBJointBt::addToWorld() {
	if (!isInWorld()) {
		mWorld->addConstraint((btTypedConstraint*) mJoint, true);
		JointPhysics::addToWorld();
	}
}

void SRBJointBt::removeFromWorld() {
	if (isInWorld()) {
		mWorld->removeConstraint((btTypedConstraint*) mJoint);
		JointPhysics::removeFromWorld();
	}
}

SRBJointBt* SRBJointBt::clone() {
	return new SRBJointBt(*this);
}

void SRBJointBt::applyJointTorque(int jointIndex, int jointAxisIndex,
	double torque) {

	if (mJoint) {
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
		btVector3 hingeAxisLocalA =
			mJoint->getFrameOffsetA().getBasis().getColumn(col);

		btVector3 hingeAxisLocalB =
			mJoint->getFrameOffsetB().getBasis().getColumn(col);

		btVector3 hingeAxisWorldA =
			mJoint->getRigidBodyA().getWorldTransform().getBasis()
				* hingeAxisLocalA;

		btVector3 hingeAxisWorldB =
			mJoint->getRigidBodyB().getWorldTransform().getBasis()
				* hingeAxisLocalB;

		btVector3 hingeTorqueA = torque * hingeAxisWorldA;
		btVector3 hingeTorqueB = torque * hingeAxisWorldB;

		mJoint->getRigidBodyA().applyTorque(-hingeTorqueA);
		mJoint->getRigidBodyB().applyTorque(hingeTorqueB);
	}
}

double SRBJointBt::getJointPos(int jointIndex, int jointAxisIndex) {
	return mJoint->getAngle(jointAxisIndex);
}

double SRBJointBt::getJointVel(int jointIndex, int jointAxisIndex) {
	//TODO: Find a way to get joint velocity in SRB
	return 0;
//	mJoint->get
}
