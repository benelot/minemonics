#ifndef VIEW_UNIVSERSE_ENVIRONMENTS_PLANEO3D_H_
#define VIEW_UNIVSERSE_ENVIRONMENTS_PLANEO3D_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreLight.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
#include <view/universe/environments/EnvironmentO3D.hpp>

//## utils headers

/**
 * @brief		The plane graphical representation in Ogre 3D.
 * @details		Details
 * @date		2015-02-12
 * @author		Benjamin Ellenberger
 */
class PlaneO3D: public EnvironmentO3D {
public:
	PlaneO3D(SimulationManager* simulationMgr);
	virtual ~PlaneO3D();

	void initialize(Ogre::Light* l);
	void update();

	bool mTerrainsImported;
};

#endif /* VIEW_UNIVSERSE_ENVIRONMENTS_PLANEO3D_H_ */
