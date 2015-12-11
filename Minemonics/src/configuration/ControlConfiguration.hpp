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
	static const double JOINT_MIN_FREQUENCY; /**!<Hz Lowest frequency of joint movement*/

	static const double JOINT_MAX_FREQUENCY; /**!< Hz Highest frequency of joint movement */

	static const double JOINT_MIN_AMPLITUDE; /**!< Lowest amplitude of joint movement */

	static const double JOINT_MAX_AMPLITUDE; /**!< Highest amplitude of joint movement */

	static const double JOINT_MIN_X_OFFSET; /**!< Lowest X Offset (shift) of the center of joint movement */

	static const double JOINT_MAX_X_OFFSET; /**!< Highest X Offset (shift) of the center of joint movement*/

	static const double JOINT_MIN_Y_OFFSET; /**!< Lowest Y Offset of the center of joint movement */

	static const double JOINT_MAX_Y_OFFSET; /**!< Highest Y Offset of the center of joint movement */

	static const ControllerGene::ControllerType CONTROLLER_TYPE; /*!< Controller gene type */
};

#endif /* CONFIGURATION_CONTROLCONFIGURATION_H_ */
