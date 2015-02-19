/*
 * HillsO3D.h
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

#ifndef HILLSO3D_H_
#define HILLSO3D_H_

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include "view/general/evolution/environments/Hills.h"

class HillsO3D: public Hills {
public:
	HillsO3D(Ogre::SceneManager* mSceneMgr);
	virtual ~HillsO3D();

	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);
	void buildTerrain();
	void destroy();

	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::TerrainGroup* mTerrainGroup;
	bool mTerrainsImported;
	Ogre::SceneManager* mSceneMgr;
};

#endif /* HILLSO3D_H_ */
