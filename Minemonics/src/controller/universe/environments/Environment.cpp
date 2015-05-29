//# corresponding headers
#include <controller/universe/environments/Environment.hpp>

//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>

//## view headers
#include <view/universe/environments/EnvironmentGraphics.hpp>

//## utils headers

Environment::Environment() :
		mEnvironmentType(UNKNOWN_ENVIRONMENT_TYPE), mEnvironmentGraphics(
		NULL), mEnvironmentModel(NULL) {
}

Environment::~Environment() {

	delete mEnvironmentGraphics;
	mEnvironmentGraphics = NULL;

	delete mEnvironmentModel;
	mEnvironmentModel = NULL;
}

void Environment::initialize(EnvironmentType environmentType) {
	mEnvironmentType = environmentType;
}

btRigidBody*& Environment::getBody() {
	return ((EnvironmentBt*) mEnvironmentModel->getEnvironmentPhysics())->getBody();
}

void Environment::update() {

}

