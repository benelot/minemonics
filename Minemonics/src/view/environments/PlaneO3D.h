/*
 * PlaneO3D.h
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

#ifndef PLANEO3D_H_
#define PLANEO3D_H_

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
#include <view/environments/EnvironmentO3D.h>

//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
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

#endif /* PLANEO3D_H_ */
