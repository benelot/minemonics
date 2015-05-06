//# corresponding header
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
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers

JointBt::JointBt() :
		mG6DofJoint(NULL), mWorld(NULL) {
	mMotors.clear();
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
	servoMotor->initialize(0, mG6DofJoint->getRotationalLimitMotor(0),
			maxForces.getX(), maxSpeeds.getX());
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(1, mG6DofJoint->getRotationalLimitMotor(1),
			maxForces.getY(), maxSpeeds.getY());
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new ServoMotor();
	servoMotor->initialize(2, mG6DofJoint->getRotationalLimitMotor(2),
			maxForces.getZ(), maxSpeeds.getZ());
	mMotors.push_back(servoMotor);
}

void JointBt::setRotationalLimitMotorEnabled(int index, bool enable) {
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
