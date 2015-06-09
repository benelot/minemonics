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
		mInWorld(false), mRestitution(0.5), mFriction(0.8) {
}

LimbPhysics::~LimbPhysics() {
}

bool LimbPhysics::equals(const LimbPhysics& limbPhysics) const {
	if (mInWorld != limbPhysics.mInWorld) {
		return false;
	}

	if (mRestitution != limbPhysics.mRestitution) {
		return false;
	}

	if (mFriction != limbPhysics.mFriction) {
		return false;
	}

	return true;
}
