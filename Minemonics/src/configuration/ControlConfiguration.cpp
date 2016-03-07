//# corresponding headers
#include <configuration/ControlConfiguration.hpp>

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
//## view headers
//## utils headers

const double ControlConfiguration::SINE_MIN_FREQUENCY = 0.5; /**!<Hz Lowest frequency of joint movement*/

const double ControlConfiguration::SINE_MAX_FREQUENCY = 4; /**!< Hz Highest frequency of joint movement */

const double ControlConfiguration::SINE_MIN_AMPLITUDE = 0; /**!< Lowest amplitude of joint movement */

const double ControlConfiguration::SINE_MAX_AMPLITUDE = 0.5; /**!< Highest amplitude of joint movement */

const double ControlConfiguration::SINE_MIN_X_OFFSET = 0; /**!< Lowest X Offset (shift) of the center of joint movement */

const double ControlConfiguration::SINE_MAX_X_OFFSET = 2 * M_PI; /**!< Highest X Offset (shift) of the center of joint movement*/

const double ControlConfiguration::SINE_MIN_Y_OFFSET = 0; /**!< Lowest Y Offset of the center of joint movement */

const double ControlConfiguration::SINE_MAX_Y_OFFSET = 1; /**!< Highest Y Offset of the center of joint movement */

const ControllerGene::ControllerType ControlConfiguration::CONTROLLER_TYPE =
	ControllerGene::ChaoticControllerGene; /*!< Controller gene type */

const bool ControlConfiguration::IS_POSITION_CONTROLLED = false;

const double ControlConfiguration::CHAOS_MIN_INIT_CONDITION = -0.5f;

const double ControlConfiguration::CHAOS_MAX_INIT_CONDITION = 0.5f;

const double ControlConfiguration::CHAOS_MIN_INTEGRATION_SPEED = 0.001f; /**!< Must be below one*/

const double ControlConfiguration::CHAOS_MAX_INTEGRATION_SPEED = 10; /**!< Must be higher than one*/

const double ControlConfiguration::CHAOS_BASE_INTEGRATION_SPEED = 0.0005f;

const double ControlConfiguration::SIGN_DEPENDENT_OUTPUT = true;

const double ControlConfiguration::PERTURBATION_RANGE_X = 1e-4f;

const double ControlConfiguration::PERTURBATION_RANGE_Y = 1e-4f;

const double ControlConfiguration::PERTURBATION_RANGE_Z = 1e-4f;

const bool ControlConfiguration::RANDOM_PERTURBATION = false;
