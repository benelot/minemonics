//# corresponding headers
#include <model/universe/environments/EnvironmentModel.hpp>

//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
#include <controller/SaveController.hpp>

//## model headers
#include <model/universe/environments/bullet/EnvironmentBt.hpp>
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

EnvironmentModel::EnvironmentModel() :
	mEnvironmentPhysics(NULL), mPhysicsController(NULL), mInWorld(false), mType(
		PLANE) {

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
		((EnvironmentBt*) mEnvironmentPhysics)->getBody(),
		PhysicsConfiguration::COL_GROUND,
		PhysicsConfiguration::GROUND_COLLIDES_WITH);
	mInWorld = true;
}

void EnvironmentModel::removeFromWorld() {
	mPhysicsController->removeBody(
		((EnvironmentBt*) mEnvironmentPhysics)->getBody());
	mInWorld = false;
}

void EnvironmentModel::save() {
	SaveController<EnvironmentModel> environmentModelSaver;
	environmentModelSaver.save(*this, mSerializationPath.c_str());
}

void EnvironmentModel::load() {
	SaveController<EnvironmentModel> environmentModelSaver;
	environmentModelSaver.restore(*this, mSerializationPath.c_str());
}
