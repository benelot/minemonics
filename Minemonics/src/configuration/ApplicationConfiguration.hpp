#ifndef CONFIGURATION_APPLICATIONCONFIGURATION_H_
#define CONFIGURATION_APPLICATIONCONFIGURATION_H_

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

	static const int APPLICATION_TICK = 1000.0f / 60.0f; //ms
};

const std::string ApplicationConfiguration::APPLICATION_TITLE = /**!< version.features.bugs-fixed.commit */
"Minemonics - The Origin of Creatures v.0.54.16.670";

#endif /* CONFIGURATION_APPLICATIONCONFIGURATION_H_ */
