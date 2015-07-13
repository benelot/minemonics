//# corresponding headers
#include <model/universe/environments/EnvironmentModel.hpp>

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
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//## view headers
//## utils headers

EnvironmentModel::EnvironmentModel() :
		mEnvironmentPhysics(NULL), mPhysicsController(NULL), mInWorld(false) {

}

EnvironmentModel::~EnvironmentModel() {
	delete mEnvironmentPhysics;
	mEnvironmentPhysics = NULL;

	delete mPhysicsController;
	mPhysicsController = NULL;
}

bool EnvironmentModel::isInWorld() const {
	return mInWorld;
}

void EnvironmentModel::addToWorld() {
	mPhysicsController->addBody(
			((EnvironmentBt*) mEnvironmentPhysics)->getBody());
	mInWorld = true;
}

void EnvironmentModel::removeFromWorld() {
	mPhysicsController->removeBody(
			((EnvironmentBt*) mEnvironmentPhysics)->getBody());
	mInWorld = false;
}
