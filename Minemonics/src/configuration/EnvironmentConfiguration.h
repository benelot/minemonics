/*
 * EnvironmentConfiguration.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef ENVIRONMENTCONFIGURATION_H_
#define ENVIRONMENTCONFIGURATION_H_

#include "controller/environments/Environment.h"

class EnvironmentConfiguration {
public:
	/**
	 * The environment type used in the simulator
	 */
	// TODO: Make the environment type changeable from within the simulator.
	static const Environment::EnvironmentType ENVIRONMENT_TYPE = Environment::PLANE;
};

#endif /* ENVIRONMENTCONFIGURATION_H_ */
