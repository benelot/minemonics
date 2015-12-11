#ifndef CONFIGURATION_APPLICATIONCONFIGURATION_H_
#define CONFIGURATION_APPLICATIONCONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>

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

/**
 * @brief		Basic configuration of the simulation application.
 * @details		Basic configuration of the simulation application.
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class ApplicationConfiguration {
public:

	static const std::string APPLICATION_TITLE; /**!< The title of the application.*/

	static const int APPLICATION_TICK; //ms
};
#endif /* CONFIGURATION_APPLICATIONCONFIGURATION_H_ */
