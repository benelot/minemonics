/*
 * HillsO3D.cpp
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "HillsO3D.h"

//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

HillsO3D::HillsO3D(SimulationManager* simulationMgr) :
		EnvironmentO3D(simulationMgr), mTerrainsImported(false) {
}

HillsO3D::~HillsO3D() {
	// TODO Auto-generated destructor stub
}

void HillsO3D::initialize(Light* l) {
	EnvironmentO3D::initialize("HillsO3D",l);
	mPerlinNoiseTerrainGenerator = OGRE_NEW PerlinNoiseTerrainGenerator;
			mTerrainPagedWorldSection->setDefiner(mPerlinNoiseTerrainGenerator);
}

//-------------------------------------------------------------------------------------
void HillsO3D::configureTerrainDefaults(Ogre::Light* light) {

}

//-------------------------------------------------------------------------------------
void HillsO3D::getTerrainImage(bool flipX, bool flipY, Ogre::Image& img) {
	img.load("terrain.png",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();

}
//-------------------------------------------------------------------------------------
void HillsO3D::defineTerrain(long x, long y) {
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
	if (Ogre::ResourceGroupManager::getSingleton().resourceExists(
			mTerrainGroup->getResourceGroup(), filename)) {
		mTerrainGroup->defineTerrain(x, y);
	} else {
		Ogre::Image img;
		getTerrainImage(x % 2 != 0, y % 2 != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);
		mTerrainsImported = true;
	}
}
//-------------------------------------------------------------------------------------
void HillsO3D::initBlendMaps(Ogre::Terrain* terrain) {
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
	Ogre::Real minHeight0 = 70;
	Ogre::Real fadeDist0 = 40;
	Ogre::Real minHeight1 = 70;
	Ogre::Real fadeDist1 = 15;
	float* pBlend0 = blendMap0->getBlendPointer();
	float* pBlend1 = blendMap1->getBlendPointer();
	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y) {
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x) {
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0) / fadeDist0;
			val = Ogre::Math::Clamp(val, (Ogre::Real) 0, (Ogre::Real) 1);
			*pBlend0++ = val;

			val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real) 0, (Ogre::Real) 1);
			*pBlend1++ = val;
		}
	}
	blendMap0->dirty();
	blendMap1->dirty();
	blendMap0->update();
	blendMap1->update();
}

void HillsO3D::buildTerrain() {
	for (long x = 0; x <= 0; ++x)
		for (long y = 0; y <= 0; ++y)
			defineTerrain(x, y);

	// sync load since we want everything in place when we start
	mTerrainGroup->loadAllTerrains(true);

	if (mTerrainsImported) {
		Ogre::TerrainGroup::TerrainIterator ti =
				mTerrainGroup->getTerrainIterator();
		while (ti.hasMoreElements()) {
			Ogre::Terrain* t = ti.getNext()->instance;
			initBlendMaps(t);
		}
	}

	mTerrainGroup->freeTemporaryResources();

}

