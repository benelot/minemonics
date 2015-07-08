//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <iterator>
#include <vector>

//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h>
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
		mG6DofJoint(NULL), mWorld(NULL) {
	mMotors.clear();
}

JointBt::JointBt(const JointBt& jointBt) :
		mG6DofJoint(NULL), mWorld(NULL) {
	//TODO: Implement copy from jointBt.
}

JointBt::~JointBt() {
	removeFromWorld();

	//delete and nullify the 6DofJoint.
	delete mG6DofJoint;
	mG6DofJoint = NULL;

	// nullify the world reference
	mWorld = NULL;

	//delete and clear the motor vector
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
			delete (*motorIterator);
		}
	}

	mMotors.clear();

	delete mG6DofJoint->getJointFeedback();
}

void JointBt::initialize(btDynamicsWorld* world, btRigidBody* bodyA,
		btRigidBody* bodyB, btTransform& tframeInA, btTransform& tframeInB) {
	mWorld = world;
	mG6DofJoint = new btGeneric6DofSpringConstraint(*bodyA, *bodyB, tframeInA,
			tframeInB, true/*use fixed frame A for linear limits*/);
	mG6DofJoint->setLinearLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setLinearUpperLimit(btVector3(0, 0, 0));

	mG6DofJoint->setAngularLowerLimit(btVector3(0, 0, 0));
	mG6DofJoint->setAngularUpperLimit(btVector3(0, 0, 0));

	mG6DofJoint->setEquilibriumPoint();

	mG6DofJoint->enableFeedback(true);
	btJointFeedback* jfb = new btJointFeedback();
	mG6DofJoint->setJointFeedback(jfb);

	//debug drawing
	mG6DofJoint->setDbgDrawSize(btScalar(5.f));

}

void JointBt::update() {
	//apply motor forces
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
			(*motorIterator)->apply();
		}
	}
}

void JointBt::initializeRotationalLimitMotors(btVector3 maxForces,
		btVector3 maxSpeeds) {
	//add pitch servo motor
	ServoMotor* servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_PITCH,
			mG6DofJoint->getRotationalLimitMotor(RDOF_PITCH), maxForces.getX(),
			maxSpeeds.getX());
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_YAW,
			mG6DofJoint->getRotationalLimitMotor(JointPhysics::RDOF_YAW),
			maxForces.getY(), maxSpeeds.getY());
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::DOF_ROLL,
			mG6DofJoint->getRotationalLimitMotor(JointPhysics::RDOF_ROLL),
			maxForces.getZ(), maxSpeeds.getZ());
	mMotors.push_back(servoMotor);
}

bool JointBt::equals(const JointBt& jointBt) const {
	std::vector<Motor*>::const_iterator it = mMotors.begin();
	std::vector<Motor*>::const_iterator it2 = jointBt.mMotors.begin();
	for (; it != mMotors.end(), it2 != jointBt.mMotors.end(); it++, it2++) {
		if (!(*it)->equals(**(it2))) {
			return false;
		}
	}

	return true;
}

void JointBt::reset(Ogre::Vector3 position) {
	//nothing to be reset
}

void JointBt::reposition(Ogre::Vector3 position) {
	//nothing to be repositioned
}

bool JointBt::isStrained() {
	btVector3 fbA = mG6DofJoint->getJointFeedback()->m_appliedForceBodyA;
	btVector3 fbB = mG6DofJoint->getJointFeedback()->m_appliedForceBodyB;
	btVector3 tbA = mG6DofJoint->getJointFeedback()->m_appliedTorqueBodyA;
	btVector3 tbB = mG6DofJoint->getJointFeedback()->m_appliedTorqueBodyB;
	std::cout << "----------------------" << std::endl;
	std::cout << "Applied impulse: " <<mG6DofJoint->getAppliedImpulse() << std::endl;
	std::cout << "Joint feedback force A: (" << fbA.getX() << "," << fbA.getY() << "," << fbA.getZ() << ")" << std::endl;
	std::cout << "Joint feedback force B: (" << fbB.getX() << "," << fbB.getY() << "," << fbB.getZ() << ")" << std::endl;
	std::cout << "Joint feedback torque A: (" << tbA.getX() << "," << tbA.getY() << "," << tbA.getZ() << ")" << std::endl;
	std::cout << "Joint feedback torque B: (" << tbB.getX() << "," << tbB.getY() << "," << tbB.getZ() << ")" << std::endl;
	std::cout << "----------------------" << std::endl;
	return false;
}

void JointBt::setRotationalLimitMotorEnabled(
		JointPhysics::RotationalDegreeOfFreedom index, bool enable) {
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->getIndex() == index) {
			(*motorIterator)->setEnabled(true);
			break;
		}
	}

	mG6DofJoint->getRotationalLimitMotor(index)->m_enableMotor = enable;
}

void JointBt::addToWorld() {
	mWorld->addConstraint((btTypedConstraint*) mG6DofJoint, true);
}

void JointBt::removeFromWorld() {
	mWorld->removeConstraint((btTypedConstraint*) mG6DofJoint);
}

JointBt* JointBt::clone() {
	return new JointBt(*this);
}
