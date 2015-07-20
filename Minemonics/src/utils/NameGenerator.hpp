#ifndef UTILS_NAMEGENERATOR_HPP_
#define UTILS_NAMEGENERATOR_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <string>
#include <vector>

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
#include <utils/Randomness.hpp>

/**
 * @brief		The name generator generates names (first and second names) for the creatures to be used as their identifiers.
 * @details		Details
 * @date		2015-03-13
 * @author		Benjamin Ellenberger
 */
class NameGenerator {
public:
	NameGenerator();
	virtual ~NameGenerator();

	/**
	 * Initialize the name generator.
	 */
	void initialize();

	/**
	 * Generate a first name.
	 * @return The first name.
	 */
	std::string generateFirstName();

private:
	std::vector<std::string> mNamePrefix;
	std::vector<std::string> mNameStems;
	std::vector<std::string> mNameSuffix;
};

#endif /* UTILS_NAMEGENERATOR_HPP_ */
