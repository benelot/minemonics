/*
 * EnvironmentO3D.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: leviathan
 */

//# corresponding header
#include <SimulationManager.hpp>
#include <view/universe/environments/EnvironmentO3D.hpp>

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

// max range for a int16
#define ENDLESS_PAGE_MIN_X (-0x7FFF)
#define ENDLESS_PAGE_MIN_Y (-0x7FFF)
#define ENDLESS_PAGE_MAX_X 0x7FFF
#define ENDLESS_PAGE_MAX_Y 0x7FFF

#define TERRAIN_WORLD_SIZE 12000.0f
#define TERRAIN_SIZE 513
#define HOLD_LOD_DISTANCE 3000.0

EnvironmentO3D::EnvironmentO3D(SimulationManager* simulationMgr) :
		mSimulationMgr(simulationMgr), mTerrainGlobals(NULL), mTerrainGroup(NULL), mTerrainPaging(
		NULL), mPageManager(NULL), mPagedWorld(NULL), mTerrainPagedWorldSection(
		NULL), mPerlinNoiseTerrainGenerator(NULL), mLodStatus(false), mAutoLod(
				true), mFallVelocity(0), mTerrainPos(0, 0, 0) {

}

EnvironmentO3D::~EnvironmentO3D() {
	if (mTerrainPaging) {
		OGRE_DELETE mTerrainPaging;
		mPageManager->destroyWorld(mPagedWorld);
		OGRE_DELETE mPageManager;
	}

	if (mTerrainGlobals)
		OGRE_DELETE mTerrainGlobals;
}

void EnvironmentO3D::initialize(std::string fileName,Ogre::Light* l) {
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSimulationMgr->getSceneManager(), Ogre::Terrain::ALIGN_X_Z,
	TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(Ogre::String(),
			Ogre::String("terrain"));
	mTerrainGroup->setOrigin(mTerrainPos);
	mTerrainGroup->setAutoUpdateLod(
			Ogre::TerrainAutoUpdateLodFactory::getAutoUpdateLod(Ogre::BY_DISTANCE));

	configureTerrainDefaults (l);

	// Paging setup
	mPageManager = OGRE_NEW Ogre::PageManager();
	// Since we're not loading any pages from .page files, we need a way just
	// to say we've loaded them without them actually being loaded
	mPageManager->setPageProvider(&mDummyPageProvider);
	mPageManager->addCamera(mSimulationMgr->getCamera());
	mPageManager->setDebugDisplayLevel(0);
	mTerrainPaging = OGRE_NEW Ogre::TerrainPaging(mPageManager);
	mPagedWorld = mPageManager->createWorld();
	mTerrainPagedWorldSection = mTerrainPaging->createWorldSection(mPagedWorld,
			mTerrainGroup, 400, 500, ENDLESS_PAGE_MIN_X, ENDLESS_PAGE_MIN_Y,
			ENDLESS_PAGE_MAX_X, ENDLESS_PAGE_MAX_Y);

	mTerrainGroup->freeTemporaryResources();
}

void EnvironmentO3D::configureTerrainDefaults(Ogre::Light* l) {
	// Configure global
	mTerrainGlobals->setMaxPixelError(8);
	// testing composite map
	mTerrainGlobals->setCompositeMapDistance(3000);

	mTerrainGlobals->getDefaultMaterialGenerator()->setLightmapEnabled(false);

	mTerrainGlobals->setCompositeMapAmbient(mSimulationMgr->getSceneManager()->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(l->getDiffuseColour());
	mTerrainGlobals->setLightMapDirection(l->getDerivedDirection());

	// Configure default import settings for if we use imported image
	Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = TERRAIN_SIZE;
	defaultimp.worldSize = TERRAIN_WORLD_SIZE;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;
	// textures
	defaultimp.layerList.resize(1);
//	defaultimp.layerList[0].worldSize = 1000;
//	defaultimp.layerList[0].textureNames.push_back(
//			"grid_illusion.png");
//	defaultimp.layerList[0].textureNames.push_back(
//			"grid_illusion.png");

	defaultimp.layerList[0].worldSize = 1000;
	defaultimp.layerList[0].textureNames.push_back(
			"honeycomb.png");
	defaultimp.layerList[0].textureNames.push_back(
			"honeycomb.png");

//	defaultimp.layerList[0].worldSize = 100;
//	defaultimp.layerList[0].textureNames.push_back(
//			"dirt_grayrocky_diffusespecular.dds");
//	defaultimp.layerList[0].textureNames.push_back(
//			"dirt_grayrocky_normalheight.dds");
//	defaultimp.layerList[1].worldSize = 30;
//	defaultimp.layerList[1].textureNames.push_back(
//			"grass_green-01_diffusespecular.dds");
//	defaultimp.layerList[1].textureNames.push_back(
//			"grass_green-01_normalheight.dds");
//	defaultimp.layerList[2].worldSize = 200;
//	defaultimp.layerList[2].textureNames.push_back(
//			"growth_weirdfungus-03_diffusespecular.dds");
//	defaultimp.layerList[2].textureNames.push_back(
//			"growth_weirdfungus-03_normalheight.dds");
}

//-------------------------------------------------------------------------------------
void EnvironmentO3D::initBlendMaps(Ogre::Terrain* terrain) {
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

void EnvironmentO3D::update() {
	mTerrainGroup->autoUpdateLodAll(false, Ogre::Any(Ogre::Real(HOLD_LOD_DISTANCE)));
}

