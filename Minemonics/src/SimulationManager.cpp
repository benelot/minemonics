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

	mStart = boost::posix_time::second_clock::local_time();
	mNow = boost::posix_time::second_clock::local_time();
	mRuntime = mNow - mStart;
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

	// Align CEGUI mouse with OIS mouse
	const OIS::MouseState state =
			getInputHandler()->getMouse()->getMouseState();
	CEGUI::Vector2f mousePos =
			mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
			state.X.abs - mousePos.d_x, state.Y.abs - mousePos.d_y);
}

//-------------------------------------------------------------------------------------
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	//update timer
	mNow = boost::posix_time::second_clock::local_time();
	boost::posix_time::time_duration mRuntime = mNow -mStart;

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

	mCameraHandler.reposition(evt.timeSinceLastFrame);

	if (mFpsPanel != NULL) {
		if (mFpsPanel->isVisible()) // if fps panel is visible, then update its contents
		{
			if (mFpsPanel->size() == 2) {
				mFpsPanel->setParamValue(0,
						Ogre::StringConverter::toString(mWindow->getLastFPS()),
						true);
				mFpsPanel->setParamValue(1,
						Ogre::StringConverter::toString(mRuntime.total_milliseconds()), true);
			} else {
				Ogre::RenderTarget::FrameStats fs = mWindow->getStatistics();
				mFpsPanel->setParamValue(0,
						Ogre::StringConverter::toString(fs.lastFPS), false);
				mFpsPanel->setParamValue(1,
						Ogre::StringConverter::toString(fs.avgFPS), false);
				mFpsPanel->setParamValue(2,
						Ogre::StringConverter::toString(fs.bestFPS), false);
				mFpsPanel->setParamValue(3,
						Ogre::StringConverter::toString(fs.worstFPS), false);
				mFpsPanel->setParamValue(4,
						Ogre::StringConverter::toString(fs.triangleCount),
						false);
				mFpsPanel->setParamValue(5,
						Ogre::StringConverter::toString(fs.batchCount), true);
			}
		}
	}
	if (mDetailsPanel != NULL) {
		if (mDetailsPanel->isVisible()) // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0,
					Ogre::StringConverter::toString(
							mCamera->getDerivedPosition().x), false);
			mDetailsPanel->setParamValue(1,
					Ogre::StringConverter::toString(
							mCamera->getDerivedPosition().y), false);
			mDetailsPanel->setParamValue(2,
					Ogre::StringConverter::toString(
							mCamera->getDerivedPosition().z), false);
			mDetailsPanel->setParamValue(4,
					Ogre::StringConverter::toString(
							mCamera->getDerivedOrientation().w), false);
			mDetailsPanel->setParamValue(5,
					Ogre::StringConverter::toString(
							mCamera->getDerivedOrientation().x), false);
			mDetailsPanel->setParamValue(6,
					Ogre::StringConverter::toString(
							mCamera->getDerivedOrientation().y), false);
			mDetailsPanel->setParamValue(7,
					Ogre::StringConverter::toString(
							mCamera->getDerivedOrientation().z), true);
		}
	}

	return true;

// Inject time elapsed
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
	return true;
}

//-------------------------------------------------------------------------------------
bool SimulationManager::quit() {
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

// CEGUI

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
			(CEGUI::utf8*) "Ogremonics.scheme", (CEGUI::utf8*) "GUI");
//	CEGUI::SchemeManager::getSingleton().createFromFile(
//			(CEGUI::utf8*) "TaharezLook.scheme", (CEGUI::utf8*) "GUI");
//	CEGUI::SchemeManager::getSingleton().createFromFile(
//			(CEGUI::utf8*) "WindowsLook.scheme", (CEGUI::utf8*) "GUI");

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
	createDebugPanels();

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
CameraHandler & SimulationManager::getCameraHandler() {
	return mCameraHandler;
}

CEGUIInputHandler * SimulationManager::getInputHandler() {
	return mCEGUIInputHandler;
}

StateHandler * SimulationManager::getStateHandler() {
	return mStateHandler;
}

