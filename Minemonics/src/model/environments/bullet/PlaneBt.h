/*
 * PlaneBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_ENVIRONMENT_PLANEBT_H_
#define MODEL_ENVIRONMENT_PLANEBT_H_

//# corresponding header
#include "model/environments/bullet/EnvironmentBt.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

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
