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
#include <model/universe/evolution/population/creature/CreatureModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbModel.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

LimbModel::LimbModel() :
	mLimbPhysics(NULL), mCreatureModel(NULL), mParentJointIndex(0) {
}

LimbModel::LimbModel(const LimbModel& limbModel) {
	mLimbPhysics = limbModel.mLimbPhysics->clone();
	mCreatureModel = limbModel.mCreatureModel;
	mParentJointIndex = limbModel.mParentJointIndex;
}

LimbModel::~LimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;
}

void LimbModel::initialize(btDynamicsWorld* const world,
	CreatureModel* const creatureModel, const LimbPhysics::PrimitiveType type,
	const Ogre::Vector3 position, const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const std::vector<ComponentModel*>::size_type ownIndex) {
	ComponentModel::initialize(ComponentModel::LimbComponent, ownIndex);

	// initialize the physics model of the limb
	mLimbPhysics = new LimbBt();
	((LimbBt*) mLimbPhysics)->initialize(world, this, type, position,
		OgreBulletUtils::convert(orientation),
		OgreBulletUtils::convert(initialRelativePosition),
		OgreBulletUtils::convert(initialOrientation), dimensions,
		btScalar(mass), btScalar(restitution), btScalar(friction), color,
		isIntraBodyColliding);

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
	if (!ComponentModel::equals(limbModel)) {
		return false;
	}

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

void LimbModel::calm() {
	mLimbPhysics->calm();
}

double LimbModel::getInterpenetrationDepth() {
	return mLimbPhysics->getInterpenetrationDepth();
}

const Ogre::ColourValue LimbModel::getColor() const {
	return mLimbPhysics->getColor();
}

const LimbPhysics::PrimitiveType LimbModel::getPrimitiveType() const {
	return mLimbPhysics->getType();
}

const Ogre::Vector3 LimbModel::getDimensions() const {
	return mLimbPhysics->getDimensions();
}

std::ostream & operator<<(std::ostream &os, const LimbModel &limbModel) {
	os << "LimbModel: LimbPhysics=" << (*limbModel.mLimbPhysics)
		<< "/ParentJointIndex=" << limbModel.mParentJointIndex;

	os << "/ChildJointIndices=[";
	for (std::vector<std::vector<JointModel*>::size_type>::const_iterator it =
		limbModel.mChildJointIndices.begin(); /**!< The vector of child joint indices.*/
	it != limbModel.mChildJointIndices.end(); it++) {
		os << (*it);
		os << "||";
	}
	os << "]/Sensors=[";

	for (std::vector<Tactioceptor*>::const_iterator it =
		limbModel.mTactioceptors.begin(); /**!< The vector of tactioceptors.*/
	it != limbModel.mTactioceptors.end(); it++) {
		os << (**it);
		os << "||";
	}
	os << "]";
	return os;
}
