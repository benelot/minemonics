/*
 * Environment.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

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

//## utils headers

class Environment {
public:
	enum EnvironmentType {
		HILLS = 1, PLANE = 2, OPENSEA = 3
	};

	EnvironmentType mEnvironmentType;

	Environment(EnvironmentType environmentType);
	virtual ~Environment();

};

#endif /* ENVIRONMENT_H_ */
