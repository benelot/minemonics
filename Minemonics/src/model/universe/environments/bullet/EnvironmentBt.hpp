/*
 * EnvironmentBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_
#define MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_

//# corresponding header
#include <btBulletDynamicsCommon.h>
#include <model/universe/environments/EnvironmentPhysics.hpp>

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
class EnvironmentBt: public EnvironmentPhysics {
public:
	EnvironmentBt();
	virtual ~EnvironmentBt();

	virtual btRigidBody*& getBody() = 0;
};

#endif /* MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_ */