Ogre::Camera * SimulationManager::getCamera() {
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


void SimulationManager::windowFocusChange(Ogre::RenderWindow* rw)
{
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Window has gained focus...";
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Window has lost focus...";
}

CEGUI::Window * SimulationManager::createMenu(CEGUI::Window * sheet,
		CEGUI::WindowManager & win) {
	//Menu bar
	CEGUI::Window *menuBar = win.createWindow("Ogremonics/Menubar", "menu");
	menuBar->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.037, 0)));
	menuBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));

	//#####################
	//File menu
	CEGUI::Window *fileTopItem = win.createWindow("Ogremonics/MenuItem",
			"fileTopItem");
	fileTopItem->setText("File");
	menuBar->addChild(fileTopItem);
	CEGUI::Window *fileMenu = win.createWindow("Ogremonics/PopupMenu",
			"fileMenu");
	fileTopItem->addChild(fileMenu);

	//quit item
	CEGUI::Window *quitApplicationItem = win.createWindow("Ogremonics/MenuItem",
			"cmdQuitApplication");
	quitApplicationItem->setText("Quit [Q]");
	fileMenu->addChild(quitApplicationItem);

	//#####################
	//Evolution menu
	CEGUI::Window *evolutionTopItem = win.createWindow("Ogremonics/MenuItem",
			"evolutionTopItem");
	evolutionTopItem->setText("Evolution");
	menuBar->addChild(evolutionTopItem);
	CEGUI::Window *evolutionMenu = win.createWindow("Ogremonics/PopupMenu",
			"evolutionMenu");
	evolutionTopItem->addChild(evolutionMenu);

	// new evolution item
	CEGUI::Window *newEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"cmdNewEvolution");
	newEvolutionItem->setText("New Evolution");
	evolutionMenu->addChild(newEvolutionItem);

	// open evolution item
	CEGUI::Window *openEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"openEvolutionItem");
	openEvolutionItem->setText("Open Evolution...");
	evolutionMenu->addChild(openEvolutionItem);

	// save evolution as...
	CEGUI::Window *saveEvolutionAsItem = win.createWindow("Ogremonics/MenuItem",
			"saveEvolutionAsItem");
	saveEvolutionAsItem->setText("Save Evolution as...");
	evolutionMenu->addChild(saveEvolutionAsItem);

	// close evolution
	CEGUI::Window *closeEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"closeEvolutionItem");
	closeEvolutionItem->setText("Close Evolution");
	evolutionMenu->addChild(closeEvolutionItem);

	// Run evolution
	CEGUI::Window *runEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"runEvolutionItem");
	runEvolutionItem->setText("Run Evolution");
	evolutionMenu->addChild(runEvolutionItem);

	// Pause evolution
	CEGUI::Window *pauseEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"pauseEvolutionItem");
	pauseEvolutionItem->setText("Pause Evolution");
	evolutionMenu->addChild(pauseEvolutionItem);

	// Stop evolution
	CEGUI::Window *stopEvolutionItem = win.createWindow("Ogremonics/MenuItem",
			"stopEvolutionItem");
	stopEvolutionItem->setText("Stop Evolution");
	evolutionMenu->addChild(stopEvolutionItem);

	// Browse history
	CEGUI::Window *browseHistoryItem = win.createWindow("Ogremonics/MenuItem",
			"browseHistoryItem");
	browseHistoryItem->setText("Browse History");
	evolutionMenu->addChild(browseHistoryItem);

	//#####################
	//Environment menu
	CEGUI::Window *environmentTopItem = win.createWindow("Ogremonics/MenuItem",
			"environmentTopItem");
	environmentTopItem->setText("Environment");
	menuBar->addChild(environmentTopItem);
	CEGUI::Window *environmentMenu = win.createWindow("Ogremonics/PopupMenu",
			"evolutionMenu");
	environmentTopItem->addChild(environmentMenu);

	// Hills...
	CEGUI::Window *hillsItem = win.createWindow("Ogremonics/MenuItem",
			"hillsItem");
	hillsItem->setText("Hills...");
	environmentMenu->addChild(hillsItem);

	// Opensea
	CEGUI::Window *openSeaItem = win.createWindow("Ogremonics/MenuItem",
			"openSeaItem");
	openSeaItem->setText("Open Sea");
	environmentMenu->addChild(openSeaItem);

	// Plane
	CEGUI::Window *planeItem = win.createWindow("Ogremonics/MenuItem",
			"planeItem");
	planeItem->setText("Plane");
	environmentMenu->addChild(planeItem);

	//#####################
	//Population menu
	CEGUI::Window *populationTopItem = win.createWindow("Ogremonics/MenuItem",
			"populationTopItem");
	populationTopItem->setText("Population");
	menuBar->addChild(populationTopItem);
	CEGUI::Window *populationMenu = win.createWindow("Ogremonics/PopupMenu",
			"populationMenu");
	populationTopItem->addChild(populationMenu);

	// New Population
	CEGUI::Window *newPopulationItem = win.createWindow("Ogremonics/MenuItem",
			"newPopulationItem");
	newPopulationItem->setText("New Population");
	populationMenu->addChild(newPopulationItem);

	// Open Population...
	CEGUI::Window *openPopulationItem = win.createWindow("Ogremonics/MenuItem",
			"openPopulationItem");
	openPopulationItem->setText("Open Population");
	populationMenu->addChild(openPopulationItem);

	// Save population as...
	CEGUI::Window *savePopulationAsItem = win.createWindow(
			"Ogremonics/MenuItem", "savePopulationAsItem");
	savePopulationAsItem->setText("Save Population as...");
	populationMenu->addChild(savePopulationAsItem);

	// Close population
	CEGUI::Window *closePopulationItem = win.createWindow("Ogremonics/MenuItem",
			"closePopulationItem");
	closePopulationItem->setText("Close Population");
	populationMenu->addChild(closePopulationItem);

	//#####################
	//Creature menu
	CEGUI::Window *creatureTopItem = win.createWindow("Ogremonics/MenuItem",
			"creatureTopItem");
	creatureTopItem->setText("Creature");
	menuBar->addChild(creatureTopItem);
	CEGUI::Window *creatureMenu = win.createWindow("Ogremonics/PopupMenu",
			"creatureMenu");
	creatureTopItem->addChild(creatureMenu);

	// New random creature
	CEGUI::Window *newCreatureItem = win.createWindow("Ogremonics/MenuItem",
			"newCreatureItem");
	newCreatureItem->setText("New Random Creature [F5]");
	creatureMenu->addChild(newCreatureItem);

	// Open creature...
	CEGUI::Window *openCreatureItem = win.createWindow("Ogremonics/MenuItem",
			"openCreatureItem");
	openCreatureItem->setText("Open Creature...");
	creatureMenu->addChild(openCreatureItem);

	// Save creature as...
	CEGUI::Window *saveCreatureAsItem = win.createWindow("Ogremonics/MenuItem",
			"saveCreatureAsItem");
	saveCreatureAsItem->setText("Save Creature As...");
	creatureMenu->addChild(saveCreatureAsItem);

	// Close creature
	CEGUI::Window *closeCreatureItem = win.createWindow("Ogremonics/MenuItem",
			"closeCreatureItem");
	closeCreatureItem->setText("Close Creature");
	creatureMenu->addChild(closeCreatureItem);

	// Record frames
	CEGUI::Window *recordFramesItem = win.createWindow("Ogremonics/MenuItem",
			"recordFramesItem");
	recordFramesItem->setText("Record Frames [CTRL+R]");
	creatureMenu->addChild(recordFramesItem);

	//#####################
	//Spawn menu
	CEGUI::Window *spawnTopItem = win.createWindow("Ogremonics/MenuItem",
			"spawnTopItem");
	spawnTopItem->setText("Spawn");
	menuBar->addChild(spawnTopItem);
	CEGUI::Window *spawnMenu = win.createWindow("Ogremonics/PopupMenu",
			"spawnMenu");
	spawnTopItem->addChild(spawnMenu);

	// spawn Box
	CEGUI::Window *spawnBoxItem = win.createWindow("Ogremonics/MenuItem",
			"quitItem");
	spawnBoxItem->setText("Box [2]");
	spawnMenu->addChild(spawnBoxItem);

	// spawn Sphere
	CEGUI::Window *spawnSphereItem = win.createWindow("Ogremonics/MenuItem",
			"spawnSphereItem");
	spawnSphereItem->setText("Sphere [3]");
	spawnMenu->addChild(spawnSphereItem);

	// spawn Capsule
	CEGUI::Window *spawnCapsuleItem = win.createWindow("Ogremonics/MenuItem",
			"spawnCapsuleItem");
	spawnCapsuleItem->setText("Capsule [6]");
	spawnMenu->addChild(spawnCapsuleItem);

	//#####################
	// Action menu
	CEGUI::Window *actionTopItem = win.createWindow("Ogremonics/MenuItem",
			"actionTopItem");
	actionTopItem->setText("Action");
	menuBar->addChild(actionTopItem);
	CEGUI::Window *actionMenu = win.createWindow("Ogremonics/PopupMenu",
			"fileMenu");
	actionTopItem->addChild(actionMenu);

	// Return to origin
	CEGUI::Window *returnToOriginItem = win.createWindow("Ogremonics/MenuItem",
			"returnToOriginItem");
	returnToOriginItem->setText("Return to Origin [K]");
	actionMenu->addChild(returnToOriginItem);

	//#####################
	//Settings menu
	CEGUI::Window *settingsTopItem = win.createWindow("Ogremonics/MenuItem",
			"settingsTopItem");
	settingsTopItem->setText("Settings");
	menuBar->addChild(settingsTopItem);
	CEGUI::Window *settingsMenu = win.createWindow("Ogremonics/PopupMenu",
			"settingsMenu");
	settingsTopItem->addChild(settingsMenu);

	// Evolution menu
	CEGUI::Window *evolutionSettingsTopItem = win.createWindow(
			"Ogremonics/MenuItem", "evolutionSettingsTopItem");
	evolutionSettingsTopItem->setText("Evolution");
	settingsMenu->addChild(evolutionSettingsTopItem);
	CEGUI::Window *evolutionSettingsMenu = win.createWindow(
			"Ogremonics/PopupMenu", "evolutionSettingsMenu");
	evolutionSettingsTopItem->addChild(evolutionSettingsMenu);

	//Population menu
	CEGUI::Window *populationSettingsTopItem = win.createWindow(
			"Ogremonics/MenuItem", "populationSettingsTopItem");
	populationSettingsTopItem->setText("Population");
	settingsMenu->addChild(populationSettingsTopItem);
	CEGUI::Window *populationSettingsMenu = win.createWindow(
			"Ogremonics/PopupMenu", "populationSettingsMenu");
	populationSettingsTopItem->addChild(populationSettingsMenu);

	// Population size
	CEGUI::Window *populationSizeItem = win.createWindow("Ogremonics/MenuItem",
			"populationSizeItem");
	populationSizeItem->setText("Population Size...");
	populationSettingsMenu->addChild(populationSizeItem);

	// Selection style
	CEGUI::Window *selectionStyleItem = win.createWindow("Ogremonics/MenuItem",
			"selectionStyleItem");
	selectionStyleItem->setText("Selection Style...");
	populationSettingsMenu->addChild(selectionStyleItem);

	// Creature
	CEGUI::Window *creatureSettingsTopItem = win.createWindow(
			"Ogremonics/MenuItem", "creatureSettingsTopItem");
	creatureSettingsTopItem->setText("Creature");
	settingsMenu->addChild(creatureSettingsTopItem);
	CEGUI::Window *creatureSettingsMenu = win.createWindow(
			"Ogremonics/PopupMenu", "creatureSettingsMenu");
	creatureSettingsTopItem->addChild(creatureSettingsMenu);

	// Rendering
	CEGUI::Window *renderingTopItem = win.createWindow("Ogremonics/MenuItem",
			"renderingTopItem");
	renderingTopItem->setText("Rendering");
	settingsMenu->addChild(renderingTopItem);

	// Rendering menu
	CEGUI::Window *renderingMenu = win.createWindow("Ogremonics/PopupMenu",
			"renderingMenu");
	renderingTopItem->addChild(renderingMenu);

	// Shadows on/off
	CEGUI::Window *shadowsItem = win.createWindow("Ogremonics/MenuItem",
			"shadowsItem");
	shadowsItem->setText("Shadows on/off [H]");
	renderingMenu->addChild(shadowsItem);

	// Fog on/off
	CEGUI::Window *fogItem = win.createWindow("Ogremonics/MenuItem", "fogItem");
	fogItem->setText("Fog on/off [F]");
	renderingMenu->addChild(fogItem);

	// Skybox on/off
	CEGUI::Window *skyboxItem = win.createWindow("Ogremonics/MenuItem",
			"skyboxItem");
	skyboxItem->setText("Skybox on/off [B]");
	renderingMenu->addChild(skyboxItem);

	// Greenscreen on/off
	CEGUI::Window *greenscreenItem = win.createWindow("Ogremonics/MenuItem",
			"greenscreenItem");
	greenscreenItem->setText("Greenscreen on/off");
	renderingMenu->addChild(greenscreenItem);

	// Status on/off
	CEGUI::Window *statusItem = win.createWindow("Ogremonics/MenuItem",
			"statusItem");
	statusItem->setText("Status on/off");
	renderingMenu->addChild(statusItem);

	// Polygon mode
	CEGUI::Window *polygonModeTopItem = win.createWindow("Ogremonics/MenuItem",
			"polygonModeTopItem");
	polygonModeTopItem->setText("Polygon mode");
	renderingMenu->addChild(polygonModeTopItem);

	// Polygon mode menu
	CEGUI::Window *polygonModeMenu = win.createWindow("Ogremonics/PopupMenu",
			"polygonModeMenu");
	polygonModeTopItem->addChild(polygonModeMenu);

	// Solid
	CEGUI::Window *solidModeItem = win.createWindow("Ogremonics/MenuItem",
			"solidModeItem");
	solidModeItem->setText("Solid mode");
	polygonModeMenu->addChild(solidModeItem);

	// Wireframe
	CEGUI::Window *wireframeModeItem = win.createWindow("Ogremonics/MenuItem",
			"wireframeModeItem");
	wireframeModeItem->setText("Wireframe mode");
	polygonModeMenu->addChild(wireframeModeItem);

	// Ambient light
	CEGUI::Window *ambientLightTopItem = win.createWindow("Ogremonics/MenuItem",
			"ambientLightTopItem");
	ambientLightTopItem->setText("Ambient light");
	renderingMenu->addChild(ambientLightTopItem);

	// Ambient light menu
	CEGUI::Window *ambientLightMenu = win.createWindow("Ogremonics/PopupMenu",
			"ambientLightMenu");
	ambientLightTopItem->addChild(ambientLightMenu);

	// 0 %
	CEGUI::Window *ambientLight0Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight0Item");
	ambientLight0Item->setText("0 %");
	ambientLightMenu->addChild(ambientLight0Item);

	// 10 %
	CEGUI::Window *ambientLight10Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight10Item");
	ambientLight10Item->setText("10 %");
	ambientLightMenu->addChild(ambientLight10Item);

	// 20 %
	CEGUI::Window *ambientLight20Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight20Item");
	ambientLight20Item->setText("20 %");
	ambientLightMenu->addChild(ambientLight20Item);

	// 30 %
	CEGUI::Window *ambientLight30Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight30Item");
	ambientLight30Item->setText("30 %");
	ambientLightMenu->addChild(ambientLight30Item);

	// 40 %
	CEGUI::Window *ambientLight40Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight40Item");
	ambientLight40Item->setText("40 %");
	ambientLightMenu->addChild(ambientLight40Item);

	// 50 %
	CEGUI::Window *ambientLight50Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight50Item");
	ambientLight50Item->setText("50 %");
	ambientLightMenu->addChild(ambientLight50Item);

	// 60 %
	CEGUI::Window *ambientLight60Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight60Item");
	ambientLight60Item->setText("60 %");
	ambientLightMenu->addChild(ambientLight60Item);

	// 70 %
	CEGUI::Window *ambientLight70Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight70Item");
	ambientLight70Item->setText("70 %");
	ambientLightMenu->addChild(ambientLight70Item);

	// 80 %
	CEGUI::Window *ambientLight80Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight80Item");
	ambientLight80Item->setText("80 %");
	ambientLightMenu->addChild(ambientLight80Item);

	// 90 %
	CEGUI::Window *ambientLight90Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight90Item");
	ambientLight90Item->setText("90 %");
	ambientLightMenu->addChild(ambientLight90Item);

	// 100 %
	CEGUI::Window *ambientLight100Item = win.createWindow("Ogremonics/MenuItem",
			"ambientLight100Item");
	ambientLight100Item->setText("100 %");
	ambientLightMenu->addChild(ambientLight100Item);

	// Tune for speed
	CEGUI::Window *tuneForSpeedItem = win.createWindow("Ogremonics/MenuItem",
			"tuneForSpeedItem");
	tuneForSpeedItem->setText("Tune for Speed [Keypad -]");
	renderingMenu->addChild(tuneForSpeedItem);

	// Tune for quality
	CEGUI::Window *tuneForQualityItem = win.createWindow("Ogremonics/MenuItem",
			"tuneForQualityItem");
	tuneForQualityItem->setText("Tune for Quality [Keypad +]");
	renderingMenu->addChild(tuneForQualityItem);

	// Movement
	CEGUI::Window *movementTopItem = win.createWindow("Ogremonics/MenuItem",
			"movementTopItem");
	movementTopItem->setText("Movement");
	settingsMenu->addChild(movementTopItem);

	// Movement menu
	CEGUI::Window *movementMenu = win.createWindow("Ogremonics/PopupMenu",
			"movementMenu");
	movementTopItem->addChild(movementMenu);

	// Speed 1
	CEGUI::Window *speed1Item = win.createWindow("Ogremonics/MenuItem",
			"speed1Item");
	speed1Item->setText("Speed 1 [ALT-1]");
	movementMenu->addChild(speed1Item);

	// Speed 2
	CEGUI::Window *speed2Item = win.createWindow("Ogremonics/MenuItem",
			"speed2Item");
	speed2Item->setText("Speed 2 [ALT-2]");
	movementMenu->addChild(speed2Item);

	// Speed 3
	CEGUI::Window *speed3Item = win.createWindow("Ogremonics/MenuItem",
			"speed3Item");
	speed3Item->setText("Speed 3 [ALT-3]");
	movementMenu->addChild(speed3Item);

	// Speed 4
	CEGUI::Window *speed4Item = win.createWindow("Ogremonics/MenuItem",
			"speed4Item");
	speed4Item->setText("Speed 4 [ALT-4]");
	movementMenu->addChild(speed4Item);

	// Speed 5
	CEGUI::Window *speed5Item = win.createWindow("Ogremonics/MenuItem",
			"speed5Item");
	speed5Item->setText("Speed 5 [ALT-5]");
	movementMenu->addChild(speed5Item);

	// Speed 6
	CEGUI::Window *speed6Item = win.createWindow("Ogremonics/MenuItem",
			"speed6Item");
	speed6Item->setText("Speed 6 [ALT-6]");
	movementMenu->addChild(speed6Item);

	// Speed 7
	CEGUI::Window *speed7Item = win.createWindow("Ogremonics/MenuItem",
			"speed7Item");
	speed7Item->setText("Speed 7 [ALT-7]");
	movementMenu->addChild(speed7Item);

	// Speed 8
	CEGUI::Window *speed8Item = win.createWindow("Ogremonics/MenuItem",
			"speed8Item");
	speed8Item->setText("Speed 8 [ALT-8]");
	movementMenu->addChild(speed8Item);

	// Speed 9
	CEGUI::Window *speed9Item = win.createWindow("Ogremonics/MenuItem",
			"speed9Item");
	speed9Item->setText("Speed 9 [ALT-9]");
	movementMenu->addChild(speed9Item);

	// Speed 10
	CEGUI::Window *speed10Item = win.createWindow("Ogremonics/MenuItem",
			"speed10Item");
	speed10Item->setText("Speed 10 [ALT-10]");
	movementMenu->addChild(speed10Item);

	// Physics
	CEGUI::Window *physicsTopItem = win.createWindow("Ogremonics/MenuItem",
			"physicsTopItem");
	physicsTopItem->setText("Physics");
	settingsMenu->addChild(physicsTopItem);

	// Physics menu
	CEGUI::Window *physicsMenu = win.createWindow("Ogremonics/PopupMenu",
			"physicsMenu");
	physicsTopItem->addChild(physicsMenu);

	// Pause simulation
	CEGUI::Window *pauseSimulationItem = win.createWindow("Ogremonics/MenuItem",
			"pauseSimulationItem");
	pauseSimulationItem->setText("Pause Simulation");
	physicsMenu->addChild(pauseSimulationItem);

	// gravity
	CEGUI::Window *gravityTopItem = win.createWindow("Ogremonics/MenuItem",
			"gravityTopItem");
	gravityTopItem->setText("Gravity");
	physicsMenu->addChild(gravityTopItem);

	//gravity menu
	CEGUI::Window *gravityMenu = win.createWindow("Ogremonics/PopupMenu",
			"gravityMenu");
	gravityTopItem->addChild(gravityMenu);

	// No gravity
	CEGUI::Window *noGravityItem = win.createWindow("Ogremonics/MenuItem",
			"noGravityItem");
	noGravityItem->setText("No Gravity");
	gravityMenu->addChild(noGravityItem);

	// Pluto gravity 0.059
	CEGUI::Window *plutoGravityItem = win.createWindow("Ogremonics/MenuItem",
			"plutoGravityItem");
	plutoGravityItem->setText("Pluto Gravity 0.059 g");
	gravityMenu->addChild(plutoGravityItem);

	// Moon gravity 0.166
	CEGUI::Window *moonGravityItem = win.createWindow("Ogremonics/MenuItem",
			"moonGravityItem");
	moonGravityItem->setText("Moon Gravity 0.166 g");
	gravityMenu->addChild(moonGravityItem);

	// Mars/Mercury gravity 0.377/0.378
	CEGUI::Window *marsMercuryGravityItem = win.createWindow(
			"Ogremonics/MenuItem", "marsMercuryGravityItem");
	marsMercuryGravityItem->setText("Mars/Mercury Gravity 0.377 g");
	gravityMenu->addChild(marsMercuryGravityItem);

	// Uranus gravity 0.889
	CEGUI::Window *uranusGravityItem = win.createWindow("Ogremonics/MenuItem",
			"uranusGravityItem");
	uranusGravityItem->setText("Uranus Gravity 0.899 g");
	gravityMenu->addChild(uranusGravityItem);

	// Venus/Saturn gravity 0.907/0.916
	CEGUI::Window *venusSaturnGravityItem = win.createWindow(
			"Ogremonics/MenuItem", "venusSaturnGravityItem");
	venusSaturnGravityItem->setText("Venus/Saturn Gravity 0.91 g");
	gravityMenu->addChild(venusSaturnGravityItem);

	// Earth gravity 1
	CEGUI::Window *earthGravityItem = win.createWindow("Ogremonics/MenuItem",
			"earthGravityItem");
	earthGravityItem->setText("Earth Gravity 1 g");
	gravityMenu->addChild(earthGravityItem);

	// Neptune gravity 1.12
	CEGUI::Window *neptuneGravityItem = win.createWindow("Ogremonics/MenuItem",
			"neptuneGravityItem");
	neptuneGravityItem->setText("Neptune Gravity 1.12 g");
	gravityMenu->addChild(neptuneGravityItem);

	// Jupiter gravity 2.36
	CEGUI::Window *jupiterGravityItem = win.createWindow("Ogremonics/MenuItem",
			"jupiterGravityItem");
	jupiterGravityItem->setText("Jupiter Gravity 2.36 g");
	gravityMenu->addChild(jupiterGravityItem);

	// Sun gravity 27.930682977
	CEGUI::Window *sunGravityItem = win.createWindow("Ogremonics/MenuItem",
			"sunGravityItem");
	sunGravityItem->setText("Sun Gravity 27.9 g");
	gravityMenu->addChild(sunGravityItem);

	// Custom gravity...
	CEGUI::Window *customGravityItem = win.createWindow("Ogremonics/MenuItem",
			"customGravityItem");
	customGravityItem->setText("Custom Gravity");
	gravityMenu->addChild(customGravityItem);

	//#####################
	// Help menu
	CEGUI::Window *helpTopItem = win.createWindow("Ogremonics/MenuItem",
			"helpTopItem");
	helpTopItem->setText("Help");
	menuBar->addChild(helpTopItem);
	CEGUI::Window *helpMenu = win.createWindow("Ogremonics/PopupMenu",
			"helpMenu");
	helpTopItem->addChild(helpMenu);

	// About
	CEGUI::Window *aboutItem = win.createWindow("Ogremonics/MenuItem",
			"aboutItem");
	aboutItem->setText("About");
	helpMenu->addChild(aboutItem);

	sheet->addChild(menuBar);
	return sheet;
}

