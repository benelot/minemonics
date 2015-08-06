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
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpring2Constraint.h>
#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//## view headers
//## utils headers

JointBt::JointBt() :
		mWorld(NULL), mG6DofJoint(NULL) {
	mMotors.clear();
}

JointBt::JointBt(const JointBt& jointBt) {
	mWorld = jointBt.mWorld;
	mG6DofJoint = jointBt.mG6DofJoint;
	mInWorld = jointBt.mInWorld;

	for (std::vector<Motor*>::const_iterator mit = jointBt.mMotors.begin();
			mit != jointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

JointBt::JointBt(btDynamicsWorld* const world, btRigidBody* const bodyA,
		btRigidBody* const bodyB, const btTransform& tframeInA,
		const btTransform& tframeInB) {
	mWorld = world;
	mG6DofJoint = new CONSTRAINT_TYPE(*bodyA, *bodyB, tframeInA,
			tframeInB EXTRAPARAMS);
	mG6DofJoint->setLinearLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setLinearUpperLimit(btVector3(0, 0, 0));

	mG6DofJoint->setAngularLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setAngularUpperLimit(btVector3(0, 0, 0));

	//springs
	mG6DofJoint->enableSpring(0, true);
	mG6DofJoint->enableSpring(1, true);
	mG6DofJoint->enableSpring(2, true);
	mG6DofJoint->enableSpring(3, true);
	mG6DofJoint->enableSpring(4, true);
	mG6DofJoint->enableSpring(5, true);
	mG6DofJoint->setStiffness(0, 100);
	mG6DofJoint->setStiffness(1, 100);
	mG6DofJoint->setStiffness(2, 100);
	mG6DofJoint->setStiffness(3, 100);
	mG6DofJoint->setStiffness(4, 100);
	mG6DofJoint->setStiffness(5, 100);

#ifdef USE_6DOF2
	mG6DofJoint->setDamping(0, 0);
	mG6DofJoint->setDamping(1, 0);
	mG6DofJoint->setDamping(2, 0);
	mG6DofJoint->setDamping(3, 0);
	mG6DofJoint->setDamping(4, 0);
	mG6DofJoint->setDamping(5, 0);
#else
	mG6DofJoint->setDamping(0, 1);
	mG6DofJoint->setDamping(1, 1);
	mG6DofJoint->setDamping(2, 1);
	mG6DofJoint->setDamping(3, 1);
	mG6DofJoint->setDamping(4, 1);
	mG6DofJoint->setDamping(5, 1);
#endif

	mG6DofJoint->setEquilibriumPoint(0, 0);
	mG6DofJoint->setEquilibriumPoint(1, 0);
	mG6DofJoint->setEquilibriumPoint(2, 0);
	mG6DofJoint->setEquilibriumPoint(3, 0);
	mG6DofJoint->setEquilibriumPoint(4, 0);
	mG6DofJoint->setEquilibriumPoint(5, 0);

	mG6DofJoint->enableFeedback(true);
	mG6DofJoint->setJointFeedback(new btJointFeedback());

	//debug drawing
	mG6DofJoint->setDbgDrawSize(btScalar(5.f));

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

	delete mG6DofJoint;
	mG6DofJoint = NULL;
}

void JointBt::update(double timeSinceLastTick) {

	//apply motor forces
	//TODO: Turn on when you want to use motors
//	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
//			motorIterator != mMotors.end(); motorIterator++) {
//		if ((*motorIterator)->isEnabled()) {
//			(*motorIterator)->apply(timeSinceLastTick);
//		}
//	}
}

void JointBt::initializeRotationalLimitMotors(const btVector3 maxForces,
		const btVector3 maxSpeeds) {
	//add pitch servo motor
	ServoMotor* servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_PITCH,
			mG6DofJoint->getRotationalLimitMotor(RDOF_PITCH), maxForces.getX(),
			maxSpeeds.getX());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_YAW,
			mG6DofJoint->getRotationalLimitMotor(JointPhysics::RDOF_YAW),
			maxForces.getY(), maxSpeeds.getY());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_ROLL,
			mG6DofJoint->getRotationalLimitMotor(JointPhysics::RDOF_ROLL),
			maxForces.getZ(), maxSpeeds.getZ());
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);
}

bool JointBt::equals(const JointBt& jointBt) const {

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
	btVector3 fbA = mG6DofJoint->getJointFeedback()->m_appliedForceBodyA;
	btVector3 fbB = mG6DofJoint->getJointFeedback()->m_appliedForceBodyB;
	btVector3 tbA = mG6DofJoint->getJointFeedback()->m_appliedTorqueBodyA;
	btVector3 tbB = mG6DofJoint->getJointFeedback()->m_appliedTorqueBodyB;
	std::cout << "----------------------" << std::endl;
	std::cout << "Applied impulse: " << mG6DofJoint->getAppliedImpulse()
			<< std::endl;
	std::cout << "Joint feedback force A: (" << fbA.getX() << "," << fbA.getY()
			<< "," << fbA.getZ() << ")" << std::endl;
	std::cout << "Joint feedback force B: (" << fbB.getX() << "," << fbB.getY()
			<< "," << fbB.getZ() << ")" << std::endl;
	std::cout << "Joint feedback torque A: (" << tbA.getX() << "," << tbA.getY()
			<< "," << tbA.getZ() << ")" << std::endl;
	std::cout << "Joint feedback torque B: (" << tbB.getX() << "," << tbB.getY()
			<< "," << tbB.getZ() << ")" << std::endl;
	std::cout << "----------------------" << std::endl;
	return false;
}

void JointBt::setRotationalLimitMotorEnabled(
		const JointPhysics::RotationalDegreeOfFreedom index,
		const bool enable) {
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->getIndex() == index) {
			(*motorIterator)->setEnabled(true);
			break;
		}
	}

#ifdef USE_6DOF2
	mG6DofJoint->enableMotor(2+index, true);

#else
	mG6DofJoint->getRotationalLimitMotor(index)->m_enableMotor = true;

#endif

}

void JointBt::addToWorld() {
	if (!isInWorld()) {
		mWorld->addConstraint((btTypedConstraint*) mG6DofJoint, true);
		JointPhysics::addToWorld();
	}
}

void JointBt::removeFromWorld() {
	if (isInWorld()) {
		mWorld->removeConstraint((btTypedConstraint*) mG6DofJoint);
		JointPhysics::removeFromWorld();
	}
}

JointBt* JointBt::clone() {
	return new JointBt(*this);
}
