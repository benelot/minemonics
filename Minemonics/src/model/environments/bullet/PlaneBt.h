/*
 * PlaneBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_ENVIRONMENT_PLANEBT_H_
#define MODEL_ENVIRONMENT_PLANEBT_H_

#include <btBulletDynamicsCommon.h>

#include "EnvironmentBt.h"

class PlaneBt : public EnvironmentBt {
public:
	PlaneBt();
	virtual ~PlaneBt();

	void initialize();

	btRigidBody*& getBody() {
		return mGroundBody;
	}

private:
	btCollisionShape* mGroundShape;
	btDefaultMotionState* mGroundMotionState;
	btRigidBody* mGroundBody;
};

#endif /* MODEL_ENVIRONMENT_PLANEBT_H_ */
