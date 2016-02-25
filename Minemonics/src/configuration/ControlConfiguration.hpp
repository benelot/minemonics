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
	static const double SINE_MIN_FREQUENCY; /**!<Hz Lowest frequency of joint movement*/

	static const double SINE_MAX_FREQUENCY; /**!< Hz Highest frequency of joint movement */

	static const double SINE_MIN_AMPLITUDE; /**!< Lowest amplitude of joint movement */

	static const double SINE_MAX_AMPLITUDE; /**!< Highest amplitude of joint movement */

	static const double SINE_MIN_X_OFFSET; /**!< Lowest X Offset (shift) of the center of joint movement */

	static const double SINE_MAX_X_OFFSET; /**!< Highest X Offset (shift) of the center of joint movement*/

	static const double SINE_MIN_Y_OFFSET; /**!< Lowest Y Offset of the center of joint movement */

	static const double SINE_MAX_Y_OFFSET; /**!< Highest Y Offset of the center of joint movement */

	static const ControllerGene::ControllerType CONTROLLER_TYPE; /*!< Controller gene type */

	static const bool IS_POSITION_CONTROLLED;

	static const double CHAOS_MIN_INIT_CONDITION;

	static const double CHAOS_MAX_INIT_CONDITION;

	static const double CHAOS_MIN_INTEGRATION_SPEED;

	static const double CHAOS_MAX_INTEGRATION_SPEED;

	static const double CHAOS_BASE_INTEGRATION_SPEED;

	static const double SIGN_DEPENDENT_OUTPUT;

	static const double PERTURBATION_RANGE_X;

	static const double PERTURBATION_RANGE_Y;

	static const double PERTURBATION_RANGE_Z;

	static const bool RANDOM_PERTURBATION;
};

#endif /* CONFIGURATION_CONTROLCONFIGURATION_H_ */
