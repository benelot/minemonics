//# corresponding headers
#include <view/picking/MousePicker.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <CEGUI/GUIContext.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/System.h>
#include <CEGUI/Vector.h>
#include <LinearMath/btVector3.h>
#include <OgreCamera.h>
#include <OgreRay.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
#include <view/picking/BulletRay.hpp>

//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

MousePicker::MousePicker(ViewController* viewController) {
	mViewController = viewController;

}

MousePicker::~MousePicker() {
	// TODO Auto-generated destructor stub
}

void MousePicker::castRay(btDynamicsWorld* world) {
	Ogre::Ray ray = getMouseRay();
	BulletRay::castRay(world, OgreBulletUtils::convert(ray.getOrigin()),
			OgreBulletUtils::convert(ray.getDirection()));
}

void MousePicker::castRay() {
	//Implement OgreMeshRay
	Ogre::Ray ray = getMouseRay();
	BulletRay::castRay(
			mViewController->getPlanetsInView()[0]->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			OgreBulletUtils::convert(ray.getOrigin()),
			OgreBulletUtils::convert(ray.getDirection()));
}

Ogre::Ray MousePicker::getMouseRay() {
	//get the mouse position
	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();
	CEGUI::Vector2f mousePos = context.getMouseCursor().getPosition();

	//return the mouse ray
	return mViewController->getCameraHandler().getCamera()->getCameraToViewportRay(
			mousePos.d_x, mousePos.d_y);
}
