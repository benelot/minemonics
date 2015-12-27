//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>

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
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/SRBLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp>

//## view headers
//## utils headers

BoostLogger SRBJointModel::mBoostLogger; /*<! initialize the boost logger*/
SRBJointModel::_Init SRBJointModel::_initializer;
SRBJointModel::SRBJointModel() {
	addSensors();
}

SRBJointModel::SRBJointModel(const SRBJointModel& jointModel) :
	JointModel(jointModel) {
	mParentIndex = jointModel.mParentIndex;
	mChildIndex = jointModel.mChildIndex;
	mOwnIndex = jointModel.mOwnIndex;
	mJointPhysics = jointModel.mJointPhysics->clone();

	addSensors();
}

SRBJointModel::SRBJointModel(btDynamicsWorld* const world,
	SRBLimbModel* const limbA, SRBLimbModel* const limbB,
	const Ogre::Vector3 pivotInW,
	const std::vector<LimbModel*>::size_type indexA,
	const std::vector<LimbModel*>::size_type indexB,
	const std::vector<JointModel*>::size_type ownIndex,
	JointPhysics::JointType type, Ogre::Vector3 jointPitchAxis,
	Ogre::Vector3 jointYawAxis, Ogre::Vector3 jointMinAngle,
	Ogre::Vector3 jointMaxAngle) {
	ComponentModel::initialize(ComponentModel::JointComponent, ownIndex);
	mParentIndex = indexA;
	mChildIndex = indexB;
	mOwnIndex = ownIndex;

	mJointPhysics = new SRBJointBt(world, (SRBLimbBt*) limbA->getLimbPhysics(),
		(SRBLimbBt*) limbB->getLimbPhysics(),
		OgreBulletUtils::convert(pivotInW), type,
		OgreBulletUtils::convert(jointPitchAxis),
		OgreBulletUtils::convert(jointYawAxis),
		OgreBulletUtils::convert(jointMinAngle),
		OgreBulletUtils::convert(jointMaxAngle), mOwnIndex);

	addSensors();
}

SRBJointModel::~SRBJointModel() {
}

void SRBJointModel::initialize() {
	mJointPhysics->initialize();

	mDataSinkPitch.initialize("", 3, 20);
	mDataSinkYaw.initialize("", 3, 20);
	mDataSinkRoll.initialize("", 3, 20);
}

void SRBJointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
	const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void SRBJointModel::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
		jointRollStiffness);
}

void SRBJointModel::setAngularDamping(
	const double springPitchDampingCoefficient,
	double springYawDampingCoefficient, double springRollDampingCoefficient) {
	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
		springYawDampingCoefficient, springRollDampingCoefficient);
}

bool SRBJointModel::equals(const SRBJointModel& jointModel) const {
	if (!ComponentModel::equals(jointModel)) {
		return false;
	}

	if (!((SRBJointBt*) mJointPhysics)->equals(
		(*(SRBJointBt*) jointModel.mJointPhysics))) {
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
	const Ogre::Vector3 lowerLimits, const Ogre::Vector3 upperLimits,
	bool positionControlled) {
	mJointPhysics->generateMotors(OgreBulletUtils::convert(maxForces),
		OgreBulletUtils::convert(lowerLimits),
		OgreBulletUtils::convert(upperLimits), positionControlled);
}

