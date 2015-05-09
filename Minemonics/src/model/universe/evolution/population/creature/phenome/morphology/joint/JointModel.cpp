//# corresponding header
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointModel.hpp>

//# forward declarations
#ifndef NULL
#define NULL 0
#endif

//# system headers
//## controller headers
//## model headers
#include <LinearMath/btTransform.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/evolution/population/creature/phenome/morphology/joint/JointBt.hpp>

//## view headers
//## utils headers

JointModel::JointModel() :
		mJointPhysics(NULL) {

}

JointModel::~JointModel() {
	delete mJointPhysics;
	mJointPhysics = NULL;
}

void JointModel::initialize(btDynamicsWorld* world, btRigidBody* limbA,
		btRigidBody* limbB, btTransform localA, btTransform localB) {
	mJointPhysics = new JointBt();
	((JointBt*) mJointPhysics)->initialize(world, limbA, limbB, localA, localB);
}
