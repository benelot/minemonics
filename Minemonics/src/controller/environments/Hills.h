/*
 * Hills.h
 *
 *  Created on: Mar 24, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_ENVIRONMENTS_HILLS_H_
#define CONTROLLER_ENVIRONMENTS_HILLS_H_

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


class Hills: public Environment {
public:
	Hills();
	virtual ~Hills();

	void initialize(SimulationManager* simulationMgr, Ogre::Light* l);
};

#endif /* CONTROLLER_ENVIRONMENTS_HILLS_H_ */
