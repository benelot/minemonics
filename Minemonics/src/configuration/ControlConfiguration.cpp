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

const double ControlConfiguration::JOINT_MIN_FREQUENCY = 0.1; /**!<Hz Lowest frequency of joint movement*/

const double ControlConfiguration::JOINT_MAX_FREQUENCY = 4; /**!< Hz Highest frequency of joint movement */

const double ControlConfiguration::JOINT_MIN_AMPLITUDE = 0; /**!< Lowest amplitude of joint movement */

const double ControlConfiguration::JOINT_MAX_AMPLITUDE = 0.5; /**!< Highest amplitude of joint movement */

const double ControlConfiguration::JOINT_MIN_X_OFFSET = 0; /**!< Lowest X Offset (shift) of the center of joint movement */

const double ControlConfiguration::JOINT_MAX_X_OFFSET = 2 * M_PI; /**!< Highest X Offset (shift) of the center of joint movement*/

const double ControlConfiguration::JOINT_MIN_Y_OFFSET = 0; /**!< Lowest Y Offset of the center of joint movement */

const double ControlConfiguration::JOINT_MAX_Y_OFFSET = 1; /**!< Highest Y Offset of the center of joint movement */

const ControllerGene::ControllerType ControlConfiguration::CONTROLLER_TYPE =
	ControllerGene::ChaoticControllerGene; /*!< Controller gene type */
