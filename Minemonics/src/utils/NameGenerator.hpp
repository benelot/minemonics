/*
 * NameGenerator.h
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

#ifndef UTILS_NAMEGENERATOR_HPP_
#define UTILS_NAMEGENERATOR_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <utils/Randomness.hpp>
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

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class NameGenerator {
public:
	NameGenerator();
	void initialize();
	virtual ~NameGenerator();
	std::string generateName();

	std::vector<std::string> mNamePrefix;
	std::vector<std::string> mNameStems;
	std::vector<std::string> mNameSuffix;

	Randomness mRandomness;


};

#endif /* UTILS_NAMEGENERATOR_HPP_ */
