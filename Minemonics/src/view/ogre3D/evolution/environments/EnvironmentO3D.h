/*
 * EnvironmentO3D.h
 *
 *  Created on: Feb 21, 2015
 *      Author: leviathan
 */

#ifndef ENVIRONMENTO3D_H_
#define ENVIRONMENTO3D_H_

//# corresponding header

//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers
#include <OgreSceneManager.h>

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

class EnvironmentO3D {
public:
	EnvironmentO3D();
	virtual ~EnvironmentO3D();
protected:
	Ogre::SceneManager* mSceneMgr;
};

#endif /* ENVIRONMENTO3D_H_ */
