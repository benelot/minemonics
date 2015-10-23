//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/SRBJointModel.hpp>
#include <view/universe/evolution/population/creature/phenome/morphology/joint/JointGraphics.hpp>

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

JointGraphics::JointGraphics(const JointModel* const jointModel) :
	mJointModel(jointModel), mInWorld(false) {
}

JointGraphics::~JointGraphics() {
}

