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

//configuration
#include "configuration/EnvironmentConfiguration.h"

// view
#include "view/general/evolution/environments/Environment.h"
#include "view/ogre3D/evolution/environments/HillsO3D.h"
#include "view/ogre3D/evolution/environments/PlaneO3D.h"
#include "view/CEGUI/GUISheetHandler.h"
#include "view/CEGUI/CEGUIBuilder.h"

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

//#define _DEBUGGUI

BoostLogger SimulationManager::mBoostLogger;  // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
//		mInfoLabel(0),
		mCameraHandler(this), mRenderer(0), mLayout(NULL), mSystem(NULL), mInputHandler(
		NULL), mStateHandler(NULL), mGUISheetHandler(NULL), mTerrain(NULL), mDetailsPanel(
		NULL), mFpsPanel(NULL), mTestObject(NULL),parents(EvolutionConfiguration::PopSize,
				ChromosomeT<bool>(EvolutionConfiguration::Dimension)),offsprings(EvolutionConfiguration::PopSize,
				ChromosomeT<bool>(EvolutionConfiguration::Dimension)),jury(1),t(0) {

	// main frame timer initialization
	mStart = boost::posix_time::second_clock::local_time();
	mNow = boost::posix_time::second_clock::local_time();
	mRuntime = mNow - mStart;
}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {
	CEGUI::OgreRenderer::destroySystem();
}

void SimulationManager::destroyScene(void) {
	if (mTerrain->environmentType == Environment::HILLS)
		((HillsO3D*) mTerrain)->destroy();

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
	mInputHandler = new CEGUIInputHandler(mStateHandler, windowHnd, this);
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

	unsigned i, t;

	//
	// initialize random number generator
	//
	boost::posix_time::time_duration duration(mNow.time_of_day());
	Rng::seed(duration.total_milliseconds());

	//
	// maximization task
	//
	parents.setMaximize();
	offsprings.setMaximize();

	//
	// initialize all chromosomes of parent population
	//
	for (i = 0; i < parents.size(); ++i)
		parents[i][0].initialize();

	//
	// evaluate parents (only needed for elitist strategy)
	//
	if (EvolutionConfiguration::NElitists > 0)
		for (i = 0; i < parents.size(); ++i) {
			jury.setEvaluationSubject(parents[i][0]);
			jury.evaluateFitness();
			parents[i].setFitness(jury.getFitness());
		}
}

//-------------------------------------------------------------------------------------
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	// update main frame timer
	mNow = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration mRuntime = mNow - mStart;

	//TODO: Fix keyboard grab problem
//	if(mRuntime.total_seconds() % 10 == 0)
//	{
//		mInputHandler->destroyInputHandler();
//		mInputHandler->initializeInputHandler();
//		mInputHandlerReset = true;
//
//	}
//	else
//	{
//		mInputHandlerReset = false;
//	}

	if (mWindow->isClosed() || mStateHandler->getCurrentState() == SHUTDOWN)
		return false;

	//Need to capture/update each device
	mInputHandler->capture();

	mCameraHandler.reposition(evt.timeSinceLastFrame);

	updatePanels();

	mTestObject->update(evt.timeSinceLastFrame);

	//TODO: Use for creature evolution, but clean up afterwards
	// updateEvolution();

// Inject time elapsed
	CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
	return true;
}

//TODO: Use for creature evolution, but clean up afterwards
void SimulationManager::updateEvolution() {
	//
	// recombine by crossing over two parents
	//
	offsprings = parents;
	int i = 0;
	for (i = 0; i < offsprings.size() - 1; i += 2)
		if (Rng::coinToss(EvolutionConfiguration::CrossProb))
			offsprings[i][0].crossover(offsprings[i + 1][0],
					EvolutionConfiguration::CrossPoints);
	//
	// mutate by flipping bits
	//
	for (i = 0; i < offsprings.size(); ++i)
		offsprings[i][0].flip(EvolutionConfiguration::FlipProb);
	//
	// evaluate objective function
	//
	for (i = 0; i < offsprings.size(); ++i) {
		jury.setEvaluationSubject((offsprings[i][0]));
		jury.evaluateFitness();
		offsprings[i].setFitness(jury.getFitness());
	}
	//
	// scale fitness values and use proportional selection
	//
	//offsprings.linearDynamicScaling(window, t);
	parents.selectProportional(offsprings, EvolutionConfiguration::NElitists);

	t++;
	//
	// print out best value found so far
	//
	std::cout<< "Generation " << t << "s best individual has fitness value " << "\t" << parents.best().fitnessValue() << std::endl;

}

