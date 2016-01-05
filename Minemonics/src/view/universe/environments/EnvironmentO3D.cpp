//# corresponding headers
#include <view/universe/environments/EnvironmentO3D.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/lexical_cast.hpp>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/viewcontroller/ViewController.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>

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

#define TERRAIN_LOAD_RADIUS 1500
#define TERRAIN_HOLD_RADIUS 3000

EnvironmentO3D::EnvironmentO3D() :
	mTerrainGlobals(NULL), mTerrainGroup(NULL), mTerrainPaging(NULL), mPageManager(
		NULL), mPagedWorld(NULL), mTerrainPagedWorldSection(NULL), mPerlinNoiseTerrainGenerator(
		NULL), mLODStatus(false), mAutoLOD(true), mTerrainPos(0, 0, 0), mInWorld(
		false) {

}

EnvironmentO3D::~EnvironmentO3D() {
	if (mTerrainPaging) {
		OGRE_DELETE mTerrainPaging;
		mPageManager->destroyWorld(mPagedWorld);
		OGRE_DELETE mPageManager;
	}

	mTerrainGlobals = NULL;

	mTerrainGroup = NULL; // deleted in terrain paging
//	if (mTerrainGroup) {
//		OGRE_DELETE mTerrainGroup;
//	}

	mTerrainPagedWorldSection = NULL; // deleted somewhere
//	if (mTerrainPagedWorldSection) {
//		OGRE_DELETE mTerrainPagedWorldSection;
//	}
}

void EnvironmentO3D::initialize(const std::string fileName,
	const Ogre::Light* const l) {
	mTerrainGlobals = &SimulationManager::getSingleton()->getTerrainGlobals();

	mTerrainGroup = new Ogre::TerrainGroup(
		SimulationManager::getSingleton()->getSceneManager(),
		Ogre::Terrain::ALIGN_X_Z,
		TERRAIN_SIZE, TERRAIN_WORLD_SIZE);

	//TODO: The terrain does not need to be saved, it is always randomly created.
	//set how the terrain should be named for faster loading
	mTerrainGroup->setFilenameConvention(Ogre::String(),
		Ogre::String(
			boost::lexical_cast < std::string > (this) + "/" + "Terrain"));

	//set origin of the terrain
	mTerrainGroup->setOrigin(mTerrainPos);

	mTerrainGroup->setAutoUpdateLod(
		Ogre::TerrainAutoUpdateLodFactory::getAutoUpdateLod(Ogre::BY_DISTANCE));

	configureTerrainDefaults(l);

	// Paging setup
	mPageManager = new Ogre::PageManager();
	// Since we're not loading any pages from .page files, we need a way just
	// to say we've loaded them without them actually being loaded
	mPageManager->setPageProvider(&mDummyPageProvider);
	mPageManager->addCamera(
		SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera());
	mPageManager->setDebugDisplayLevel(0);

	mTerrainPaging = new Ogre::TerrainPaging(mPageManager);
	mPagedWorld = mPageManager->createWorld();
	mTerrainPagedWorldSection = mTerrainPaging->createWorldSection(mPagedWorld,
		mTerrainGroup, TERRAIN_LOAD_RADIUS, TERRAIN_HOLD_RADIUS,
		ENDLESS_PAGE_MIN_X, ENDLESS_PAGE_MIN_Y,
		ENDLESS_PAGE_MAX_X, ENDLESS_PAGE_MAX_Y);
	mTerrainGroup->freeTemporaryResources();

	mTerrainGroup->loadAllTerrains(true);
}

void EnvironmentO3D::configureTerrainDefaults(const Ogre::Light* const l) {

	// Configure global
	//TODO:Change this to zero if the bullet physics terrain is strongly different
	mTerrainGlobals->setMaxPixelError(8);
	//TODO: Fix ambient light for composite map
//	mTerrainGlobals->setCompositeMapAmbient(
//			SimulationManager::getSingleton()->getSceneManager()->getAmbientLight());
	mTerrainGlobals->setCompositeMapAmbient(Ogre::ColourValue(1, 1, 1));

	mTerrainGlobals->setCastsDynamicShadows(false);

	if (l != NULL) {
		// testing composite map
		mTerrainGlobals->getDefaultMaterialGenerator()->setLightmapEnabled(
			true);
		mTerrainGlobals->setCompositeMapDistance(32000);
		mTerrainGlobals->setCompositeMapDiffuse(l->getDiffuseColour());
		mTerrainGlobals->setLightMapDirection(l->getDerivedDirection());
	} else {
		mTerrainGlobals->getDefaultMaterialGenerator()->setLightmapEnabled(
			false);
		mTerrainGlobals->setCompositeMapDistance(32000);
	}

//	 Configure default import settings for if we use imported image
	Ogre::Terrain::ImportData& defaultimp =
		mTerrainGroup->getDefaultImportSettings();
	defaultimp.terrainSize = TERRAIN_SIZE;
	defaultimp.worldSize = TERRAIN_WORLD_SIZE;
	defaultimp.inputScale = 600;
	defaultimp.minBatchSize = 33;
	defaultimp.maxBatchSize = 65;

//	 textures
	defaultimp.layerList.resize(1);
	defaultimp.layerList[0].worldSize = 10;
	defaultimp.layerList[0].textureNames.push_back("grid5.png");
//
//	defaultimp.layerList[0].worldSize = 1000;
//	defaultimp.layerList[0].textureNames.push_back("honeycomb.png");
//	defaultimp.layerList[0].textureNames.push_back("honeycomb.png");

//	defaultimp.layerList.resize(3);
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

bool EnvironmentO3D::isInWorld() const {
	return mInWorld;
}

void EnvironmentO3D::addToWorld() {
	mInWorld = true;
	mTerrainGroup->setOrigin(mTerrainPos);
}

void EnvironmentO3D::removeFromWorld() {
	mInWorld = false;
	//TODO: There must be another way to hide a terrain.
	mTerrainGroup->setOrigin(Ogre::Vector3(0, 1000000, 0));
}

//-------------------------------------------------------------------------------------
void EnvironmentO3D::initBlendMaps(Ogre::Terrain* const terrain) {
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

void EnvironmentO3D::update(double timeSinceLastTick) {
	mTerrainGroup->autoUpdateLodAll(false,
		Ogre::Any(Ogre::Real(HOLD_LOD_DISTANCE)));
}

