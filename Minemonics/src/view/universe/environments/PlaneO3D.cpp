//# corresponding header
#include <SimulationManager.hpp>
#include <view/universe/environments/PlaneO3D.hpp>

//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

PlaneO3D::PlaneO3D(SimulationManager* const simulationMgr) :
		EnvironmentO3D(simulationMgr) {

}

PlaneO3D::~PlaneO3D() {
}

void PlaneO3D::initialize(const Ogre::Light* const l) {
	EnvironmentO3D::initialize("PlaneO3D",l);
	mTerrainPagedWorldSection->setDefiner(OGRE_NEW PlaneTerrainDefiner);
}

void PlaneO3D::update(){
	EnvironmentO3D::update();
}

