//# corresponding header
//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

JointModel::JointModel() :
		mJointPhysics(NULL) {

}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
}

