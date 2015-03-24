/*
 * Environment.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class EnvironmentGraphics;
class EnvironmentPhysics;

//# system headers
//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class Environment {
public:
	enum EnvironmentType {
		UNKNOWN_ENVIRONMENT_TYPE = 0, HILLS = 1, PLANE = 2, OPENSEA = 3
	};

	EnvironmentType mEnvironmentType;

	Environment();
	virtual ~Environment();
	void initialize(SimulationManager* simulationMgr,
			EnvironmentType environmentType);

	btRigidBody*& getBody();

protected:
	SimulationManager* mSimulationMgr;
	EnvironmentPhysics* mEnvironmentPhysics;
	EnvironmentGraphics* mEnvironmentGraphics;

};

#endif /* ENVIRONMENT_H_ */
