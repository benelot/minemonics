/*
 * Environment.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "Environment.h"

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
#include "model/environments/EnvironmentPhysics.h"
#include "model/environments/bullet/EnvironmentBt.h"

//## view headers
#include "view/environments/EnvironmentGraphics.h"

//## utils headers

Environment::Environment() :
		mSimulationMgr(NULL), mEnvironmentType(UNKNOWN_ENVIRONMENT_TYPE), mEnvironmentGraphics(
		NULL), mEnvironmentPhysics(NULL) {
}

Environment::~Environment() {
	// TODO Auto-generated destructor stub
}

void Environment::initialize(SimulationManager* simulationMgr,
		EnvironmentType environmentType) {
	mSimulationMgr = simulationMgr;
	mEnvironmentType = environmentType;
}

btRigidBody*& Environment::getBody() {
	return ((EnvironmentBt*) mEnvironmentPhysics)->getBody();
}

