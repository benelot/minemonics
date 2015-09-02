//# corresponding header
#include <controller/universe/environments/Hills.hpp>
#include <model/universe/environments/bullet/HillsBt.hpp>
#include <view/universe/environments/HillsO3D.hpp>

//## view headers

Hills::Hills() {
}

Hills::~Hills() {
	
}

void Hills::initialize(SimulationManager* simulationMgr, Ogre::Light* l) {
	Environment::initialize(Environment::HILLS);

	mEnvironmentGraphics = new HillsO3D(simulationMgr);
	((HillsO3D*) mEnvironmentGraphics)->initialize(l);
//	mEnvironmentPhysics = new HillsBt();

	//		Ogre::TerrainGroup * pGroup = ((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup();
	//		Ogre::Terrain * terrain = pGroup->getTerrain(0, 0);

	//((HillsBt*) mEnvironmentPhysics)->initialize(((HillsO3D*) mEnvironmentGraphics)->getTerrainGroup()->getTerrain(0, 0));

}

EnvironmentModel* Hills::getEnvironmentModel() {
	//TODO Implement Hills
	return NULL;
}
