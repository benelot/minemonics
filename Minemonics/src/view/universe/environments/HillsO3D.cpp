//# corresponding header
#include <view/universe/environments/HillsO3D.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

HillsO3D::HillsO3D(SimulationManager* simulationMgr) :
		EnvironmentO3D(simulationMgr), mTerrainsImported(false) {
}

HillsO3D::~HillsO3D() {
}

void HillsO3D::initialize(Ogre::Light* l) {
	EnvironmentO3D::initialize("HillsO3D",l);
	mPerlinNoiseTerrainGenerator = OGRE_NEW PerlinNoiseTerrainGenerator;
			mTerrainPagedWorldSection->setDefiner(mPerlinNoiseTerrainGenerator);
}

