/*
 * HillsO3D.h
 *
 *  Created on: Feb 12, 2015
 *      Author: leviathan
 */

#ifndef HILLSO3D_H_
#define HILLSO3D_H_

//# corresponding header

//# forward declarations
class SimulationManager;
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
class HillsO3D: public EnvironmentO3D {
public:
	HillsO3D(SimulationManager* simulationMgr);
	virtual ~HillsO3D();

	void initialize(Ogre::Light* l);
	void update();

	bool mTerrainsImported;
};

#endif /* HILLSO3D_H_ */
