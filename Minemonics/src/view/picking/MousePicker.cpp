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
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers
#include <utils/ogre3D/OgreBulletUtils.hpp>

MousePicker::MousePicker(ViewController* viewController) {
	mViewController = viewController;

}

MousePicker::~MousePicker() {
	// TODO Auto-generated destructor stub
}

void MousePicker::pickBody(btDynamicsWorld* world) {
	Ogre::Ray ray = getMouseRay();
	mBulletPicker.pickBody(world, OgreBulletUtils::convert(ray.getOrigin()),
			OgreBulletUtils::convert(ray.getOrigin()+ray.getDirection()));
}

void MousePicker::pickBody() {
	//Implement OgreMeshRay
	Ogre::Ray ray = getMouseRay();
	mBulletPicker.pickBody(
			mViewController->getSelectedPlanet()->getPlanetModel()->getEnvironmentModel()->getPhysicsController()->getDynamicsWorld(),
			OgreBulletUtils::convert(ray.getOrigin()),
			OgreBulletUtils::convert(ray.getOrigin()+ray.getDirection()*10000.0f));
}

void MousePicker::moveBody(){
	Ogre::Ray ray = getMouseRay();
	mBulletPicker.movePickedBody(OgreBulletUtils::convert(ray.getOrigin()),
			OgreBulletUtils::convert(ray.getOrigin()+ray.getDirection()*10000.0f));
}

Ogre::Ray MousePicker::getMouseRay() {
	//get the mouse position
	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();
	CEGUI::Vector2f mousePos = context.getMouseCursor().getPosition();

	//return the mouse ray
	return mViewController->getCameraHandler().getCamera()->getCameraToViewportRay(
			mousePos.d_x/((double)SimulationManager::getSingleton()->getWindowWidth()), mousePos.d_y/((double)SimulationManager::getSingleton()->getWindowHeight()));
}
