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
#include <OgreLight.h>

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
		HILLS = 1, PLANE = 2, OPENSEA = 3
	};

	EnvironmentType mEnvironmentType;

	Environment(SimulationManager* simulationMgr,
			EnvironmentType environmentType);
	virtual ~Environment();
	void initialize(Ogre::Light* l);

	btRigidBody*& getBody();

private:
	SimulationManager* mSimulationMgr;
	EnvironmentPhysics* mEnvironmentPhysics;
	EnvironmentGraphics* mEnvironmentGraphics;

};

#endif /* ENVIRONMENT_H_ */
