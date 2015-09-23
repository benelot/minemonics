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

FSLimbModel::FSLimbModel() :
	mLimbPhysics(NULL), mCreatureModel(NULL), mParentJointIndex(0) {
}

FSLimbModel::FSLimbModel(const FSLimbModel& limbModel) {
	mLimbPhysics = limbModel.mLimbPhysics->clone();
	mCreatureModel = limbModel.mCreatureModel;
	mParentJointIndex = limbModel.mParentJointIndex;
}

FSLimbModel::~FSLimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;
}

void FSLimbModel::initialize(btDynamicsWorld* const world,
	CreatureModel* const creatureModel, const LimbPhysics::PrimitiveType type,
	const Ogre::Vector3 position, const Ogre::Quaternion orientation,
	const Ogre::Vector3 initialRelativePosition,
	const Ogre::Quaternion initialOrientation, const Ogre::Vector3 dimensions,
	const double mass, const double restitution, const double friction,
	const Ogre::ColourValue color, bool isIntraBodyColliding,
	const std::vector<ComponentModel*>::size_type ownIndex) {
	ComponentModel::initialize(ComponentModel::LimbComponent, ownIndex);

	// initialize the physics model of the limb
	mLimbPhysics = new FSLimbBt();
	mLimbPhysics->initialize(world, this, type, position, orientation,
		initialRelativePosition, initialOrientation, dimensions, mass,
		restitution, friction, color, isIntraBodyColliding);

	mCreatureModel = creatureModel;

	//TODO: proof of concept, make better.
	Tactioceptor* tactioceptor = new Tactioceptor();
	mSensors.push_back(tactioceptor);
	mTactioceptors.push_back(tactioceptor);
}

void FSLimbModel::reset(Ogre::Vector3 position) {
	mLimbPhysics->reset(position);
}

void FSLimbModel::reposition(Ogre::Vector3 position) {
	mLimbPhysics->reposition(position);
}

bool FSLimbModel::equals(const FSLimbModel& limbModel) const {
	if (!ComponentModel::equals(limbModel)) {
		return false;
	}

	if (!mLimbPhysics->equals(*limbModel.mLimbPhysics)) {
		return false;
	}

	return true;
}

FSLimbModel* FSLimbModel::clone() {
	return new FSLimbModel(*this);
}

void FSLimbModel::activateTactioceptors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(true);
	}
}

void FSLimbModel::resetSensors() {
	for (std::vector<Tactioceptor*>::iterator tit = mTactioceptors.begin();
		tit != mTactioceptors.end(); tit++) {
		(*tit)->setTouched(false);
	}
}

void FSLimbModel::update(double timeSinceLastTick) {

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
LimbPhysics* FSLimbModel::getLimbPhysics() const {
	return mLimbPhysics;
}

/**
 * Get the position of the limb in the physical world.
 * @return The position of the limb in the physical world.
 */
const Ogre::Vector3 FSLimbModel::getPosition() const {
	return OgreBulletUtils::convert(mLimbPhysics->getPosition());
}

const double FSLimbModel::getVolume() const {
	return mLimbPhysics->getVolume();
}

/**
 * Get the orientation of the limb in the physical world.
 * @return The orientation of the limb in the physical world.
 */
const Ogre::Quaternion FSLimbModel::getOrientation() const {
	return OgreBulletUtils::convert(mLimbPhysics->getOrientation());
}

void FSLimbModel::setInterpenetrationDepth(double interpenetrationDepth) {
	mLimbPhysics->setInterpenetrationDepth(interpenetrationDepth);
}

void FSLimbModel::calm() {
	mLimbPhysics->calm();
}

double FSLimbModel::getInterpenetrationDepth() {
	return mLimbPhysics->getInterpenetrationDepth();
}

const Ogre::ColourValue FSLimbModel::getColor() const {
	return mLimbPhysics->getColor();
}

const LimbPhysics::PrimitiveType FSLimbModel::getPrimitiveType() const {
	return mLimbPhysics->getType();
}

const Ogre::Vector3 FSLimbModel::getDimensions() const {
	return mLimbPhysics->getDimensions();
}

std::ostream & operator<<(std::ostream &os, const FSLimbModel &limbModel) {
	os << "LimbModel: LimbPhysics=" << (*limbModel.mLimbPhysics)
		<< "/ParentJointIndex=" << limbModel.mParentJointIndex;

	os << "/ChildJointIndices=[";
	for (std::vector<std::vector<FSJointModel*>::size_type>::const_iterator it =
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

const Ogre::Vector3 FSLimbModel::getVelocities() const {
	return mLimbPhysics->getVelocities();
}
