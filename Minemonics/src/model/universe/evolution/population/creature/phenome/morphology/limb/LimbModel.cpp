//# corresponding headers
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/Sensor.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/sensor/exteroceptor/Tactioceptor.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

LimbModel::LimbModel() :
		mLimbPhysics(NULL), mCreatureModel(
		NULL), mJointIndex(0) {
}

LimbModel::LimbModel(const LimbModel& limbModel) {
	mLimbPhysics = limbModel.mLimbPhysics->clone();
	mCreatureModel = limbModel.mCreatureModel;
	mJointIndex = limbModel.mJointIndex;
}

LimbModel::~LimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;
}

void LimbModel::initialize(btDynamicsWorld* const world,
		CreatureModel* const creatureModel, const PrimitiveType type,
		const Ogre::Vector3 position, const Ogre::Quaternion orientation,
		const Ogre::Vector3 initialRelativePosition,
		const Ogre::Quaternion initialOrientation,
		const Ogre::Vector3 dimensions, const double mass,
		const double restitution, const double friction,
		const Ogre::ColourValue color, const int ownIndex) {
	ComponentModel::initialize(ComponentModel::LimbComponent, ownIndex);

	// initialize the physics model of the limb
	mLimbPhysics = new LimbBt();
	((LimbBt*) mLimbPhysics)->initialize(world, this, type,
			OgreBulletUtils::convert(position),
			OgreBulletUtils::convert(orientation),
			OgreBulletUtils::convert(initialRelativePosition),
			OgreBulletUtils::convert(initialOrientation),
			OgreBulletUtils::convert(dimensions), btScalar(mass),
			btScalar(restitution), btScalar(friction),
			OgreBulletUtils::convert(color));

	mCreatureModel = creatureModel;

	//TODO: proof of concept, make better.
	Tactioceptor* tactioceptor = new Tactioceptor();
	mSensors.push_back(tactioceptor);
	mTactioceptors.push_back(tactioceptor);
}

void LimbModel::reset(Ogre::Vector3 position) {
	mLimbPhysics->reset(position);
}

void LimbModel::reposition(Ogre::Vector3 position) {
	mLimbPhysics->reposition(position);
}

bool LimbModel::equals(const LimbModel& limbModel) const {

	if (!mLimbPhysics->equals(*limbModel.mLimbPhysics)) {
		return false;
	}

	return true;
}

LimbModel* LimbModel::clone() {
	return new LimbModel(*this);
}

void LimbModel::activateTactioceptors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
			tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(true);
	}
}

void LimbModel::resetSensors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
			tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(false);
	}
}

void LimbModel::update(double timeSinceLastTick) {

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
LimbPhysics* LimbModel::getLimbPhysics() const {
	return mLimbPhysics;
}

/**
 * Get the position of the limb in the physical world.
 * @return The position of the limb in the physical world.
 */
const Ogre::Vector3 LimbModel::getPosition() const {
	return OgreBulletUtils::convert(mLimbPhysics->getPosition());
}

const double LimbModel::getVolume() const {
	return mLimbPhysics->getVolume();
}

/**
 * Get the orientation of the limb in the physical world.
 * @return The orientation of the limb in the physical world.
 */
const Ogre::Quaternion LimbModel::getOrientation() const {
	return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
}

void LimbModel::setInterpenetrationDepth(double interpenetrationDepth) {
	mLimbPhysics->setInterpenetrationDepth(interpenetrationDepth);
}

double LimbModel::getInterpenetrationDepth() {
	return mLimbPhysics->getInterpenetrationDepth();
}

const Ogre::ColourValue LimbModel::getColor() const {
	return Ogre::ColourValue(mLimbPhysics->getColor().x(),
			mLimbPhysics->getColor().y(), mLimbPhysics->getColor().z());
}

const LimbModel::PrimitiveType LimbModel::getPrimitiveType() const {
	return mLimbPhysics->getType();
}

const Ogre::Vector3 LimbModel::getDimensions() const {
	return OgreBulletUtils::convert(mLimbPhysics->getDimensions());
}
