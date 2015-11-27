//# corresponding headers
#include <controller/universe/environments/Plane.hpp>

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

BoostLogger Plane::mBoostLogger; /*<! initialize the boost logger*/
Plane::_Init Plane::_initializer;
Plane::Plane() :
	Environment() {
}

Plane::~Plane() {
//	They are all deleted in environment
}

void Plane::initialize(
	EnvironmentModel* const environmentModel,
	const Ogre::Light* const l) {
	Environment::initialize();

	// setup the planet model
	mEnvironmentModel = environmentModel;

	// setup the plane view
	mEnvironmentGraphics = new PlaneO3D((PlaneModel*) mEnvironmentModel);
	getPlaneView()->initialize(l);
}

void Plane::update(double timeSinceLastTick) {
	getPlaneModel()->update(timeSinceLastTick);
	getPlaneView()->update(timeSinceLastTick);
}
