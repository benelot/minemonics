//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointPhysics.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/effector/motor/ServoMotor.hpp>

//## view headers
//## utils headers

JointPhysics::JointPhysics() :
	mInWorld(false), mType(JointPhysics::UNKNOWN_JOINT), mJointPitchEnabled(
		true), mJointRollEnabled(true), mJointYawEnabled(true), mJointMaxAngle(
		0, 0, 0), mJointMaxForces(0, 0, 0), mJointMaxSpeeds(0, 0, 0), mJointMinAngle(
		0, 0, 0), mJointPitchAxis(1, 0, 0) {
}

JointPhysics::~JointPhysics() {
}

bool JointPhysics::equals(const JointPhysics& jointPhysics) const {
	if (mInWorld != jointPhysics.mInWorld) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}

	if (mJointPitchAxis != jointPhysics.mJointPitchAxis) {
		return false;
	}

	if (mJointPitchEnabled != jointPhysics.mJointPitchEnabled) {
		return false;
	}

	if (mJointMinAngle != jointPhysics.mJointMinAngle) {
		return false;
	}

	if (mJointMaxAngle != jointPhysics.mJointMaxAngle) {
		return false;
	}

	if (mJointMaxForces != jointPhysics.mJointMaxForces) {
		return false;
	}

	if (mJointMaxSpeeds != jointPhysics.mJointMaxSpeeds) {
		return false;
	}

	if (mJointRollEnabled != jointPhysics.mJointRollEnabled) {
		return false;
	}

	if (mJointYawEnabled != jointPhysics.mJointYawEnabled) {
		return false;
	}

	if (mType != jointPhysics.mType) {
		return false;
	}
	return true;
}

void JointPhysics::generateMotors(const Ogre::Vector3 maxForces) {
	mJointMaxForces = maxForces;

	// add pitch servo motor
	ServoMotor* servoMotor = new ServoMotor();
	servoMotor->initialize(JointPhysics::RDOF_PITCH, maxForces.x,
		mJointMinAngle.x, mJointMaxAngle.x);
	//TODO: Hack, make better
	servoMotor->setEnabled(true);
	mMotors.push_back(servoMotor);

	if (mType == SPHERICAL_JOINT) {
		// add yaw servo motor
		servoMotor = new ServoMotor();
		servoMotor->initialize(JointPhysics::RDOF_YAW, maxForces.y,
			mJointMinAngle.y, mJointMaxAngle.y);

		//TODO: Hack, make better
		servoMotor->setEnabled(true);
		mMotors.push_back(servoMotor);

		//add roll servo motor
		servoMotor = new ServoMotor();
		servoMotor->initialize(JointPhysics::RDOF_ROLL, maxForces.z,
			mJointMinAngle.z, mJointMaxSpeeds.z);

		//TODO: Hack, make better
		servoMotor->setEnabled(true);
		mMotors.push_back(servoMotor);
	}
}
