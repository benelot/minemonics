/*
 * Environment.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include <controller/environments/Environment.hpp>
#include <model/environments/bullet/EnvironmentBt.hpp>
#include <model/environments/EnvironmentPhysics.hpp>
#include <view/environments/EnvironmentGraphics.hpp>

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

