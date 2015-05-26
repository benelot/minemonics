/*
 * EnvironmentPhysics.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_
#define MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_

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

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class EnvironmentPhysics {
public:
	EnvironmentPhysics();
	virtual ~EnvironmentPhysics();

	virtual void initialize() = 0;
};

#endif /* MODEL_UNIVERSE_ENVIRONMENTS_ENVIRONMENTPHYSICS_HPP_ */
