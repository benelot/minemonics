//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>

#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>

//## view headers
//## utils headers

SRBJointModel::SRBJointModel() {

}

SRBJointModel::SRBJointModel(const SRBJointModel& SRBJointModel) :
	JointModel(SRBJointModel) {
}

SRBJointModel::SRBJointModel(btDynamicsWorld* const world,
	btRigidBody* const limbA, btRigidBody* const limbB,
	const btTransform localA, const btTransform localB,
	const std::vector<LimbModel*>::size_type indexA,
	const std::vector<LimbModel*>::size_type indexB,
	const std::vector<LimbModel*>::size_type ownIndex,
	JointPhysics::JointType type, bool jointPitchEnabled, bool jointYawEnabled,
	bool jointRollEnabled, Ogre::Vector3 jointPitchAxis,
	Ogre::Vector3 jointMinAngle, Ogre::Vector3 jointMaxAngle) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mParentIndex = indexA;
	mChildIndex = indexB;
	mOwnIndex = ownIndex;
	mLocalA = localA;
	mLocalB = localB;
	mLocalAPosition = OgreBulletUtils::convert(localA.getOrigin());
	mLocalBPosition = OgreBulletUtils::convert(localB.getOrigin());

	mLocalAOrientation = OgreBulletUtils::convert(localB.getRotation());
	mLocalBOrientation = OgreBulletUtils::convert(localB.getRotation());

	mJointPhysics = new SRBJointBt(world, limbA, limbB, localA,
		localB, type, jointPitchEnabled, jointYawEnabled, jointRollEnabled,
		OgreBulletUtils::convert(jointPitchAxis),
		OgreBulletUtils::convert(jointMinAngle),
		OgreBulletUtils::convert(jointMaxAngle));

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

SRBJointModel::~SRBJointModel() {
}

void SRBJointModel::initialize(){
	mLocalA.setOrigin(OgreBulletUtils::convert(mLocalAPosition));
	mLocalA.setRotation(OgreBulletUtils::convert(mLocalAOrientation));
	mLocalB.setOrigin(OgreBulletUtils::convert(mLocalBPosition));
	mLocalB.setRotation(OgreBulletUtils::convert(mLocalBOrientation));

	((SRBJointBt*)mJointPhysics)->setFrameInA(mLocalA);
	((SRBJointBt*)mJointPhysics)->setFrameInB(mLocalB);
	mJointPhysics->initialize();
}

void SRBJointModel::update(double timeSinceLastTick) {
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

void SRBJointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
	const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void SRBJointModel::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
//	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
//			jointRollStiffness);
}

void SRBJointModel::setAngularDamping(
	const double springPitchDampingCoefficient,
	double springYawDampingCoefficient, double springRollDampingCoefficient) {
//	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
//			springYawDampingCoefficient, springRollDampingCoefficient);
}

bool SRBJointModel::equals(const SRBJointModel& SRBJointModel) const {
	if (!ComponentModel::equals(SRBJointModel)) {
		return false;
	}

	if (!((SRBJointBt*) mJointPhysics)->equals(
		(*(SRBJointBt*) SRBJointModel.mJointPhysics))) {
		return false;
	}

	if (mParentIndex != SRBJointModel.mParentIndex) {
		return false;
	}

	if (mChildIndex != SRBJointModel.mChildIndex) {
		return false;
	}

	if (mOwnIndex != SRBJointModel.mOwnIndex) {
		return false;
	}

	if (mComponentType != SRBJointModel.mComponentType) {
		return false;
	}

	return true;
}

void SRBJointModel::reset(const Ogre::Vector3 position) {
	mJointPhysics->reset(position);
}

void SRBJointModel::reposition(const Ogre::Vector3 position) {
	mJointPhysics->reposition(position);
}

SRBJointModel* SRBJointModel::clone() {
	return new SRBJointModel(*this);
}

void SRBJointModel::generateMotors(const Ogre::Vector3 maxForces,
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits) {
	mJointPhysics->generateMotors(OgreBulletUtils::convert(maxForces),
		OgreBulletUtils::convert(lowerLimits),
		OgreBulletUtils::convert(upperLimits));
}

void SRBJointModel::enableAngularMotor(const bool pitchEnable,
	const bool yawEnable, const bool rollEnable) {
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_PITCH,
		pitchEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_YAW,
		yawEnable);
	mJointPhysics->setRotationalLimitMotorEnabled(JointPhysics::RDOF_ROLL,
		rollEnable);
}

