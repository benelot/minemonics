//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers

FSJointModel::FSJointModel() :
	mJointPhysics(NULL), mParentIndex(-1), mChildIndex(-1), mOwnIndex(-1) {

}

FSJointModel::FSJointModel(const FSJointModel& jointModel) :
	mParentIndex(jointModel.mParentIndex), mChildIndex(jointModel.mChildIndex), mOwnIndex(
		jointModel.mOwnIndex) {
	mJointPhysics = jointModel.mJointPhysics->clone();
}

FSJointModel::~FSJointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
}

void FSJointModel::initialize(btDynamicsWorld* const world,
	btRigidBody* const limbA, btRigidBody* const limbB,
	const btTransform localA, const btTransform localB,
	const std::vector<FSLimbModel*>::size_type indexA,
	const std::vector<FSLimbModel*>::size_type indexB,
	const std::vector<FSLimbModel*>::size_type ownIndex,
	FSJointPhysics::JointType type, bool jointPitchEnabled, bool jointYawEnabled,
	bool jointRollEnabled, Ogre::Vector3 jointPitchAxis,
	Ogre::Vector3 jointLowerLimits, Ogre::Vector3 jointUpperLimits) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mParentIndex = indexA;
	mChildIndex = indexB;
	mOwnIndex = ownIndex;
	mLocalA = localA;
	mLocalB = localB;
	mJointPhysics = new FSJointBt();
	((FSJointBt*) mJointPhysics)->initialize(world, limbA, limbB, localA, localB,
		type, jointPitchEnabled, jointYawEnabled, jointRollEnabled,
		OgreBulletUtils::convert(jointPitchAxis),
		OgreBulletUtils::convert(jointLowerLimits),
		OgreBulletUtils::convert(jointUpperLimits));

	//TODO: proof of concept, make better.
//	JointAngleProprioceptor* angleceptor = new JointAngleProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH);
//	mSensors.push_back(angleceptor);
//	mAngleceptors.push_back(angleceptor);
//
//	JointForceProprioceptor* forceceptor = new JointForceProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH);
//	mSensors.push_back(forceceptor);
//	mForceceptors.push_back(forceceptor);
//
//	JointLimitProprioceptor* limitceptor = new JointLimitProprioceptor(
//			((JointBt*) mJointPhysics)->getG6DofJoint(),
//			JointPhysics::RDOF_PITCH, JointLimitProprioceptor::BOTH_LIMITS);
//	mSensors.push_back(limitceptor);
//	mLimitceptors.push_back(limitceptor);
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

//bool JointModel::isStrained() {
//	return mJointPhysics->isStrained();
//}

void JointModel::generateMotors(const Ogre::Vector3 maxForces,
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits) {
	mJointPhysics->generateMotors(OgreBulletUtils::convert(maxForces),
		OgreBulletUtils::convert(lowerLimits),
		OgreBulletUtils::convert(upperLimits));
}

void FSJointModel::enableAngularMotor(const bool pitchEnable,
	const bool yawEnable, const bool rollEnable) {
	mJointPhysics->setRotationalLimitMotorEnabled(FSJointPhysics::RDOF_PITCH,
		pitchEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(FSJointPhysics::RDOF_YAW,
		yawEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(FSJointPhysics::RDOF_ROLL,
		rollEnable);
}

