/*
 * Environment.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

class Environment {
public:
	enum EnvironmentType{
			HILLS = 1,
			PLANE = 2,
			OPENSEA =3
		};

	EnvironmentType environmentType;

	Environment(EnvironmentType environmentType);
	virtual ~Environment();

};

#endif /* ENVIRONMENT_H_ */
