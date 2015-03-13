/*
 * NameGenerator.h
 *
 *  Created on: Mar 13, 2015
 *      Author: leviathan
 */

#ifndef UTILS_NAMEGENERATOR_H_
#define UTILS_NAMEGENERATOR_H_

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
#include "utils/Randomness.h"

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

#endif /* UTILS_NAMEGENERATOR_H_ */
