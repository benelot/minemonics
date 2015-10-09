#ifndef VIEW_UNIVERSE_ENVIRONMENTS_PLANEO3D_H_
#define VIEW_UNIVERSE_ENVIRONMENTS_PLANEO3D_H_

//# corresponding header
#include <view/universe/environments/EnvironmentO3D.hpp>

//# forward declarations
class PlaneModel;

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
//## utils headers

/**
 * @brief		The plane graphical representation in Ogre 3D.
 * @details		Details
 * @date		2015-02-12
 * @author		Benjamin Ellenberger
 */
class PlaneO3D: public EnvironmentO3D {
public:
	PlaneO3D(const PlaneModel* const planeModel);
	virtual ~PlaneO3D();

	/**
	 * Initialize the plane view.
	 * @param l The light of the scene.
	 */
	void initialize(const Ogre::Light* const l);

	/**
	 * Update the plane view.
	 */
	void update(double timeSinceLastTick);

private:
	const PlaneModel* mPlaneModel;
};

#endif /* VIEW_UNIVERSE_ENVIRONMENTS_PLANEO3D_H_ */
