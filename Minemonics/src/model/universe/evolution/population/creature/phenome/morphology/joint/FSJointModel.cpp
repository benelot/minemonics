//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointModel.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/FSLimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/FSJointBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointAngleceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointForceceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointLimitceptor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/proprioceptor/JointVelocityceptor.hpp>

//## view headers
//## utils headers

BoostLogger FSJointModel::mBoostLogger; /*<! initialize the boost logger*/
FSJointModel::_Init FSJointModel::_initializer;
FSJointModel::FSJointModel() {
	addSensors();
}

FSJointModel::FSJointModel(const FSJointModel& jointModel) {
	mParentIndex = jointModel.mParentIndex;
	mChildIndex = jointModel.mChildIndex;
	mOwnIndex = jointModel.mOwnIndex;
	mJointPhysics = jointModel.mJointPhysics->clone();

	addSensors();
}

FSJointModel::FSJointModel(btDynamicsWorld* const world,
	FSLimbModel* const limbA, FSLimbModel* const limbB,
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

	mJointPhysics = new FSJointBt(world,
		((FSLimbBt*) limbA->getLimbPhysics()),
		((FSLimbBt*) limbB->getLimbPhysics()),
		OgreBulletUtils::convert(pivotInW), type,
		OgreBulletUtils::convert(jointPitchAxis),
		OgreBulletUtils::convert(jointYawAxis),
		OgreBulletUtils::convert(jointMinAngle),
		OgreBulletUtils::convert(jointMaxAngle), mOwnIndex);

	addSensors();
}

FSJointModel::~FSJointModel() {
}

void FSJointModel::initialize() {
	mJointPhysics->initialize();

	mDataSinkPitch.initialize("", 3, 20);
	mDataSinkYaw.initialize("", 3, 20);
	mDataSinkRoll.initialize("", 3, 20);

}

void FSJointModel::setAngularLimits(const Ogre::Vector3 angularLowerLimit,
	const Ogre::Vector3 angularUpperLimit) {
	mJointPhysics->setAngularLimits(angularLowerLimit, angularUpperLimit);
}

void FSJointModel::setAngularStiffness(const double jointPitchStiffness,
	const double jointYawStiffness, const double jointRollStiffness) {
	mJointPhysics->setAngularStiffness(jointPitchStiffness, jointYawStiffness,
		jointRollStiffness);
}

void FSJointModel::setAngularDamping(const double springPitchDampingCoefficient,
	double springYawDampingCoefficient, double springRollDampingCoefficient) {
	mJointPhysics->setAngularDamping(springPitchDampingCoefficient,
		springYawDampingCoefficient, springRollDampingCoefficient);
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

