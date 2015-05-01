//# corresponding headers
#include <controller/environments/Environment.hpp>

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
#include <model/environments/bullet/EnvironmentBt.hpp>
#include <model/environments/EnvironmentPhysics.hpp>

//## view headers
#include <view/environments/EnvironmentGraphics.hpp>

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

