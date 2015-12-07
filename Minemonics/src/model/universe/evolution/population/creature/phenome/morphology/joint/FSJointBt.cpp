//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btMatrix3x3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/MorphologyConfiguration.hpp>
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/Motor.hpp>

//## view headers
//## utils headers
#include <utils/MathUtils.hpp>

BoostLogger FSJointBt::mBoostLogger; /*<! initialize the boost logger*/
FSJointBt::_Init FSJointBt::_initializer;
FSJointBt::FSJointBt() :
	mWorld(NULL), mMultiBody(NULL), mPitchMotor(NULL), mYawMotor(NULL), mRollMotor(
	NULL) {
}

FSJointBt::FSJointBt(btDynamicsWorld* const world, FSLimbBt* const limbA,
	FSLimbBt* const limbB, const btVector3& pivotInW,
	JointPhysics::JointType type, btVector3 jointPitchAxis,
	btVector3 jointYawAxis, btVector3 jointLowerLimits,
	btVector3 jointUpperLimits, int ownIndex) :
	mMultiBody(NULL), mPitchMotor(NULL), mYawMotor(NULL), mRollMotor(NULL) {
	mWorld = ((btMultiBodyDynamicsWorld*) world);
	mType = type;

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

	mLimbMassForceScalar = limbA->getVolume() * limbB->getVolume();

	// now get constraint frame in local coordinate systems
	mFrameInA = limbA->getRigidBody()->getCenterOfMassTransform().inverse() * frameInW;
	mFrameInB = limbB->getRigidBody()->getCenterOfMassTransform().inverse() * frameInW;

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

FSJointBt::FSJointBt(const FSJointBt& jointBt) {
	mWorld = jointBt.mWorld;
	mInWorld = jointBt.mInWorld;
	mMultiBody = jointBt.mMultiBody;

	mPitchMotor = jointBt.mPitchMotor;
	mYawMotor = jointBt.mYawMotor;
	mRollMotor = jointBt.mRollMotor;

	for (std::vector<Motor*>::const_iterator mit = jointBt.mMotors.begin();
		mit != jointBt.mMotors.end(); mit++) {
		mMotors.push_back(*mit);
	}
}

void FSJointBt::initialize() {
	mFrameInA.setOrigin(OgreBulletUtils::convert(mLocalAPosition));
	mFrameInA.setRotation(OgreBulletUtils::convert(mLocalAOrientation));
	mFrameInB.setOrigin(OgreBulletUtils::convert(mLocalBPosition));
	mFrameInB.setRotation(OgreBulletUtils::convert(mLocalBOrientation));

	if (!mPitchMotor) {
		mPitchMotor = new btMultiBodyJointMotor(mMultiBody, mJointIndex, 0,
			PhysicsConfiguration::FIXED_STEP_SIZE_SEC * mJointDamping.x * mLimbMassForceScalar);
	}
}

FSJointBt::~FSJointBt() {
	removeFromWorld();

	mWorld = NULL; 	// nullify the world reference
}

void FSJointBt::update(double timeSinceLastTick) {

	//apply motor forces
	for (std::vector<Motor*>::iterator motorIterator = mMotors.begin();
		motorIterator != mMotors.end(); motorIterator++) {
		if ((*motorIterator)->isEnabled()
			&& MorphologyConfiguration::BODY_MOTORS_ENABLED) {
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
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	// add yaw servo motor
	servoMotor = new FSServoMotor(JointPhysics::RDOF_YAW, maxForces.getY(),
		lowerLimits.y(), upperLimits.y(), positionControlled);
	servoMotor->initialize();
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	//add roll servo motor
	servoMotor = new FSServoMotor(JointPhysics::RDOF_ROLL, maxForces.getZ(),
		lowerLimits.z(), upperLimits.z(), positionControlled);
	servoMotor->initialize();
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

void FSJointBt::setAngularStiffness(double jointPitchStiffness,
	double jointYawStiffness, double jointRollStiffness) {
	// Not implementedt in FS Joint Bt
	if (false) {
	} else {
		mJointStiffness.x = jointPitchStiffness;
		mJointStiffness.y = jointYawStiffness;
		mJointStiffness.z = jointRollStiffness;
	}
}

void FSJointBt::setAngularDamping(double jointPitchDamping,
	double jointYawDamping, double jointRollDamping) {

	mJointDamping.x = jointPitchDamping;
	mJointDamping.y = jointYawDamping;
	mJointDamping.z = jointRollDamping;

	if (mPitchMotor) {
		mPitchMotor->setMaxAppliedImpulse(jointPitchDamping);
	}

	//TODO: Yaw and roll motor are not used anyway
//	if (!mYawMotor) {
//
//	}
//
//	if (!mRollMotor) {
//
//	}
}

void FSJointBt::addToWorld() {
	if (!isInWorld()) {
		JointPhysics::addToWorld();

		if (mPitchMotor) {
			mWorld->addMultiBodyConstraint(mPitchMotor);
		}
	}
}

void FSJointBt::removeFromWorld() {
	if (isInWorld()) {
		JointPhysics::removeFromWorld();

		if (mPitchMotor) {
			mWorld->removeMultiBodyConstraint(mPitchMotor);
		}
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

double FSJointBt::getJointVel(int jointAxisIndex, double timeSinceLastTick,
	double lastJointPosition) {
	return mMultiBody->getJointVel(mJointIndex);
}

