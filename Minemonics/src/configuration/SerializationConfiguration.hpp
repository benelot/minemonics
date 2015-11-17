#ifndef CONFIGURATION_SERIALIZATIONCONFIGURATION_HPP_
#define CONFIGURATION_SERIALIZATIONCONFIGURATION_HPP_

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
 * @brief		The configuration for serialization.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class SerializationConfiguration {
public:
	static const bool POPULATION_EXPANDED = true; /**!< If the population is saved in a folder or in one file */

	static const std::string TOP_FOLDER; /**!< The name of the top folder of where we save the universe*/
};

#endif /* CONFIGURATION_SERIALIZATIONCONFIGURATION_HPP_ */
