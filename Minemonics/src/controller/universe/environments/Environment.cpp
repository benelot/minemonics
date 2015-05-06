//# corresponding headers
#include <controller/universe/environments/Environment.hpp>
#include <model/universe/environments/bullet/EnvironmentBt.hpp>
#include <model/universe/environments/EnvironmentPhysics.hpp>
#include <view/universe/environments/EnvironmentGraphics.hpp>

//## utils headers

Environment::Environment() :
		mSimulationMgr(NULL), mEnvironmentType(UNKNOWN_ENVIRONMENT_TYPE), mEnvironmentGraphics(
		NULL), mEnvironmentPhysics(NULL) {
}

Environment::~Environment() {
	mSimulationMgr = NULL;

	delete mEnvironmentGraphics;
	mEnvironmentGraphics = NULL;

	delete mEnvironmentPhysics;
	mEnvironmentPhysics = NULL;
}

void Environment::initialize(SimulationManager* simulationMgr,
		EnvironmentType environmentType) {
	mSimulationMgr = simulationMgr;
	mEnvironmentType = environmentType;
}

btRigidBody*& Environment::getBody() {
	return ((EnvironmentBt*) mEnvironmentPhysics)->getBody();
}

