/*
 * EnvironmentO3D.h
 *
 *  Created on: Feb 21, 2015
 *      Author: leviathan
 */

#ifndef ENVIRONMENTO3D_H_
#define ENVIRONMENTO3D_H_

#include <OgreSceneManager.h>

class EnvironmentO3D {
public:
	EnvironmentO3D();
	virtual ~EnvironmentO3D();
protected:
	Ogre::SceneManager* mSceneMgr;
};

#endif /* ENVIRONMENTO3D_H_ */
