/*
 * EnvironmentBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_
#define MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_

#include <btBulletDynamicsCommon.h>

#include "model/environments/EnvironmentPhysics.h"

class EnvironmentBt: public EnvironmentPhysics {
public:
	EnvironmentBt();
	virtual ~EnvironmentBt();

	virtual btRigidBody*& getBody() = 0;
};

#endif /* MODEL_BULLET_ENVIRONMENTS_ENVIRONMENTBT_H_ */
