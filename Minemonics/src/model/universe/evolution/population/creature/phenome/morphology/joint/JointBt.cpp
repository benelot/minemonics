//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//# forward declarations
//# system headers
#include <iostream>
#include <vector>

//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <BulletDynamics/Featherstone/btMultiBodyDynamicsWorld.h>
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

//## view headers
//## utils headers

JointBt::JointBt() :
	mWorld(NULL) {
	mMotors.clear();
}

JointBt::JointBt(const JointBt& jointBt) {
	mWorld = jointBt.mWorld;
	mInWorld = jointBt.mInWorld;

	for (std::vector<Motor*>::const_iterator mit = jointBt.mMotors.begin();
		mit != jointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

void JointBt::initialize(btDynamicsWorld* const world, btRigidBody* const bodyA,
	btRigidBody* const bodyB, const btTransform& tframeInA,
	const btTransform& tframeInB, JointPhysics::JointType type,
	bool jointPitchEnabled, bool jointYawEnabled, bool jointRollEnabled,
	btVector3 jointPitchAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits) {
	mWorld = world;
	mType = type;
	mJointPitchEnabled = jointPitchEnabled;
	mJointYawEnabled = jointYawEnabled;
	mJointRollEnabled = jointRollEnabled;

	mJointPitchAxis = OgreBulletUtils::convert(jointPitchAxis);
	mJointMinAngle = OgreBulletUtils::convert(jointLowerLimits);
	mJointMaxAngle = OgreBulletUtils::convert(jointUpperLimits);

}

JointBt::~JointBt() {
	removeFromWorld();

	// nullify the world reference
	mWorld = NULL;

	//delete and clear the motor vector
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		delete (*motorIterator);
	}

	mMotors.clear();
}

void JointBt::update(double timeSinceLastTick) {

	//apply motor forces
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
			(*motorIterator)->apply(timeSinceLastTick);
		}
	}

//	isStrained();
}

//void JointBt::initializeRotationalLimitMotors(btMultiBody* multiBody,
//	const int ownIndex, const btVector3 maxForces, const btVector3 maxSpeeds,
//	const btVector3 lowerLimits, const btVector3 upperLimits) {
//	// add pitch servo motor
//	ServoMotor* servoMotor = new ServoMotor();
//	servoMotor->initialize(multiBody, ownIndex, JointPhysics::RDOF_PITCH,
//		maxForces.getX(), maxSpeeds.getX(), lowerLimits.getX(),
//		upperLimits.getX());
//	((btMultiBodyDynamicsWorld*) mWorld)->addMultiBodyConstraint(
//		servoMotor->getJointMotor());
//	//TODO: Hack, make better
//	servoMotor->setEnabled(true);
//	mMotors.push_back(servoMotor);
//
//	// add yaw servo motor
//	servoMotor = new ServoMotor();
//	servoMotor->initialize(multiBody, ownIndex, JointPhysics::RDOF_YAW,
//		maxForces.getY(), maxSpeeds.getY(), lowerLimits.getY(),
//		upperLimits.getY());
//	((btMultiBodyDynamicsWorld*) mWorld)->addMultiBodyConstraint(
//		servoMotor->getJointMotor());
//	//TODO: Hack, make better
//	servoMotor->setEnabled(true);
//	mMotors.push_back(servoMotor);
//
//	//add roll servo motor
//	servoMotor = new ServoMotor();
//	servoMotor->initialize(multiBody, ownIndex, JointPhysics::RDOF_ROLL,
//		maxForces.getZ(), maxSpeeds.getZ(), lowerLimits.getZ(),
//		upperLimits.getZ());
//	((btMultiBodyDynamicsWorld*) mWorld)->addMultiBodyConstraint(
//		servoMotor->getJointMotor());
//	//TODO: Hack, make better
//	servoMotor->setEnabled(true);
//	mMotors.push_back(servoMotor);
//}

bool JointBt::equals(const JointBt& jointBt) const {

	if (JointPhysics::equals(jointBt)) {
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

void JointBt::reset(const Ogre::Vector3 position) {
	//nothing to be reset
}

void JointBt::reposition(const Ogre::Vector3 position) {
	//nothing to be repositioned
}

bool JointBt::isStrained() {
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
}

void JointBt::setRotationalLimitMotorEnabled(
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

void JointBt::addToWorld() {
	if (!isInWorld()) {
//		mWorld->addConstraint((btTypedConstraint*) mJoint, true);
		JointPhysics::addToWorld();
	}
}

void JointBt::removeFromWorld() {
	if (isInWorld()) {
//		mWorld->removeConstraint((btTypedConstraint*) mJoint);
		JointPhysics::removeFromWorld();
	}
}

JointBt* JointBt::clone() {
	return new JointBt(*this);
}