void SimulationManager::createDebugPanels() {
	ParamsPanel::VectorStringPairs items;

	items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
	items.push_back(ParamsPanel::PairString("Run time", "0"));		// 0
	mFpsPanel = ParamsPanel::createParamsPanel(CEGUI_INFOPANEL_BORDER,
			(int) mWindow->getHeight()
					- (3 * CEGUI_INFOPANEL_BORDER + CEGUI_INFOPANEL_CAPTION
							+ CEGUI_INFOPANEL_TEXT * items.size()), "FPS", 150,
			items, mLayout);

	items.clear();
	items.push_back(ParamsPanel::PairString("cam.pX", "0"));		// 0
	items.push_back(ParamsPanel::PairString("cam.pY", "0"));		// 1
	items.push_back(ParamsPanel::PairString("cam.pZ", "0"));		// 2
	items.push_back(ParamsPanel::PairString("", ""));		// 3
	items.push_back(ParamsPanel::PairString("cam.oW", "0"));		// 4
	items.push_back(ParamsPanel::PairString("cam.oX", "0"));		// 5
	items.push_back(ParamsPanel::PairString("cam.oY", "0"));		// 6
	items.push_back(ParamsPanel::PairString("cam.oZ", "0"));		// 7
	items.push_back(ParamsPanel::PairString("", ""));		// 8
	items.push_back(ParamsPanel::PairString("Filtering", "None"));		// 9
	items.push_back(ParamsPanel::PairString("Poly Mode", "Solid"));		// 10
	mDetailsPanel = ParamsPanel::createParamsPanel(
			(int) mWindow->getWidth() - 200 - CEGUI_INFOPANEL_BORDER,
			CEGUI_INFOPANEL_BORDER * 4, "Debug", 200, items, mLayout);
	mDetailsPanel->hide();

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

ParamsPanel * &SimulationManager::getDetailsPanel() {
	return mDetailsPanel;
}

ParamsPanel * &SimulationManager::getFpsPanel() {
	return mFpsPanel;
}

void SimulationManager::setDetailsPanel(ParamsPanel*& detailsPanel) {
	mDetailsPanel = detailsPanel;
}

void SimulationManager::setFpsPanel(ParamsPanel* fpsPanel) {
	mFpsPanel = fpsPanel;
}

CEGUI::Window * &SimulationManager::getLayout() {
	return mLayout;
}

#endif