void SimulationManager::updatePanels() {
	if (mFpsPanel != NULL) {
		if (mFpsPanel->isVisible()) // if fps panel is visible, then update its contents
		{
			if (mFpsPanel->size() == 3) {
				mFpsPanel->setParamValue(0,
						Ogre::StringConverter::toString(mWindow->getLastFPS()),
						true);
				mFpsPanel->setParamValue(1,
						Ogre::StringConverter::toString(
								mRuntime.total_milliseconds()), true);

				if (mTerrain->environmentType == Environment::HILLS) {
					if (((HillsO3D*) mTerrain)->mTerrainGroup->isDerivedDataUpdateInProgress()) {
						if (((HillsO3D*) mTerrain)->mTerrainsImported) {
							mFpsPanel->setParamValue(2,
									"Building terrain, please wait...", true);
						} else {
							mFpsPanel->setParamValue(2,
									"Updating textures, patience...", true);
						}
					} else {
						mFpsPanel->setParamValue(2, "Idle.", true);
						if (((HillsO3D*) mTerrain)->mTerrainsImported) {
							((HillsO3D*) mTerrain)->mTerrainGroup->saveAllTerrains(
									true);
							((HillsO3D*) mTerrain)->mTerrainsImported = false;
						}
					}
				}
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

	CEGUIBuilder ceguiBuilder(this);
	CEGUI::Window* menu = ceguiBuilder.createMenu();
	mLayout->addChild(menu);
	setFpsPanel(ceguiBuilder.createFpsPanel());
	mLayout->addChild(getFpsPanel()->getWidgetPanel());
	setDetailsPanel(ceguiBuilder.createDetailsPanel());
	mLayout->addChild(getDetailsPanel()->getWidgetPanel());

	mTestObject = new MathGLWindow(this, 400, 400,
			CEGUI::USize(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.4f, 0)));
	mLayout->addChild(mTestObject->getMathGlWindow());
	mTestObject->getMathGlWindow()->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.5f, 0), CEGUI::UDim(0.3f, 0)));
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

	switch (EnvironmentConfiguration::environmentType) {
	case Environment::HILLS:
		// Create hills
		mTerrain = new HillsO3D(mSceneMgr);
		((HillsO3D*) mTerrain)->configureTerrainDefaults(light);
		((HillsO3D*) mTerrain)->buildTerrain();
		break;
	case Environment::PLANE:
		//create plane
		mTerrain = new PlaneO3D(mSceneMgr);
		((PlaneO3D*) mTerrain)->configureTerrainDefaults(light);
		((PlaneO3D*) mTerrain)->buildTerrain();
		break;
	case Environment::OPENSEA:
		break;
	}

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
	return mInputHandler;
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

	const OIS::MouseState &ms = mInputHandler->getMouse()->getMouseState();
	ms.width = width;
	ms.height = height;

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Notifying CEGUI of resize....";
	mSystem->notifyDisplaySizeChanged(CEGUI::Size<float>(width,height));
}

void SimulationManager::windowFocusChange(Ogre::RenderWindow* rw) {
	if (rw->isVisible()) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Window has gained focus...";
		mInputHandler->initializeInputHandler();
		// Align CEGUI mouse with OIS mouse
		const OIS::MouseState state =
		getInputHandler()->getMouse()->getMouseState();
		CEGUI::Vector2f mousePos =
		mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
				state.X.abs - mousePos.d_x, state.Y.abs - mousePos.d_y);
	}
	else
	{
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Window has lost focus...";
		mInputHandler->destroyInputHandler();
	}
}

CEGUI::System*& SimulationManager::getCEGUISystem() {
	return mSystem;
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

void SimulationManager::setDetailsPanel(ParamsPanel* detailsPanel) {
	mDetailsPanel = detailsPanel;
}

void SimulationManager::setFpsPanel(ParamsPanel* fpsPanel) {
	mFpsPanel = fpsPanel;
}

CEGUI::Window * &SimulationManager::getLayout() {
	return mLayout;
}

Ogre::SceneManager* &SimulationManager::getSceneManager() {
	return mSceneMgr;
}

CEGUI::OgreRenderer* & SimulationManager::getRenderer() {
	return mRenderer;
}

Ogre::Root*& SimulationManager::getRoot() {
	return mRoot;
}

#endif
