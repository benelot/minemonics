#ifndef APPLICATIONCONFIGURATION_H_
#define APPLICATIONCONFIGURATION_H_

//# corresponding header
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

/**
 * @brief		Basic configuration of the simulation application.
 * @details		Basic configuration of the simulation application.
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class ApplicationConfiguration {
public:
	/**
	 * The title of the application.
	 */
	static const std::string APPLICATION_TITLE;
};

const std::string ApplicationConfiguration::APPLICATION_TITLE = "Minemonics - The Origin of Creatures v.0.2.123";

#endif /* APPLICATIONCONFIGURATION_H_ */
