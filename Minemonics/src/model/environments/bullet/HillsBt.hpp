/*
 * HillsBt.h
 *
 *  Created on: Mar 17, 2015
 *      Author: leviathan
 */

#ifndef MODEL_ENVIRONMENT_HILLSBT_H_
#define MODEL_ENVIRONMENT_HILLSBT_H_

//# corresponding header
#include <btBulletDynamicsCommon.h>
#include <model/environments/bullet/EnvironmentBt.hpp>

//## view headers
#include <Terrain/OgreTerrain.h>

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
