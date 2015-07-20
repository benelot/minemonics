//# corresponding header
#include <view/universe/environments/PlaneO3D.hpp>

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
#include <model/universe/environments/PlaneModel.hpp>

//## view headers
//## utils headers

PlaneO3D::PlaneO3D(const PlaneModel* const planeModel) :
		EnvironmentO3D(),mPlaneModel(planeModel) {

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

