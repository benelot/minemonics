/*
 * EnvironmentO3D.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: leviathan
 */

//# corresponding header
#include "EnvironmentO3D.h"

//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers

//# custom headers
//## base headers
#include "SimulationManager.h"

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

void EnvironmentO3D::initialize(std::string fileName,Light* l) {
	mTerrainGlobals = OGRE_NEW TerrainGlobalOptions();

	mTerrainGroup = OGRE_NEW TerrainGroup(mSimulationMgr->getSceneManager(), Terrain::ALIGN_X_Z,
	TERRAIN_SIZE, TERRAIN_WORLD_SIZE);
	mTerrainGroup->setFilenameConvention(Ogre::String(),
			Ogre::String("terrain"));
	mTerrainGroup->setOrigin(mTerrainPos);
	mTerrainGroup->setAutoUpdateLod(
			TerrainAutoUpdateLodFactory::getAutoUpdateLod(BY_DISTANCE));

	configureTerrainDefaults (l);

	// Paging setup
	mPageManager = OGRE_NEW PageManager();
	// Since we're not loading any pages from .page files, we need a way just
	// to say we've loaded them without them actually being loaded
	mPageManager->setPageProvider(&mDummyPageProvider);
	mPageManager->addCamera(mSimulationMgr->getCamera());
	mPageManager->setDebugDisplayLevel(0);
	mTerrainPaging = OGRE_NEW TerrainPaging(mPageManager);
	mPagedWorld = mPageManager->createWorld();
	mTerrainPagedWorldSection = mTerrainPaging->createWorldSection(mPagedWorld,
			mTerrainGroup, 400, 500, ENDLESS_PAGE_MIN_X, ENDLESS_PAGE_MIN_Y,
			ENDLESS_PAGE_MAX_X, ENDLESS_PAGE_MAX_Y);

	mTerrainGroup->freeTemporaryResources();
}

void EnvironmentO3D::configureTerrainDefaults(Light* l) {
	// Configure global
	mTerrainGlobals->setMaxPixelError(8);
	// testing composite map
	mTerrainGlobals->setCompositeMapDistance(3000);

	mTerrainGlobals->getDefaultMaterialGenerator()->setLightmapEnabled(false);

	mTerrainGlobals->setCompositeMapAmbient(mSimulationMgr->getSceneManager()->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(l->getDiffuseColour());
	mTerrainGlobals->setLightMapDirection(l->getDerivedDirection());

	// Configure default import settings for if we use imported image
	Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = TERRAIN_SIZE;
	defaultimp.worldSize = TERRAIN_WORLD_SIZE;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;
	// textures
	defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
	defaultimp.layerList[0].textureNames.push_back(
			"dirt_grayrocky_diffusespecular.dds");
	defaultimp.layerList[0].textureNames.push_back(
			"dirt_grayrocky_normalheight.dds");
	defaultimp.layerList[1].worldSize = 30;
	defaultimp.layerList[1].textureNames.push_back(
			"grass_green-01_diffusespecular.dds");
	defaultimp.layerList[1].textureNames.push_back(
			"grass_green-01_normalheight.dds");
	defaultimp.layerList[2].worldSize = 200;
	defaultimp.layerList[2].textureNames.push_back(
			"growth_weirdfungus-03_diffusespecular.dds");
	defaultimp.layerList[2].textureNames.push_back(
			"growth_weirdfungus-03_normalheight.dds");
}

void EnvironmentO3D::update() {
	mTerrainGroup->autoUpdateLodAll(false, Any(Real(HOLD_LOD_DISTANCE)));
}

