//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletDynamics/Featherstone/btMultiBody.h>
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

FSJointBt::FSJointBt() :
	mWorld(NULL), mMultiBody(NULL) {
}

FSJointBt::FSJointBt(btDynamicsWorld* const world, btRigidBody* const bodyA,
	btRigidBody* const bodyB, const btTransform& tframeInA,
	const btTransform& tframeInB, JointPhysics::JointType type,
	btVector3 jointPitchAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits, int ownIndex) :
	mMultiBody(NULL) {
	mWorld = world;
	mType = type;

	mJointPitchAxis = OgreBulletUtils::convert(jointPitchAxis);
	mJointMinAngle = OgreBulletUtils::convert(jointLowerLimits);
	mJointMaxAngle = OgreBulletUtils::convert(jointUpperLimits);

	mMotors.clear();

	mJointIndex = ownIndex;
}

FSJointBt::FSJointBt(const FSJointBt& jointBt) {
	mWorld = jointBt.mWorld;
	mInWorld = jointBt.mInWorld;
	mMultiBody = jointBt.mMultiBody;

	for (std::vector<Motor*>::const_iterator mit = jointBt.mMotors.begin();
		mit != jointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

void FSJointBt::initialize() {
}

FSJointBt::~FSJointBt() {
	removeFromWorld();

	// nullify the world reference
	mWorld = NULL;
}

void FSJointBt::update(double timeSinceLastTick) {

	//apply motor forces
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()) {
			(*motorIterator)->apply(timeSinceLastTick);
		}
	}
}

void FSJointBt::generateMotors(const btVector3 maxForces,
	const btVector3 lowerLimits, const btVector3 upperLimits,
	bool positionControlled) {
//	add pitch servo motor
	FSServoMotor* servoMotor = new FSServoMotor(JointPhysics::RDOF_PITCH,
		maxForces.getX(), lowerLimits.x(), upperLimits.x(), positionControlled);
	servoMotor->initialize();
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new FSServoMotor(JointPhysics::RDOF_YAW, maxForces.getY(),
		lowerLimits.y(), upperLimits.y(), positionControlled);
	servoMotor->initialize();
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new FSServoMotor(JointPhysics::RDOF_ROLL, maxForces.getZ(),
		lowerLimits.z(), upperLimits.z(), positionControlled);
	servoMotor->initialize();
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);
}

bool FSJointBt::equals(const FSJointBt& jointBt) const {

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

void FSJointBt::reset(const Ogre::Vector3 position) {
	//nothing to be reset
}

void FSJointBt::reposition(const Ogre::Vector3 position) {
	//nothing to be repositioned
}

void FSJointBt::setAngularDamping(double jointPitchDamping,
	double jointYawDamping, double jointRollDamping) {
	// Not implemented in FS Joint bt
}

void FSJointBt::setRotationalLimitMotorEnabled(
	const JointPhysics::RotationalDegreeOfFreedom index, const bool enable) {
	std::vector<Motor*>::iterator motorIterator = mMotors.begin();
	for (; motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->getIndex() == index) {
			(*motorIterator)->setEnabled(true);
			break;
		}
	}
}

void FSJointBt::addToWorld() {
	if (!isInWorld()) {
		JointPhysics::addToWorld();
	}
}

void FSJointBt::removeFromWorld() {
	if (isInWorld()) {
		JointPhysics::removeFromWorld();
	}
}

FSJointBt* FSJointBt::clone() {
	return new FSJointBt(*this);
}

void FSJointBt::applyJointTorque(int jointAxisIndex, double torque) {
	mMultiBody->addJointTorque(mJointIndex, torque);
}

double FSJointBt::getJointPos(int jointAxisIndex) {
	return mMultiBody->getJointPos(mJointIndex);
}

double FSJointBt::getJointVel(int jointAxisIndex) {
	return mMultiBody->getJointVel(mJointIndex);
}

