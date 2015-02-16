/*
 -----------------------------------------------------------------------------
 Filename:    SimulationManager.cpp
 -----------------------------------------------------------------------------

 based on the source file which is part of the
 ___                 __    __ _ _    _
 /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 / \_// (_| | | |  __/  \  /\  /| |   <| |
 \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 |___/
 Tutorial Framework
 http://www.ogre3d.org/tikiwiki/
 -----------------------------------------------------------------------------
 */
#include "SimulationManager.h"
#include "view/ogre3D/evolution/environments/HillsO3D.h"

//Game component includes
#include "controller/input/KeyboardHandler.h"
#include "controller/input/MouseHandler.h"
#include "controller/camera/CameraHandler.h"

//logger
#include "utils/logging/Logger.h"

BoostLogger SimulationManager::logger;                     // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
		mInfoLabel(0), mCameraHandler(this), mKeyboardHandler(this), mMouseHandler(
				this) {
	mTerrain = NULL;

}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {
}

void SimulationManager::destroyScene(void) {
	mTerrain->destroy();
}

//-------------------------------------------------------------------------------------
void SimulationManager::createFrameListener(void) {
	BaseApplication::createFrameListener();

	mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);

	// Populate the camera container
	mCameraHandler.setCamNode(mCamera->getParentSceneNode());
}

//-------------------------------------------------------------------------------------
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	bool ret = BaseApplication::frameRenderingQueued(evt);

	if (mTerrain->mTerrainGroup->isDerivedDataUpdateInProgress()) {
		mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
		mInfoLabel->show();
		if (mTerrain->mTerrainsImported) {
			mInfoLabel->setCaption("Building terrain, please wait...");
		} else {
			mInfoLabel->setCaption("Updating textures, patience...");
		}
	} else {
		mTrayMgr->removeWidgetFromTray(mInfoLabel);
		mInfoLabel->hide();
		if (mTerrain->mTerrainsImported) {
			mTerrain->mTerrainGroup->saveAllTerrains(true);
			mTerrain->mTerrainsImported = false;
		}
	}

	if (mWindow->isClosed())
		return false;

	if (mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	mCameraHandler.reposition(evt.timeSinceLastFrame);
	return true;
}

//-------------------------------------------------------------------------------------
bool SimulationManager::keyPressed(const OIS::KeyEvent &arg) {
	return mKeyboardHandler.keyPressed(arg);

}
//-------------------------------------------------------------------------------------
bool SimulationManager::keyReleased(const OIS::KeyEvent &arg) {
	return mKeyboardHandler.keyReleased(arg);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mouseMoved(const OIS::MouseEvent &arg) {
	return mMouseHandler.mouseMoved(arg);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return mMouseHandler.mousePressed(arg, id);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return mMouseHandler.mouseReleased(arg, id);
}
//-------------------------------------------------------------------------------------
//bool SimulationManager::quit(const CEGUI::EventArgs &e)
//{
//    return true;
//}

//-------------------------------------------------------------------------------------
/**
 * Creates the scene of the application.
 */
void SimulationManager::createScene(void) {

	// Initialize the logger
	Logger::init("minemonics.log");
	Logger::initTermSink();

	// We create a test scene for testing ois and bullet
	BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Creating test environment for basic setups...";
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);

	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(
			Ogre::RSC_INFINITE_FAR_PLANE)) {
		mCamera->setFarClipDistance(0); // enable infinite far clip distance if we can
	}

	// Play with startup Texture Filtering options
	// Note: Pressing T on runtime will discard those settings
	//  Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	//  Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);

	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	Ogre::Light* light = mSceneMgr->createLight("tstLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	// create the light
	Ogre::Light *light2 = mSceneMgr->createLight("Light1");
	light2->setType(Ogre::Light::LT_POINT);
	light2->setPosition(Ogre::Vector3(250, 150, 250));
	light2->setDiffuseColour(Ogre::ColourValue::White);
	light2->setSpecularColour(Ogre::ColourValue::White);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	// Create terrain
	mTerrain = new HillsO3D(mSceneMgr);
	mTerrain->configureTerrainDefaults(light);
	mTerrain->buildTerrain();

	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 1200);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);

	// Create skyplane
	Ogre::Plane plane;
	plane.d = 100;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;

	//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
	mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true,
			0.5, 150, 150);

	// Ogrehead
	Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* headNode =
			mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
	headNode->attachObject(ogreHead);
	headNode->translate(Ogre::Vector3(1963, 50, 1660));

	// add the ninja
	Ogre::Entity *ninja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
	Ogre::SceneNode *ninjaNode =
			mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
	ninjaNode->attachObject(ninja);
	ninjaNode->translate(Ogre::Vector3(1963, 50, 1660));

	// Create the scene node
	ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1",
			Ogre::Vector3(-400, 200, 400));

	// Make it look towards the ninja
	ninjaNode->yaw(Ogre::Degree(-45));

	// Create the pitch node
	ninjaNode = ninjaNode->createChildSceneNode("PitchNode1");
	ninjaNode->attachObject(mCamera);

	// create the second camera node/pitch node
	ninjaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2",
			Ogre::Vector3(0, 200, 400));
	ninjaNode = ninjaNode->createChildSceneNode("PitchNode2");

	BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Creating test environment for basic setups...done.";
}

CameraHandler& SimulationManager::getCameraHandler() {
	return mCameraHandler;
}
// Accessor methods

KeyboardHandler& SimulationManager::getKeyboardHandler() {
	return mKeyboardHandler;
}

MouseHandler& SimulationManager::getMouseHandler() {
	return mMouseHandler;
}

void SimulationManager::enableShutdown() {
	mShutDown = true;
}

Ogre::Camera* SimulationManager::getCamera() {
	return mCamera;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
		{
// Create application object
	SimulationManager app;

	try {
		app.go();
	} catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: "
				<< e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

#ifdef __cplusplus
}
#endif
