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
#include "controller/input/OISInputHandler.h"
#include "controller/input/CEGUIInputHandler.h"
#include "controller/camera/CameraHandler.h"

//logger
#include "utils/logging/Logger.h"

#include <OgreWindowEventUtilities.h>

// needed to be able to create the CEGUI renderer interface
#include <CEGUI/RendererModules/Ogre/Renderer.h>

// CEGUI includes
#include <CEGUI/System.h>
#include <CEGUI/InputEvent.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/FontManager.h>
//#include "CEGUI/widgets/FrameWindow.h"

#include "CEGUI/widgets/PushButton.h"

// GUI sheet handlers
#include "view/CEGUI/GUISheetHandler.h"

//#define _DEBUGGUI

BoostLogger SimulationManager::logger;        // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
//		mInfoLabel(0),
		mCameraHandler(this), mRenderer(0),pLayout(NULL),pSystem(NULL),mCEGUIInputHandler(NULL) {
	mTerrain = NULL;

}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {
	CEGUI::OgreRenderer::destroySystem();
}

void SimulationManager::destroyScene(void) {
	mTerrain->destroy();
}

//-------------------------------------------------------------------------------------
void SimulationManager::createFrameListener(void) {

	/// INPUT HANDLER

	// this next bit is for the sake of the input handler
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	// For debug, in case something goes wrong the mouse can go out.
	pl.insert(OIS::ParamList::value_type("x11_keyboard_grab", "false"));
	pl.insert(OIS::ParamList::value_type("x11_mouse_grab", "false"));


	// set up the input handlers
	mStateHandler = new StateHandler();

	// since the input handler deals with pushing input to CEGUI, we need to give it a pointer
	// to the CEGUI System instance to use
	mCEGUIInputHandler = new CEGUIInputHandler(mStateHandler, windowHnd,
			this);
	mStateHandler->requestStateChange(GUI);

	// make an instance of our GUI sheet handler class
	GUISheetHandler* pDlg = new GUISheetHandler(pSystem, pLayout, mStateHandler);

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(
			OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(
			OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	// OgreBites : remove if CEGUI is satisfying
	//mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);

	// Populate the camera container
	mCameraHandler.setCamNode(mCamera->getParentSceneNode());
}

//-------------------------------------------------------------------------------------
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	if (mTerrain->mTerrainGroup->isDerivedDataUpdateInProgress()) {
		//mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
		//mInfoLabel->show();
		if (mTerrain->mTerrainsImported) {
			//mInfoLabel->setCaption("Building terrain, please wait...");
		} else {
			//mInfoLabel->setCaption("Updating textures, patience...");
		}
	} else {
		//mTrayMgr->removeWidgetFromTray(mInfoLabel);
		//mInfoLabel->hide();
		if (mTerrain->mTerrainsImported) {
			mTerrain->mTerrainGroup->saveAllTerrains(true);
			mTerrain->mTerrainsImported = false;
		}
	}

	if (mWindow->isClosed() || mStateHandler->getCurrentState() == SHUTDOWN)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	//Need to inject timestamps to CEGUI System.
	//CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

	mCameraHandler.reposition(evt.timeSinceLastFrame);
	return true;
}

//-------------------------------------------------------------------------------------
bool SimulationManager::keyPressed(const OIS::KeyEvent &arg) {
	return getInputHandler()->keyPressed(arg);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::keyReleased(const OIS::KeyEvent &arg) {
	return getInputHandler()->keyReleased(arg);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mouseMoved(const OIS::MouseEvent &arg) {
	return getInputHandler()->mouseMoved(arg);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return getInputHandler()->mousePressed(arg, id);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return getInputHandler()->mouseReleased(arg, id);
}
//-------------------------------------------------------------------------------------
bool SimulationManager::quit(const CEGUI::EventArgs &args) {
	mShutDown = true;
	return true;
}

//-------------------------------------------------------------------------------------
/**
 * Creates the scene of the application.
 */
void SimulationManager::createScene(void) {

	// Initialize the logger
	Logger::init("minemonics.log");
	Logger::initTermSink();

	/// CEGUI

	// with a scene manager and window, we can create a the GUI renderer

	// new way to instantiate a CEGUIOgreRenderer (Ogre 1.9)
	//Ogre::RenderTarget *mRenderTarget = window;
	//CEGUI::OgreRenderer::bootstrapSystem(*mRenderTarget);
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

	// This pointer is valid only locally
	pSystem = &CEGUI::System::getSingleton();

	// tell us a lot about what is going on (see CEGUI.log in the working directory)
	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

	// use this CEGUI scheme definition (see CEGUI docs for more)
	CEGUI::SchemeManager::getSingleton().createFromFile(
			(CEGUI::utf8*) "TaharezLook.scheme", (CEGUI::utf8*) "GUI");

	// show the CEGUI mouse cursor (defined in the look-n-feel)
	pSystem->getDefaultGUIContext().getMouseCursor().setDefaultImage(
			(CEGUI::utf8*) "TaharezLook/MouseArrow");

	// use this font for text in the UI
	CEGUI::FontManager::getSingleton().createFromFile("Tahoma-8.font",
			(CEGUI::utf8*) "GUI");
	pSystem->getDefaultGUIContext().setDefaultFont("Tahoma-8");

	// load a layout from the XML layout file (you'll find this in resources/gui.zip), and
	// put it in the GUI resource group
	pLayout = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(
			(CEGUI::utf8*) "katana.layout", (CEGUI::utf8*) "GUI");

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	pSystem->getDefaultGUIContext().setRootWindow(pLayout);

//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) pLayout->getChildRecursive("cmdQuit");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&SimulationManager::quit, this));

//	while (mStateHandler->getCurrentState() != SHUTDOWN) {
//		handler->capture();
//
//		// run the message pump (Eihort)
//		Ogre::WindowEventUtilities::messagePump();
//		ogre->renderOneFrame();
//	}

	// ###################
	// We create a test scene for testing ois and bullet
	// ###################
	BOOST_LOG_SEV(logger, boost::log::trivial::info)<< "Creating test environment for basic setups...";
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

	BOOST_LOG_SEV(logger, boost::log::trivial::info)<< "Creating test environment for basic setups...done.";
}

// Accessor methods
CameraHandler& SimulationManager::getCameraHandler() {
	return mCameraHandler;
}

CEGUIInputHandler* SimulationManager::getInputHandler() {
	return mCEGUIInputHandler;
}

StateHandler* SimulationManager::getStateHandler() {
	return mStateHandler;
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
