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
class SimulationManager;

//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreGpuProgramManager.h>
#include <OgreSceneManager.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreTerrainQuadTreeNode.h>
#include <OgreTerrainMaterialGeneratorA.h>
#include <OgreTerrainPagedWorldSection.h>
#include <OgreTerrainPaging.h>
#include <OgrePageManager.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
#include "view/environments/EnvironmentGraphics.h"
#include "view/ogre3D/environments/envgenerators/PerlinNoiseTerrainGenerator.h"

//## utils headers

class EnvironmentO3D: public EnvironmentGraphics {
public:
	EnvironmentO3D(SimulationManager* simulationMgr);
	virtual ~EnvironmentO3D();

	void initialize(std::string fileName, Ogre::Light* l);

	void configureTerrainDefaults(Ogre::Light* l);

	void update();

	class ImageTerrainDefiner: public Ogre::TerrainPagedWorldSection::TerrainDefiner {
	public:
		virtual void define(Ogre::TerrainGroup* terrainGroup, long x, long y) {
			Ogre::Image img;
			img.load("terrain.png",
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (x % 2)
				img.flipAroundY();
			if (y % 2)
				img.flipAroundX();
			terrainGroup->defineTerrain(x, y, &img);
		}
	};

	class PlaneTerrainDefiner: public Ogre::TerrainPagedWorldSection::TerrainDefiner {
	public:
		virtual void define(Ogre::TerrainGroup* terrainGroup, long x, long y) {
			Ogre::Image img;
			img.load("plane.png",
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (x % 2)
				img.flipAroundY();
			if (y % 2)
				img.flipAroundX();
			terrainGroup->defineTerrain(x, y, &img);
		}
	};

	/// This class just pretends to provide procedural page content to avoid page loading
	class DummyPageProvider: public Ogre::PageProvider {
	public:
		bool prepareProceduralPage(Ogre::Page* page,
				Ogre::PagedWorldSection* section) {
			return true;
		}
		bool loadProceduralPage(Ogre::Page* page,
				Ogre::PagedWorldSection* section) {
			return true;
		}
		bool unloadProceduralPage(Ogre::Page* page,
				Ogre::PagedWorldSection* section) {
			return true;
		}
		bool unprepareProceduralPage(Ogre::Page* page,
				Ogre::PagedWorldSection* section) {
			return true;
		}
	};
	DummyPageProvider mDummyPageProvider;

	void testCapabilities(const Ogre::RenderSystemCapabilities* caps) {
		if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM)
				|| !caps->hasCapability(Ogre::RSC_FRAGMENT_PROGRAM)) {
			OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
					"Your graphics card does not support vertex or fragment shaders, "
							"so you cannot run this sample. Sorry!",
					"Sample_EndlessWorld::testCapabilities");
		}
	}

	Ogre::TerrainGroup*& getTerrainGroup() {
		return mTerrainGroup;
	}

	double getTerrainHeight(double x, double z) {
		Ogre::Ray ray;
		ray.setOrigin(Ogre::Vector3(x, mTerrainPos.y + 10000, z));
		ray.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

		Ogre::TerrainGroup::RayResult rayResult = mTerrainGroup->rayIntersects(
				ray);
		if (rayResult.hit) {
			return rayResult.position.y;
		}
		return 0;
	}

protected:

	void initBlendMaps(Ogre::Terrain* terrain);

	SimulationManager* mSimulationMgr;

	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::TerrainGroup* mTerrainGroup;
	Ogre::TerrainPaging* mTerrainPaging;
	Ogre::PageManager* mPageManager;
	Ogre::PagedWorld* mPagedWorld;
	Ogre::TerrainPagedWorldSection* mTerrainPagedWorldSection;
	PerlinNoiseTerrainGenerator* mPerlinNoiseTerrainGenerator;

	Ogre::Real mFallVelocity;
	Ogre::Vector3 mTerrainPos;

	bool mLodStatus;
	bool mAutoLod;
};

#endif /* ENVIRONMENTO3D_H_ */
