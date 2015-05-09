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
#include <utils/ogre3D/OgreBulletUtils.hpp>

//## utils headers

LimbModel::LimbModel() :
		mLimbPhysics(NULL) {
}

LimbModel::~LimbModel() {
	delete mLimbPhysics;
	mLimbPhysics = NULL;
}

void LimbModel::initialize(btDynamicsWorld* world, void* limb,
		MorphologyConfiguration::PrimitiveType type, Ogre::Vector3 position,
		Ogre::Quaternion orientation,Ogre::Vector3 dimensions, double mass) {

	// initialize the physics model of the limb
	mLimbPhysics = new LimbBt();
	((LimbBt*) mLimbPhysics)->initialize(world, limb, type,
			OgreBulletUtils::convert(position),
			OgreBulletUtils::convert(orientation),
			OgreBulletUtils::convert(dimensions), btScalar(mass));
}
