#ifndef ENVIRONMENTCONFIGURATION_H_
#define ENVIRONMENTCONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/environments/Environment.hpp>

//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class EnvironmentConfiguration {
public:
	/**
	 * The environment type used in the simulator
	 */
	// TODO: Make the environment type changeable from within the simulator.
	static const Environment::EnvironmentType ENVIRONMENT_TYPE =
			Environment::PLANE;
};

#endif /* ENVIRONMENTCONFIGURATION_H_ */
