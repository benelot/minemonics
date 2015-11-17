#ifndef CONFIGURATION_CONTROLCONFIGURATION_H_
#define CONFIGURATION_CONTROLCONFIGURATION_H_

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
//## model headers
#include <model/universe/evolution/population/creature/genome/controller/ControllerGene.hpp>

//## view headers
//## utils headers

/**
 * @brief		The configuration for the controllers of the creatures.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class ControlConfiguration {
public:
	static const double JOINT_MIN_FREQUENCY = 0.1;

	static const double JOINT_MAX_FREQUENCY = 4;

	static const double JOINT_MIN_AMPLITUDE = 0;

	static const double JOINT_MAX_AMPLITUDE = 0.5;

	static const double JOINT_MIN_X_OFFSET = 0;

	static const double JOINT_MAX_X_OFFSET = 2 * M_PI;

	static const double JOINT_MIN_Y_OFFSET = 0;

	static const double JOINT_MAX_Y_OFFSET = 1;

	static const ControllerGene::ControllerType CONTROLLER_TYPE = ControllerGene::ChaoticControllerGene;
};

#endif /* CONFIGURATION_CONTROLCONFIGURATION_H_ */
