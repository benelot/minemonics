#ifndef APPLICATIONCONFIGURATION_H_
#define APPLICATIONCONFIGURATION_H_

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
	/**
	 * The title of the application.
	 */
	static const std::string APPLICATION_TITLE;

	static const int APPLICATION_TICK = 1000.0f/60.0f;//ms
};

// version.features.bugs-fixed.commit
const std::string ApplicationConfiguration::APPLICATION_TITLE = "Minemonics - The Origin of Creatures v.0.34.7.347";

#endif /* APPLICATIONCONFIGURATION_H_ */
