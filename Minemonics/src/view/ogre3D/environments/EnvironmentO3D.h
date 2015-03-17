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
#include "view/ogre3D/environments/envgenerators/PerlinNoiseTerrainGenerator.h"

//## utils headers

class EnvironmentO3D {
public:
	EnvironmentO3D(SimulationManager* simulationMgr);
	virtual ~EnvironmentO3D();

	void initialize(std::string fileName,Light* l);

	void configureTerrainDefaults(Light* l);

	void update();

	class SimpleTerrainDefiner: public TerrainPagedWorldSection::TerrainDefiner {
	public:
		virtual void define(TerrainGroup* terrainGroup, long x, long y) {
			Image img;
			img.load("terrain.png",
					ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
			if (x % 2)
				img.flipAroundY();
			if (y % 2)
				img.flipAroundX();
			terrainGroup->defineTerrain(x, y, &img);
		}
	};

	/// This class just pretends to provide procedural page content to avoid page loading
	class DummyPageProvider: public PageProvider {
	public:
		bool prepareProceduralPage(Page* page, PagedWorldSection* section) {
			return true;
		}
		bool loadProceduralPage(Page* page, PagedWorldSection* section) {
			return true;
		}
		bool unloadProceduralPage(Page* page, PagedWorldSection* section) {
			return true;
		}
		bool unprepareProceduralPage(Page* page, PagedWorldSection* section) {
			return true;
		}
	};
	DummyPageProvider mDummyPageProvider;

	void testCapabilities(const RenderSystemCapabilities* caps) {
		if (!caps->hasCapability(RSC_VERTEX_PROGRAM)
				|| !caps->hasCapability(RSC_FRAGMENT_PROGRAM)) {
			OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
					"Your graphics card does not support vertex or fragment shaders, "
							"so you cannot run this sample. Sorry!",
					"Sample_EndlessWorld::testCapabilities");
		}
	}

	StringVector getRequiredPlugins() {
		StringVector names;
		if (!GpuProgramManager::getSingleton().isSyntaxSupported("glsles")
				&& !GpuProgramManager::getSingleton().isSyntaxSupported(
						"glsl150")
				&& !GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
			names.push_back("Cg Program Manager");
		return names;
	}

protected:
	SimulationManager* mSimulationMgr;

	TerrainGlobalOptions* mTerrainGlobals;
	TerrainGroup* mTerrainGroup;
	TerrainPaging* mTerrainPaging;
	PageManager* mPageManager;
	PagedWorld* mPagedWorld;
	TerrainPagedWorldSection* mTerrainPagedWorldSection;
	PerlinNoiseTerrainGenerator* mPerlinNoiseTerrainGenerator;

	Real mFallVelocity;
	Vector3 mTerrainPos;

	bool mLodStatus;
	bool mAutoLod;
};

#endif /* ENVIRONMENTO3D_H_ */
