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
#include "view/CEGUI/GUISheetHandler.h"

//Game component includes
#include "controller/input/OISInputHandler.h"
#include "controller/input/CEGUIInputHandler.h"
#include "controller/camera/CameraHandler.h"

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

BoostLogger SimulationManager::mBoostLogger;  // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
//		mInfoLabel(0),
		mCameraHandler(this), mRenderer(0), mLayout(NULL), mSystem(NULL), mCEGUIInputHandler(
		NULL), mStateHandler(NULL), mGUISheetHandler(NULL) {
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
	size_t windowHnd = 0;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);

	// set up the input handlers
	mStateHandler = new StateHandler();

	// since the input handler deals with pushing input to CEGUI, we need to give it a pointer
	// to the CEGUI System instance to use
	mCEGUIInputHandler = new CEGUIInputHandler(mStateHandler, windowHnd, this);
	mStateHandler->requestStateChange(GUI);

	// make an instance of our GUI sheet handler class
	mGUISheetHandler = new GUISheetHandler(mSystem, mLayout, mStateHandler);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

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
	mCEGUIInputHandler->capture();

	// Align CEGUI mouse with OIS mouse
	const OIS::MouseState state =
			getInputHandler()->getMouse()->getMouseState();
	CEGUI::Vector2f mousePos =
			mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
			state.X.abs - mousePos.d_x, state.Y.abs - mousePos.d_y);

	mCameraHandler.reposition(evt.timeSinceLastFrame);

	// Inject time elapsed
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
	return true;
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
	mSystem = &CEGUI::System::getSingleton();

	// tell us a lot about what is going on (see CEGUI.log in the working directory)
	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

	// use this CEGUI scheme definition (see CEGUI docs for more)
	CEGUI::SchemeManager::getSingleton().createFromFile(
			(CEGUI::utf8*) "TaharezLook.scheme", (CEGUI::utf8*) "GUI");

	// show the CEGUI mouse cursor (defined in the look-n-feel)
	mSystem->getDefaultGUIContext().getMouseCursor().setDefaultImage(NULL);

	// use this font for text in the UI
	CEGUI::FontManager::getSingleton().createFromFile("Tahoma-8.font",
			(CEGUI::utf8*) "GUI");
	mSystem->getDefaultGUIContext().setDefaultFont("Tahoma-8");

	// load a layout from the XML layout file (you'll find this in resources/gui.zip), and
	// put it in the GUI resource group
	mLayout = CEGUI::WindowManager::getSingleton().createWindow(
			(CEGUI::utf8*) "DefaultWindow", (CEGUI::utf8*) "Sheet");

	createMenu(mLayout, CEGUI::WindowManager::getSingleton());

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	mSystem->getDefaultGUIContext().setRootWindow(mLayout);

	// ###################
	// We create a test scene for testing ois and bullet
	// ###################
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creating test environment for basic setups...";
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

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creating test environment for basic setups...done.";
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

//Adjust mouse clipping area
void SimulationManager::windowResized(Ogre::RenderWindow* rw) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Repositioning OIS pointer...";
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mCEGUIInputHandler->getMouse()->getMouseState();
	ms.width = width;
	ms.height = height;

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Notifying CEGUI of resize....";
	mSystem->notifyDisplaySizeChanged(CEGUI::Size<float>(width,height));
}

CEGUI::Window* SimulationManager::createMenu(CEGUI::Window* sheet,
		CEGUI::WindowManager& win) {
	//Barre de menu
	CEGUI::Window *menu = win.createWindow("TaharezLook/Menubar", "menu");
	menu->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.05, 0)));
	menu->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));

	//Menu fichier
	CEGUI::Window *fichier = win.createWindow("TaharezLook/MenuItem",
			"fichier");
	fichier->setText("Fichier");
	menu->addChild(fichier);
	CEGUI::Window *fichierpop = win.createWindow("TaharezLook/PopupMenu",
			"fichierpop");
	fichier->addChild(fichierpop);
	//Bouton quitter
	CEGUI::Window *quitter = win.createWindow("TaharezLook/MenuItem",
			"quitter");
	quitter->setText("Quitter");
	fichierpop->addChild(quitter);

	//Menu affichage
	CEGUI::Window *affichage = win.createWindow("TaharezLook/MenuItem",
			"affichage");
	affichage->setText("Affichage");
	menu->addChild(affichage);
	CEGUI::Window *affpop = win.createWindow("TaharezLook/PopupMenu", "affpop");
	affichage->addChild(affpop);
	// Bouton vue outil
	CEGUI::Window *outil = win.createWindow("TaharezLook/MenuItem", "outil");
	outil->setText("Vue outil                                      'O'");
	affpop->addChild(outil);
	//Bouton vue de cÃ´tÃ©
	CEGUI::Window *cote = win.createWindow("TaharezLook/MenuItem", "cote");
	cote->setText("Vue laterale                                  'L'");
	affpop->addChild(cote);
	//Bouton vues multiples
	CEGUI::Window *multi = win.createWindow("TaharezLook/MenuItem", "multiple");
	multi->setText("Vues multiples                              'M'");
	affpop->addChild(multi);
	//Bouton positions outil
	CEGUI::Window *posOutil = win.createWindow("TaharezLook/MenuItem",
			"posOutil");
	posOutil->setText("Afficher/Masquer les positions outil   'P'");
	affpop->addChild(posOutil);

	//Menu aide
	CEGUI::Window *aidemenu = win.createWindow("TaharezLook/MenuItem",
			"aidemenu");
	aidemenu->setText("?");
	menu->addChild(aidemenu);
	CEGUI::Window *aidepop = win.createWindow("TaharezLook/PopupMenu",
			"aidepop");
	aidemenu->addChild(aidepop);
	// Bouton aide
	CEGUI::Window *aide = win.createWindow("TaharezLook/MenuItem", "aide");
	aide->setText("Aide                      'F1'");
	aidepop->addChild(aide);
	// Bouton Ã  propos
	CEGUI::Window *apropos = win.createWindow("TaharezLook/MenuItem",
			"apropos");
	apropos->setText("A propos de ce logiciel");
	aidepop->addChild(apropos);

	sheet->addChild(menu);
	return sheet;
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
