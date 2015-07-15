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
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbBt.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

LimbModel::LimbModel() :
		mLimbPhysics(NULL), mColor(0, 0, 0), mPrimitiveType(UNKNOWN), mCreatureModel(
		NULL) {
}

LimbModel::LimbModel(const LimbModel& limbModel) {
	mColor = limbModel.mColor;
	mDimensions = limbModel.mDimensions;
	mLimbPhysics = limbModel.mLimbPhysics->clone();
	mPrimitiveType = limbModel.mPrimitiveType;
	mCreatureModel = limbModel.mCreatureModel;
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
			btScalar(restitution), btScalar(friction));

	mCreatureModel = creatureModel;
	mDimensions = dimensions;
	mPrimitiveType = type;
	mColor = color;
}

void LimbModel::reset(Ogre::Vector3 position) {
	mLimbPhysics->reset(position);
}

void LimbModel::reposition(Ogre::Vector3 position) {
	mLimbPhysics->reposition(position);
}

bool LimbModel::equals(const LimbModel& limbModel) const {
	if (mPrimitiveType != limbModel.mPrimitiveType) {
		return false;
	}

	if (mColor != limbModel.mColor) {
		return false;
	}

	if (mDimensions != limbModel.mDimensions) {
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
