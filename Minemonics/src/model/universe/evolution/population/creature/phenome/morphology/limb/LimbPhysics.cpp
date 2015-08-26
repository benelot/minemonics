//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/limb/LimbPhysics.hpp>

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
//## view headers
//## utils headers

LimbPhysics::LimbPhysics() :
		mInWorld(false), mRestitution(0.5), mFriction(0.8), mInitialRelativeXPosition(
				0), mInitialRelativeYPosition(0), mInitialRelativeZPosition(0), mInitialXOrientation(
				0), mInitialYOrientation(0), mInitialZOrientation(0), mInitialWOrientation(
				1), mMass(0), mVolume(0), mType(UNKNOWN), mInterpenetrationDepth(
				0), mColor(0, 0, 0) {
}

LimbPhysics::~LimbPhysics() {
}

bool LimbPhysics::equals(const LimbPhysics& limbPhysics) const {

	if(mType != limbPhysics.mType){
		return false;
	}

	if (mInitialRelativeXPosition != limbPhysics.mInitialRelativeXPosition) {
		return false;
	}

	if (mInitialRelativeYPosition != limbPhysics.mInitialRelativeYPosition) {
		return false;
	}

	if (mInitialRelativeZPosition != limbPhysics.mInitialRelativeZPosition) {
		return false;
	}

	if (mInitialXOrientation != limbPhysics.mInitialXOrientation) {
		return false;
	}

	if (mInitialYOrientation != limbPhysics.mInitialYOrientation) {
		return false;
	}

	if (mInitialZOrientation != limbPhysics.mInitialZOrientation) {
		return false;
	}

	if (mInitialWOrientation != limbPhysics.mInitialWOrientation) {
		return false;
	}

	if (mInWorld != limbPhysics.mInWorld) {
		return false;
	}

	if (mRestitution != limbPhysics.mRestitution) {
		return false;
	}

	if (mFriction != limbPhysics.mFriction) {
		return false;
	}

	if (mMass != limbPhysics.mMass) {
		return false;
	}

	return true;
}
