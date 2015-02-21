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

#include "view/general/evolution/environments/Hills.h"

#include "view/ogre3D/evolution/environments/EnvironmentO3D.h"

class HillsO3D: public Hills, public EnvironmentO3D {
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
};

#endif /* HILLSO3D_H_ */
