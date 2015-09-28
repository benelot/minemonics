//# corresponding headers
#include <configuration/Definitions.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbModel.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <LinearMath/btScalar.h>
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/ComponentModel.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/limb/SRBLimbModel.hpp>
#include <model/universe/evolution/population/creature/SRBcreature/phenome/morphology/sensor/exteroceptor/Tactioceptor.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

SRBLimbModel::SRBLimbModel() {
}

SRBLimbModel::SRBLimbModel(const SRBLimbModel& SRBLimbModel) {
	mLimbPhysics = SRBLimbModel.mLimbPhysics->clone();
	mCreatureModel = SRBLimbModel.mCreatureModel;
	mParentJointIndex = SRBLimbModel.mParentJointIndex;
}

SRBLimbModel::~SRBLimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;
}

void SRBLimbModel::initialize(btDynamicsWorld* const world,
	CreatureModel* const creatureModel, const LimbPhysics::PrimitiveType type,
	const Ogre::Vector3 position, const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const std::vector<ComponentModel*>::size_type ownIndex) {
	ComponentModel::initialize(ComponentModel::LimbComponent, ownIndex);

	// initialize the physics model of the limb
	mLimbPhysics = new SRBLimbBt();
	mLimbPhysics->initialize(world, this, type, position, orientation,
		initialRelativePosition, initialOrientation, dimensions, mass,
		restitution, friction, color, isIntraBodyColliding);

	mCreatureModel = creatureModel;

	//TODO: proof of concept, make better.
	Tactioceptor* tactioceptor = new Tactioceptor();
	mSensors.push_back(tactioceptor);
	mTactioceptors.push_back(tactioceptor);
}

void SRBLimbModel::reset(Ogre::Vector3 position) {
	mLimbPhysics->reset(position);
}

void SRBLimbModel::reposition(Ogre::Vector3 position) {
	mLimbPhysics->reposition(position);
}

bool SRBLimbModel::equals(const SRBLimbModel& SRBLimbModel) const {
	if (!ComponentModel::equals(SRBLimbModel)) {
		return false;
	}

	if (!mLimbPhysics->equals(*SRBLimbModel.mLimbPhysics)) {
		return false;
	}

	return true;
}

SRBLimbModel* SRBLimbModel::clone() {
	return new SRBLimbModel(*this);
}

void SRBLimbModel::activateTactioceptors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(true);
	}
}

void SRBLimbModel::resetSensors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(false);
	}
}

void SRBLimbModel::update(double timeSinceLastTick) {

	for (std::vector<Sensor*>::iterator sit = mSensors.begin();
		sit != mSensors.end(); sit++) {
		(*sit)->update(timeSinceLastTick);
	}

//	std::cout << std::endl << "TactileSensors:";
//	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
//			tit != mTactioceptors.end(); tit++) {
//		std::cout << (*tit)->isTouched() << "|";
//	}
//	std::cout << std::endl;

// reset the sensors when they are processed
	resetSensors();
}

/**
 * The the limb physics model of the limb.
 * @return The limb physics model of the limb.
 */
LimbPhysics* SRBLimbModel::getLimbPhysics() const {
	return mLimbPhysics;
}

/**
 * Get the position of the limb in the physical world.
 * @return The position of the limb in the physical world.
 */
const Ogre::Vector3 SRBLimbModel::getPosition() const {
	return OgreBulletUtils::convert(mLimbPhysics->getPosition());
}

const double SRBLimbModel::getVolume() const {
	return mLimbPhysics->getVolume();
}

/**
 * Get the orientation of the limb in the physical world.
 * @return The orientation of the limb in the physical world.
 */
const Ogre::Quaternion SRBLimbModel::getOrientation() const {
	return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
}

void SRBLimbModel::setInterpenetrationDepth(double interpenetrationDepth) {
	mLimbPhysics->setInterpenetrationDepth(interpenetrationDepth);
}

void SRBLimbModel::calm() {
	mLimbPhysics->calm();
}

double SRBLimbModel::getInterpenetrationDepth() {
	return mLimbPhysics->getInterpenetrationDepth();
}

const Ogre::ColourValue SRBLimbModel::getColor() const {
	return mLimbPhysics->getColor();
}

const LimbPhysics::PrimitiveType SRBLimbModel::getPrimitiveType() const {
	return mLimbPhysics->getType();
}

const Ogre::Vector3 SRBLimbModel::getDimensions() const {
	return mLimbPhysics->getDimensions();
}

std::ostream & operator<<(std::ostream &os, const SRBLimbModel &SRBLimbModel) {
	os << "SRBLimbModel: LimbPhysics=" << (*SRBLimbModel.mLimbPhysics)
		<< "/ParentJointIndex=" << SRBLimbModel.mParentJointIndex;

	os << "/ChildJointIndices=[";
	for (std::vector<std::vector<JointModel*>::size_type>::const_iterator it =
		SRBLimbModel.mChildJointIndices.begin(); /**!< The vector of child joint indices.*/
	it != SRBLimbModel.mChildJointIndices.end(); it++) {
		os << (*it);
		os << "||";
	}
	os << "]/Sensors=[";

	for (std::vector<Tactioceptor*>::const_iterator it =
		SRBLimbModel.mTactioceptors.begin(); /**!< The vector of tactioceptors.*/
	it != SRBLimbModel.mTactioceptors.end(); it++) {
		os << (**it);
		os << "||";
	}
	os << "]";
	return os;
}

const Ogre::Vector3 SRBLimbModel::getVelocities() const {
	return mLimbPhysics->getVelocities();
}
