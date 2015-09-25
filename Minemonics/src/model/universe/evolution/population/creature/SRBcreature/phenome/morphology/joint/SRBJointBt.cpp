//# corresponding header
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/joint/SRBJointBt.hpp>
#include <configuration/Definitions.hpp>
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
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/effector/motor/SRBServoMotor.hpp>

//## view headers
//## utils headers

SRBJointBt::SRBJointBt() :
	mWorld(NULL), mJoint(NULL), mMotorTarget(0, 0, 0, 1) {
	mMotors.clear();
}

SRBJointBt::SRBJointBt(const SRBJointBt& SRBJointBt) {
	mWorld = SRBJointBt.mWorld;
	mJoint = SRBJointBt.mJoint;
	mInWorld = SRBJointBt.mInWorld;

	for (std::vector<Motor*>::const_iterator mit = SRBJointBt.mMotors.begin();
		mit != SRBJointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

void SRBJointBt::initialize(btDynamicsWorld* const world,
	btRigidBody* const bodyA, btRigidBody* const bodyB,
	const btTransform& tframeInA, const btTransform& tframeInB,
	JointPhysics::JointType type, bool jointPitchEnabled, bool jointYawEnabled,
	bool jointRollEnabled, btVector3 jointPitchAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits) {
	mWorld = world;
	mJoint = new CONSTRAINT_TYPE(*bodyA, *bodyB, tframeInA,
		tframeInB EXTRAPARAMS);

//	mJoint->setDamping(10000);

	mJoint->enableFeedback(true);
	mJoint->setJointFeedback(new btJointFeedback());

	//debug drawing
	mJoint->setDbgDrawSize(btScalar(5.f));

	mType = type;
	mJointPitchEnabled = jointPitchEnabled;
	mJointYawEnabled = jointYawEnabled;
	mJointRollEnabled = jointRollEnabled;

	mJointPitchAxis = OgreBulletUtils::convert(jointPitchAxis);
	mJointMinAngle = OgreBulletUtils::convert(jointLowerLimits);
	mJointMaxAngle = OgreBulletUtils::convert(jointUpperLimits);

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
			//TODO:Reenable motors when interpenetration problems are fixed.
			(*motorIterator)->apply(timeSinceLastTick);
		}
	}
}

void SRBJointBt::generateMotors(const btVector3 maxForces,
	const btVector3 lowerLimits, const btVector3 upperLimits) {
//	add pitch servo motor
	SRBServoMotor* servoMotor = new SRBServoMotor();
	servoMotor->initialize(JointPhysics::RDOF_PITCH,
		mJoint->getRotationalLimitMotor(RDOF_PITCH), maxForces.getX(),
		lowerLimits.x(), upperLimits.x());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new SRBServoMotor();
	servoMotor->initialize(JointPhysics::RDOF_YAW,
		mJoint->getRotationalLimitMotor(RDOF_YAW), maxForces.getY(),
		lowerLimits.y(), upperLimits.y());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new SRBServoMotor();
	servoMotor->initialize(JointPhysics::RDOF_ROLL,
		mJoint->getRotationalLimitMotor(RDOF_ROLL), maxForces.getZ(),
		lowerLimits.z(), upperLimits.z());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);
}

bool SRBJointBt::equals(const SRBJointBt& SRBJointBt) const {

	if (JointPhysics::equals(SRBJointBt)) {
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

//bool SRBJointBt::isStrained() {
//TODO: Broken
//	btVector3 fbA = mJoint->getJointFeedback()->m_appliedForceBodyA;
//	btVector3 fbB = mJoint->getJointFeedback()->m_appliedForceBodyB;
//	btVector3 tbA = mJoint->getJointFeedback()->m_appliedTorqueBodyA;
//	btVector3 tbB = mJoint->getJointFeedback()->m_appliedTorqueBodyB;
//	if (abs(fbA.getX()) > PhysicsConfiguration::TORQUE_THRESHOLD
//			&& abs(fbA.getY()) > PhysicsConfiguration::TORQUE_THRESHOLD
//			&& abs(fbA.getZ()) > PhysicsConfiguration::TORQUE_THRESHOLD
//			&& abs(fbB.getX()) > PhysicsConfiguration::TORQUE_THRESHOLD
//			&& abs(fbB.getY()) > PhysicsConfiguration::TORQUE_THRESHOLD
//			&& abs(fbB.getZ()) > PhysicsConfiguration::TORQUE_THRESHOLD) {
//		std::cout << "----------------------" << std::endl;
//		std::cout << "Applied impulse: " << mJoint->getAppliedImpulse()
//				<< std::endl;
//
//		std::cout << "Joint feedback force A: (" << fbA.getX() << ","
//				<< fbA.getY() << "," << fbA.getZ() << ")" << std::endl;
//		std::cout << "Joint feedback force B: (" << fbB.getX() << ","
//				<< fbB.getY() << "," << fbB.getZ() << ")" << std::endl;
//		std::cout << "Joint feedback torque A: (" << tbA.getX() << ","
//				<< tbA.getY() << "," << tbA.getZ() << ")" << std::endl;
//		std::cout << "Joint feedback torque B: (" << tbB.getX() << ","
//				<< tbB.getY() << "," << tbB.getZ() << ")" << std::endl;
//		std::cout << "----------------------" << std::endl;
//	}
//	return false;
//}

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
