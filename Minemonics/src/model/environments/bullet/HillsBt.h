/*
 * HillsBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_ENVIRONMENT_HILLSBT_H_
#define MODEL_ENVIRONMENT_HILLSBT_H_

#include <btBulletDynamicsCommon.h>

#include "EnvironmentBt.h"

class HillsBt : public EnvironmentBt {
public:
	HillsBt();
	virtual ~HillsBt();

	btRigidBody*& getBody() {
		return mGroundBody;
	}

private:
	btCollisionShape* mGroundShape;
	btDefaultMotionState* mGroundMotionState;
	btRigidBody* mGroundBody;
};

#endif /* MODEL_ENVIRONMENT_HILLSBT_H_ */
