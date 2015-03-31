/*
 * HillsBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_ENVIRONMENT_HILLSBT_H_
#define MODEL_ENVIRONMENT_HILLSBT_H_

//# corresponding header
#include "model/environments/bullet/EnvironmentBt.h"

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <btBulletDynamicsCommon.h>

//## view headers
#include <Terrain/OgreTerrain.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class HillsBt : public EnvironmentBt {
public:
	HillsBt();
	virtual ~HillsBt();

	void initialize(Ogre::Terrain* terrain);

	btRigidBody*& getBody() {
		return mGroundBody;
	}

private:
	btCollisionShape* mGroundShape;
	btDefaultMotionState* mGroundMotionState;
	btRigidBody* mGroundBody;
};

#endif /* MODEL_ENVIRONMENT_HILLSBT_H_ */
