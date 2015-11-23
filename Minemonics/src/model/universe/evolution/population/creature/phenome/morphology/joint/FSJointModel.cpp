//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>

#include <LinearMath/btTransform.h>
#include <LinearMath/btVector3.h>
#include <OgreQuaternion.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>

//## view headers
//## utils headers

#include <utils/ogre3D/OgreBulletUtils.hpp>

BoostLogger FSJointModel::mBoostLogger; /*<! initialize the boost logger*/
FSJointModel::_Init FSJointModel::_initializer;
FSJointModel::FSJointModel() {

}

FSJointModel::FSJointModel(const FSJointModel& jointModel) {
	mParentIndex = jointModel.mParentIndex;
	mChildIndex = jointModel.mChildIndex;
	mOwnIndex = jointModel.mOwnIndex;
	mJointPhysics = jointModel.mJointPhysics->clone();
}

FSJointModel::FSJointModel(btDynamicsWorld* const world,
	btRigidBody* const limbA, btRigidBody* const limbB,
	const Ogre::Vector3 pivotInW,
	const std::vector<FSLimbModel*>::size_type indexA,
	const std::vector<FSLimbModel*>::size_type indexB,
	const std::vector<FSJointModel*>::size_type ownIndex,
	JointPhysics::JointType type, Ogre::Vector3 jointPitchAxis,
	Ogre::Vector3 jointYawAxis, Ogre::Vector3 jointMinAngle,
	Ogre::Vector3 jointMaxAngle) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mParentIndex = indexA;
	mChildIndex = indexB;
	mOwnIndex = ownIndex;

	mJointPhysics = new FSJointBt(world, limbA, limbB,
		OgreBulletUtils::convert(pivotInW), type,
		OgreBulletUtils::convert(jointPitchAxis),
		OgreBulletUtils::convert(jointYawAxis),
		OgreBulletUtils::convert(jointMinAngle),
		OgreBulletUtils::convert(jointMaxAngle), mOwnIndex);
}

FSJointModel::~FSJointModel() {
}

void FSJointModel::initialize() {

	mJointPhysics->initialize();

	addSensors();
}

void FSJointModel::addSensors() {
	JointAngleceptor* angleceptor = new JointAngleceptor(this,
		JointPhysics::RDOF_PITCH);
	mSensors.push_back(angleceptor);
	mAngleceptors.push_back(angleceptor);

	angleceptor = new JointAngleceptor(this, JointPhysics::RDOF_YAW);
	mSensors.push_back(angleceptor);
	mAngleceptors.push_back(angleceptor);

	angleceptor = new JointAngleceptor(this, JointPhysics::RDOF_ROLL);
	mSensors.push_back(angleceptor);
	mAngleceptors.push_back(angleceptor);

	JointVelocityceptor* velocityceptor = new JointVelocityceptor(this,
		JointPhysics::RDOF_PITCH);
	mSensors.push_back(velocityceptor);
	mVelocityceptors.push_back(velocityceptor);

	velocityceptor = new JointVelocityceptor(this, JointPhysics::RDOF_YAW);
	mSensors.push_back(velocityceptor);
	mVelocityceptors.push_back(velocityceptor);

	velocityceptor = new JointVelocityceptor(this, JointPhysics::RDOF_ROLL);
	mSensors.push_back(velocityceptor);
	mVelocityceptors.push_back(velocityceptor);

	JointForceceptor* forceceptor = new JointForceceptor(this,
		JointPhysics::RDOF_PITCH);
	mSensors.push_back(forceceptor);
	mForceceptors.push_back(forceceptor);

	forceceptor = new JointForceceptor(this, JointPhysics::RDOF_YAW);
	mSensors.push_back(forceceptor);
	mForceceptors.push_back(forceceptor);

	forceceptor = new JointForceceptor(this, JointPhysics::RDOF_ROLL);
	mSensors.push_back(forceceptor);
	mForceceptors.push_back(forceceptor);

	JointLimitceptor* limitceptor = new JointLimitceptor(this,
		JointPhysics::RDOF_PITCH, JointLimitceptor::BOTH_LIMITS);
	mSensors.push_back(limitceptor);
	mLimitceptors.push_back(limitceptor);

	limitceptor = new JointLimitceptor(this, JointPhysics::RDOF_YAW,
		JointLimitceptor::BOTH_LIMITS);
	mSensors.push_back(limitceptor);
	mLimitceptors.push_back(limitceptor);

	limitceptor = new JointLimitceptor(this, JointPhysics::RDOF_ROLL,
		JointLimitceptor::BOTH_LIMITS);
	mSensors.push_back(limitceptor);
	mLimitceptors.push_back(limitceptor);
}

void FSJointModel::update(double timeSinceLastTick) {
	mJointPhysics->update(timeSinceLastTick);

	for (std::vector<Sensor*>::iterator sit = mSensors.begin();
		sit != mSensors.end(); sit++) {
		(*sit)->update(timeSinceLastTick);
	}

//	std::cout << std::endl << "AngleSensors:";
//	for (std::vector<JointAngleProprioceptor*>::iterator tit = mAngleceptors.begin();
//			tit != mAngleceptors.end(); tit++) {
//		std::cout << (*tit)->getAngle() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "ForceSensors:";
//	for (std::vector<JointForceProprioceptor*>::iterator tit = mForceceptors.begin();
//			tit != mForceceptors.end(); tit++) {
//		std::cout << (*tit)->getForce() << "|";
//	}
//	std::cout << std::endl;
//
//	std::cout << std::endl << "LimitSensors:";
//	for (std::vector<JointLimitProprioceptor*>::iterator tit = mLimitceptors.begin();
//			tit != mLimitceptors.end(); tit++) {
//		std::cout << (*tit)->getLimitError() << "|";
//	}
//	std::cout << std::endl;
}

void FSJointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
	const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void FSJointModel::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
//	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
//			jointRollStiffness);
}

void FSJointModel::setAngularDamping(const double springPitchDampingCoefficient,
	double springYawDampingCoefficient, double springRollDampingCoefficient) {
//	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
//			springYawDampingCoefficient, springRollDampingCoefficient);
}

bool FSJointModel::equals(const FSJointModel& jointModel) const {
	if (!ComponentModel::equals(jointModel)) {
		return false;
	}

	if (!((FSJointBt*) mJointPhysics)->equals(
		(*(FSJointBt*) jointModel.mJointPhysics))) {
		return false;
	}

	if (mParentIndex != jointModel.mParentIndex) {
		return false;
	}

	if (mChildIndex != jointModel.mChildIndex) {
		return false;
	}

	if (mOwnIndex != jointModel.mOwnIndex) {
		return false;
	}

	if (mComponentType != jointModel.mComponentType) {
		return false;
	}

	return true;
}

void FSJointModel::reset(const Ogre::Vector3 position) {
	mJointPhysics->reset(position);
}

void FSJointModel::reposition(const Ogre::Vector3 position) {
	mJointPhysics->reposition(position);
}

FSJointModel* FSJointModel::clone() {
	return new FSJointModel(*this);
}

void FSJointModel::generateMotors(const Ogre::Vector3 maxForces,
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits,
	bool positionControlled) {
	mJointPhysics->generateMotors(OgreBulletUtils::convert(maxForces),
		OgreBulletUtils::convert(lowerLimits),
		OgreBulletUtils::convert(upperLimits), positionControlled);
}

void FSJointModel::enableAngularMotor(const bool pitchEnable,
	const bool yawEnable, const bool rollEnable) {
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_PITCH,
		pitchEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_YAW,
		yawEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_ROLL,
		rollEnable);
}

