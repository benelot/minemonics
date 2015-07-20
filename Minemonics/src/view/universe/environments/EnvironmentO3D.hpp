#ifndef VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTO3D_H_
#define VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTO3D_H_

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
#include <view/universe/environments/EnvironmentGraphics.hpp>
#include <view/universe/environments/envgenerators/PerlinNoiseTerrainGenerator.hpp>

//## utils headers

/**
 * @brief		The environmentO3D is the base view class for all environments having a ground terrain.
 * @details		Details
 * @date		2015-02-21
 * @author		Benjamin Ellenberger
 */
class EnvironmentO3D: public EnvironmentGraphics {
public:
	EnvironmentO3D();
	virtual ~EnvironmentO3D();

	/**
	 * Initialize the environment view.
	 * @param fileName The file name of the environment save.
	 * @param l The light of the scene.
	 */
	void initialize(const std::string fileName, const Ogre::Light* const l);

	/**
	 * Is the environment view in the world?
	 * @return If the environment view is in the world.
	 */
	virtual bool isInWorld() const;

	/**
	 * Add the environment view to the world.
	 */
	virtual void addToWorld();

	/**
	 * Remove the environment view from the world.
	 */
	virtual void removeFromWorld();

	/**
	 * Configure terrain defaults.
	 * @param l The light of the scene.
	 */
	void configureTerrainDefaults(const Ogre::Light* const l);

	/**
	 * Update the environment view.
	 */
	void update();

	void testCapabilities(const Ogre::RenderSystemCapabilities* const caps) {
		if (!caps->hasCapability(Ogre::RSC_VERTEX_PROGRAM)
				|| !caps->hasCapability(Ogre::RSC_FRAGMENT_PROGRAM)) {
			OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
					"Your graphics card does not support vertex or fragment shaders, "
							"so you cannot run this sample. Sorry!",
					"EnvironmentO3D::testCapabilities");
		}
	}

	//Accessor methods
	Ogre::TerrainGroup*& getTerrainGroup() {
		return mTerrainGroup;
	}

	double getTerrainHeight(const double x,const double z) {
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

	Ogre::TerrainPagedWorldSection* const getTerrainPagedWorldSection() const {
		return mTerrainPagedWorldSection;
	}

//	std::vector<Ogre::Terrain*> getAllDefinedTerrains() {
////		Ogre::TerrainIterator tit = mTerrainGroup->getTerrainIterator();
////		for(;tit != mTerrainGroup->getTerrainIterator().end();tit++)
////		{
////
////		}
//	}

protected:

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

	class ImageTerrainDefiner: public Ogre::TerrainPagedWorldSection::TerrainDefiner {
	public:
		virtual void define(Ogre::TerrainGroup* const terrainGroup,const long x, const long y) {
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

	void initBlendMaps(Ogre::Terrain* const terrain);

	Ogre::TerrainGlobalOptions* mTerrainGlobals;
	Ogre::TerrainGroup* mTerrainGroup;
	Ogre::TerrainPaging* mTerrainPaging;
	Ogre::PageManager* mPageManager;
	Ogre::PagedWorld* mPagedWorld;
	Ogre::TerrainPagedWorldSection* mTerrainPagedWorldSection;
	PerlinNoiseTerrainGenerator* mPerlinNoiseTerrainGenerator;

	Ogre::Vector3 mTerrainPos;

	bool mLODStatus;
	bool mAutoLOD;

	bool mInWorld;
};

#endif /* VIEW_UNIVERSE_ENVIRONMENTS_ENVIRONMENTO3D_H_ */
