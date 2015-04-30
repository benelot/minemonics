/*
 * Plane.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_ENVIRONMENTS_PLANE_HPP_
#define CONTROLLER_ENVIRONMENTS_PLANE_HPP_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <controller/environments/Environment.hpp>
#include <OgreLight.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers

//## model headers
//## view headers


/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class Plane: public Environment {
public:
	Plane();
	virtual ~Plane();

	void initialize(SimulationManager* simulationMgr, Ogre::Light* l);
};

#endif /* CONTROLLER_ENVIRONMENTS_PLANE_HPP_ */
