//# corresponding header
#include <SimulationManager.hpp>

//# forward declarations
//# system headers
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>

//## controller headers
#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <SDL_syswm.h>
#include <SDL_video.h>

//## model headers
#include <boost/log/core/record.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/operators.hpp>
#include <boost/parameter/keyword.hpp>

//## view headers
#include <CEGUI/GUIContext.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/System.h>
#include <CEGUI/Vector.h>
#include <OgreCamera.h>
#include <OgreColourValue.h>
#include <OgreCommon.h>
#include <OgreConfigOptionMap.h>
#include <OgreException.h>
#include <OgreFrameListener.h>
#include <OgreNode.h>
#include <OgrePlatform.h>
#include <OgreQuaternion.h>
#include <OgreRenderSystem.h>
#include <OgreRenderSystemCapabilities.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreUTFString.h>
#include <OgreVector3.h>
#include <OgreViewport.h>
#include <OgreWindowEventUtilities.h>
#include <Renderer.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/ApplicationConfiguration.hpp>
#include <configuration/EnvironmentConfiguration.hpp>
#include <configuration/EvaluationConfiguration.hpp>
#include <configuration/EvolutionConfiguration.hpp>
#include <configuration/LoggerConfiguration.hpp>
#include <configuration/OgreSystemConfigStrings.hpp>
#include <configuration/SerializationConfiguration.hpp>

//## controller headers
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/Planet.hpp>

//## model headers
#include <model/universe/Epoch.hpp>
#include <model/universe/CollisionHandler.hpp>

//## view headers
#include <view/visualization/CEGUI/infopanels/graphpanels/MathGLPanel.hpp>

//## utils headers
#include <utils/Randomness.hpp>

SimulationManager* SimulationManager::mSimulationManager;
BoostLogger SimulationManager::mBoostLogger;  // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
	mStateHandler(), mInputHandler(), mSdlWindow(NULL), mSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_01), mMousePicker(
		&mViewController), mSun(NULL) {
	// Initialize the singleton
	mSimulationManager = this;

	//initialize the singleton
	mRandomness = new Randomness();

	//set the contact processor callback
	gContactProcessedCallback = processContactCallback;

	// main frame timer initialization
	mStart = time.getMilliseconds();
	mApplicationClock = mStart;
	mPrevious = mStart;
	mNow = mStart;
	mRuntime = mNow - mStart;

	mGraphicsStart = mStart;

	mModelStart = mStart;

	mInputStart = mStart;

	mPhysicsStepStart = mStart;
	mPhysicsStepEnd = mStart;

	//durations
	mLastGraphicsTick = 0;
	mLastModelTick = 0;
	mLastInputTick = 0;
	mPhysicsTick = 0;

	mApplicationDt = 0;
	mAccumulator = 0;
	mFrameTime = 0;
}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {

	// tear down the scene
	destroyScene();

	// destroy the ogre renderer system
	CEGUI::OgreRenderer::destroySystem();

	//delete static randomness
	delete mRandomness;
}

void SimulationManager::setupView(void) {

	// Create the camera
	Ogre::Camera* camera = mSceneMgr->createCamera("PlayerCam");
	mViewController.getCameraHandler().setCamera(camera);

	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(camera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	camera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
/**
 * Creates the scene of the application.
 */
void SimulationManager::createScene(void) {

	// Initialize the logger
	Logger::init("minemonics.log", LoggerConfiguration::LOGGING_LEVEL);
	Logger::initTermSink();

	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_LOW);

	// Set render target with the current application name
	Ogre::RenderTarget* renderTarget = mRoot->getRenderTarget(
		ApplicationConfiguration::APPLICATION_TITLE);

	// initialize GUI and views
	mViewController.initialize(renderTarget, &mStateHandler);

	// request a state change saying that the GUI is shown
	mStateHandler.requestStateChange(StateHandler::GUI);

	//################################################################

	// initialize the simulation's debug drawer
	mDebugDrawer.initialize(mSceneMgr, false);
	mDebugDrawer.setDebugDrawingEnabled(false);
	mDebugDrawer.setDrawWireframe(true);
	mDebugDrawer.setDrawConstraints(true);
	mDebugDrawer.setDrawConstraintLimits(true);
	mDebugDrawer.setDrawContactPoints(false);
	mDebugDrawer.setDrawNormals(false);

	// ###################
	// We create the evaluation scene defined by the planet to be evaluated
	// ###################
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
		<< "Setup evaluation environment...";

	// Set default ambient light
	mSceneMgr->setAmbientLight(
		Ogre::ColourValue(EnvironmentConfiguration::AMBIENT_R,
			EnvironmentConfiguration::AMBIENT_G,
			EnvironmentConfiguration::AMBIENT_B));

	// either create a skydome or a skyplane
//	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 4000, true);
//	mSceneMgr->setSkyDome(true, "Examples/SpaceSkyDome1", 10, 1, 15000, true);

	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox2", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/StormSkyBox", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox1", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/SceneSkyBox2", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/TrippySkyBox", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/EarlyMorningSkyBox", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/MorningSkyBox", 4000, true);
//	mSceneMgr->setSkyBox(true, "Examples/EveningSkyBox", 4000, true);

	//  Create skyplane
	//	Ogre::Plane plane;
	//	plane.d = 100;
	//	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	//	mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 500, 20, true,
	//			0.5, 150, 150);
//	Examples/SpaceSkyPlane

	mSceneMgr->setShadowTechnique(
		(mViewController.doesShowShadows()) ?
			Ogre::SHADOWTYPE_STENCIL_MODULATIVE : Ogre::SHADOWTYPE_NONE);

	//add some filtering to reduce the moire effect
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(
		Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);

	//Set fog color and fading function
	Ogre::ColourValue fadeColour(0, 0, 0);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 17000, 30000);
//	mSceneMgr->setFog(Ogre::FOG_EXP, fadeColour, 0.002);
//	mSceneMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.002);

	// ###################
	// We initialize the universe
	// ###################
	mSun = mSceneMgr->createLight();
	mSun->setType(Ogre::Light::LT_DIRECTIONAL);
	mSun->setDiffuseColour(Ogre::ColourValue(1, 1, 0.2));
	mSun->setSpecularColour(Ogre::ColourValue(1, 1, 0.2));
	mSun->setDirection(0, -1, -1);

	mUniverse.initialize(EvaluationConfiguration::DEFAULT_PARALLEL_EVALUATION);

	// create the serialization top folder if necessary
	mSerializationPath = FilesystemManipulator::createFolder(".",SerializationConfiguration::TOP_FOLDER);

//	// create a planet called earth
//	Planet* earth = new Planet(PhysicsController::FeatherstoneModel,
//		Environment::PLANE, 20, mSun);
//
//	Epoch* oneEarthEpoch = new Epoch();
//	oneEarthEpoch->addJuryType(Jury::AVG_VELOCITY, 1, true);
//	oneEarthEpoch->addJuryType(Jury::AVG_HEIGHT, 1, false);
//
//	earth->addEpoch(oneEarthEpoch);
//
//	// add earth to universe
//	mUniverse.addPlanet(earth);
//
//	// create a population
//	Population* earthPopulation = new Population();
//	earthPopulation->initialize(earth, 100,
//		EvolutionConfiguration::ROOT_POSITION);
//
//	// add earth population to earth
//	earth->addPopulation(earthPopulation);

//	// create a population
//	Population* earth2Population = new Population();
//	earth2Population->initialize(earth, 100,
//			EvolutionConfiguration::ROOT_POSITION);

//	// add earth population to earth
//	earth->addPopulation(earth2Population);

//	TODO::Make it work with multiple planets
	// create a planet called mars
//	Planet* mars = new Planet(PhysicsController::FeatherstoneController,
//		Environment::PLANE, 20, mSun);
//
//	Epoch* oneMarsEpoch = new Epoch();
//	oneMarsEpoch->addJuryType(Jury::AVG_VELOCITY, 1, true);
//	oneMarsEpoch->addJuryType(Jury::AVG_HEIGHT, 1, false);
//
//	mars->addEpoch(oneMarsEpoch);
//
//	// add mars to universe
//	mUniverse.addPlanet(mars);
//
//	// create a population
//	Population* marsPopulation = new Population();
//	marsPopulation->initialize(mars, 10, EvolutionConfiguration::ROOT_POSITION);
//
//	// add earth population to mars
//	mars->addPopulation(marsPopulation);

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
		<< "Setup evaluation environment...done.";

	// request a state change saying that the simulation is running
	mStateHandler.requestStateChange(StateHandler::SIMULATION);
}

//-------------------------------------------------------------------------------------
void SimulationManager::createFrameListener(void) {

	// Set initial mouse clipping size
	windowResized (mWindow);

	// Register as a Window and Frame listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
	mRoot->addFrameListener(this);
}

/**
 * Called after all render targets have had their rendering commands
 * issued, but before render windows have been asked to flip their
 * buffers over.
 * @param evt
 * 		Information about the frame rendering.
 * @remarks
 * 		The usefulness of this event comes from the fact that rendering
 * commands are queued for the GPU to process. These can take a little
 * while to finish, and so while that is happening the CPU can be doing
 * useful things. Once the request to 'flip buffers' happens, the thread
 * requesting it will block until the GPU is ready, which can waste CPU
 * cycles. Therefore, it is often a good idea to use this callback to
 * perform per-frame processing. Of course because the frame's rendering
 * commands have already been issued, any changes you make will only
 * take effect from the next frame, but in most cases that's not noticeable.
 * @return
 * 		True to continue rendering, false to drop out of the rendering loop.
 */
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	// structure according to the canonical game loop
	// http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Canonical_Game_Loop

	// shutdown the application if the application has initiated shutdown
	if (mWindow->isClosed()
		|| mStateHandler.getCurrentState() == StateHandler::SHUTDOWN) {

		//shutdown the video writer if it is still running
		if (mVideoWriter.isInitialized()) {
			mVideoWriter.close();
		}
		return false;
	}

	//turn on or off the shadows.
	mSceneMgr->setShadowTechnique(
		(mViewController.doesShowShadows()) ?
			Ogre::SHADOWTYPE_STENCIL_MODULATIVE : Ogre::SHADOWTYPE_NONE);

	//#############
	// Physics handling part
	//#############
	/* This, like the rendering, ticks every time around.
	 Bullet does the interpolation for us. */
	do {
		// update timers
		mNow = time.getMilliseconds();
		mFrameTime = mNow - mPrevious;
		mPrevious = mNow;

		// update main frame timer
		mRuntime = mNow - mStart;

		mModelStart = time.getMilliseconds();
		mLastGraphicsTick = mModelStart - mGraphicsStart;

		// step the physics forward
		mUniverse.setSimulationSpeed(mSimulationSpeed);

		if (mSimulationSpeed == PhysicsConfiguration::SIMULATION_SPEED_09
			|| mSimulationSpeed == PhysicsConfiguration::SIMULATION_SPEED_10) {
			mPhysicsTick = ApplicationConfiguration::APPLICATION_TICK
				- mLastGraphicsTick - mLastInputTick;

			mPhysicsStepStart = time.getMilliseconds();

			while (mPhysicsTick > mPhysicsStepEnd - mPhysicsStepStart) {
				// update the universe
				mUniverse.update(
					PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEP_SIZE_SEC);
				mPhysicsStepEnd = time.getMilliseconds();
			}
		} else {
			//cap frametime to make the application lose time, not the physics
			if (mFrameTime > ApplicationConfiguration::APPLICATION_TICK) {
				mFrameTime = ApplicationConfiguration::APPLICATION_TICK;
			}

			mAccumulator += mFrameTime;

			while (mAccumulator
				>= PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEP_SIZE_MILLI) {
				// update the universe
				mUniverse.update(
					PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEP_SIZE_SEC);
				mAccumulator -=
					PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEP_SIZE_MILLI;
			}
		}

		mInputStart = time.getMilliseconds();
		mLastModelTick = mInputStart - mModelStart;

		//#############
		// Input part
		//#############
		// Game Clock part of the loop
		/*  This ticks once every APPLICATION_TICK milliseconds on average */
		mApplicationDt = mNow - mApplicationClock;
		if (mApplicationDt >= ApplicationConfiguration::APPLICATION_TICK) {
			mApplicationClock = mNow;
			// Inject input into handlers
			mInputHandler.injectInput();

			//update elements that work on the current input state
			mInputHandler.update(mApplicationClock);

		}
		mGraphicsStart = time.getMilliseconds();
		mLastInputTick = mGraphicsStart - mInputStart;

	} while (mStateHandler.getCurrentState()
		== StateHandler::HEADLESS_SIMULATION);

	//#############
	// Graphics part
	//#############

	// update the information in the panels on screen
	updatePanels(evt.timeSinceLastFrame);

	// update view
	mViewController.update(evt.timeSinceLastFrame);

	// draw the debug output if enabled
	mUniverse.drawDebugWorld();

	return true;
}

void SimulationManager::updatePanels(Ogre::Real timeSinceLastFrame) {

	std::vector<MovablePanel*>::iterator it =
		mViewController.getMovablePanels().begin();
	for (; it != mViewController.getMovablePanels().end(); it++) {
		switch ((*it)->getType()) {
		case MovablePanel::GRAPHPANEL: {
			((MathGLPanel*) (*it))->update(timeSinceLastFrame);
			break;
		}
		default: {
			break;
		}
		}

	}

	if (mViewController.getFpsPanel() != NULL) {
		if (mViewController.getFpsPanel()->isVisible()) // if fps panel is visible, then update its contents
		{
			if (mViewController.getFpsPanel()->size() == 3) {
				mViewController.getFpsPanel()->setParamValue(0,
					Ogre::StringConverter::toString(mWindow->getLastFPS()),
					true);
				mViewController.getFpsPanel()->setParamValue(1,
					Ogre::StringConverter::toString(mRuntime), true);

//				if (mTerrain->mEnvironmentType == Environment::HILLS) {
//					if (((HillsO3D*) mTerrain)->mTerrainGroup->isDerivedDataUpdateInProgress()) {
//						if (((HillsO3D*) mTerrain)->mTerrainsImported) {
//							mFpsPanel->setParamValue(2,
//									"Building terrain, please wait...", true);
//						} else {
//							mFpsPanel->setParamValue(2,
//									"Updating textures, patience...", true);
//						}
//					} else {
//						mFpsPanel->setParamValue(2, "Idle.", true);
//						if (((HillsO3D*) mTerrain)->mTerrainsImported) {
//							((HillsO3D*) mTerrain)->mTerrainGroup->saveAllTerrains(
//									true);
//							((HillsO3D*) mTerrain)->mTerrainsImported = false;
//						}
//					}
//				}
			} else {
				Ogre::RenderTarget::FrameStats fs = mWindow->getStatistics();
				mViewController.getFpsPanel()->setParamValue(0,
					Ogre::StringConverter::toString(fs.lastFPS), false);
				mViewController.getFpsPanel()->setParamValue(1,
					Ogre::StringConverter::toString(fs.avgFPS), false);
				mViewController.getFpsPanel()->setParamValue(2,
					Ogre::StringConverter::toString(fs.bestFPS), false);
				mViewController.getFpsPanel()->setParamValue(3,
					Ogre::StringConverter::toString(fs.worstFPS), false);
				mViewController.getFpsPanel()->setParamValue(4,
					Ogre::StringConverter::toString(fs.triangleCount), false);
				mViewController.getFpsPanel()->setParamValue(5,
					Ogre::StringConverter::toString(fs.batchCount), true);
			}
		}
	}
	if (mViewController.getDetailsPanel() != NULL) {
		if (mViewController.getDetailsPanel()->isVisible()) // if details panel is visible, then update its contents
		{
			mViewController.getDetailsPanel()->setParamValue(0,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedPosition().x),
				false);
			mViewController.getDetailsPanel()->setParamValue(1,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedPosition().y),
				false);
			mViewController.getDetailsPanel()->setParamValue(2,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedPosition().z),
				false);
			mViewController.getDetailsPanel()->setParamValue(4,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedOrientation().w),
				false);
			mViewController.getDetailsPanel()->setParamValue(5,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedOrientation().x),
				false);
			mViewController.getDetailsPanel()->setParamValue(6,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedOrientation().y),
				false);
			mViewController.getDetailsPanel()->setParamValue(7,
				Ogre::StringConverter::toString(
					mViewController.getCameraHandler().getCamera()->getDerivedOrientation().z),
				true);
		}
	}
}

/**
 * What to do if the window is resized.
 * @param rw The handle of the render window that was resized.
 */
void SimulationManager::windowResized(Ogre::RenderWindow* rw) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)
		<< "Repositioning CEGUI pointer...";
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	// Align CEGUI mouse with SDL2 mouse
	mViewController.updateMousePosition(mInputHandler.getMousePositionX(),
		mInputHandler.getMousePositionY());

	int wwidth, wheight;
	SDL_GetWindowSize(mSdlWindow, &wwidth, &wheight);
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	mWindow->resize(width, height);
#else
	mWindow->windowMovedOrResized();
#endif

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)
		<< "Notifying CEGUI of resize....";
	mViewController.notifyDisplaySizeChanged(width, height);
}

/**
 * What to do if the window focus has changed.
 * @param rw The handle of the render window whose focus has changed.
 */
void SimulationManager::windowFocusChange(Ogre::RenderWindow* rw) {
	if (rw->isVisible()) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)
			<< "Window has gained focus...";

		// Align CEGUI mouse with SDL mouse
		mViewController.updateMousePosition(mInputHandler.getMousePositionX(),
			mInputHandler.getMousePositionY());
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)
			<< "Window has lost focus...";
	}
}
//-------------------------------------------------------------------------------------

/**
 * Destroy the scene if the application is quit.
 */
void SimulationManager::destroyScene(void) {
}
//-------------------------------------------------------------------------------------

/**
 * Quit the application.
 * @return Returns true if the application could be closed normally.
 */
bool SimulationManager::quit() {
	mStateHandler.requestStateChange(StateHandler::SHUTDOWN);
	mShutDown = true;
	return true;
}

/**
 * Configure and set up the window and the render window for the simulator
 */
bool SimulationManager::configure(void) {

	mInputHandler.initialize();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Cannot initialize SDL2!", "GraphicsSystem::initialize");
	}

	// Show the configuration dialog and initialize the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if (!mRoot->restoreConfig()) {
		if (!mRoot->showConfigDialog()) {
			mStateHandler.requestStateChange(StateHandler::SHUTDOWN);
		}
	}

	Ogre::ConfigOptionMap& cfgOpts =
		mRoot->getRenderSystem()->getConfigOptions();

	mRoot->getRenderSystem()->setConfigOption("sRGB Gamma Conversion", "Yes");
	mRoot->initialise(false);

	//split resolution string
	std::vector < std::string > elems;
	std::stringstream ss(cfgOpts[OgreConf::VIDEO_MODE].currentValue);
	std::string item;
	while (std::getline(ss, item, 'x')) {
		elems.push_back(item);
	}

	//parse video resolution out of the configuration
	char* end;
	int width = strtol(elems.at(0).c_str(), &end, 10);
	int height = strtol(elems.at(1).c_str(), &end, 10);

	//find the position of the window
	int screen = 0;
	int posX = 0;
	int posY = 0;

	//is the configuration in full screen?
	bool fullscreen = (cfgOpts[OgreConf::FULL_SCREEN].currentValue
		== OgreConf::YES);

	//if full screen
	if (fullscreen) {
		// set the window position to full screen
		posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
		posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
	} else {
		//center the window on the screen
		posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
		posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
	}

	// create the SDL window
	mSdlWindow = SDL_CreateWindow(
		ApplicationConfiguration::APPLICATION_TITLE.c_str(), // window title
		posX,               // initial x position
		posY,               // initial y position
		width,              // width, in pixels
		height,             // height, in pixels
		SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
			| SDL_WINDOW_RESIZABLE);

	//Get the native window handle
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);

	if (SDL_GetWindowWMInfo(mSdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)", "GraphicsSystem::initialize");
	}

	Ogre::String winHandle;
	Ogre::NameValuePairList params;

	switch (wmInfo.subsystem) {
#ifdef WIN32
	case SDL_SYSWM_WINDOWS:
	// required to make OGRE work on Windows
	winHandle = Ogre::StringConverter::toString( (unsigned long)wmInfo.info.win.window );
	break;
#elif __MACOSX__
	case SDL_SYSWM_COCOA:
	//required to make OGRE work on MAC OSX
	params.insert( std::make_pair("macAPI", "cocoa") );
	params.insert( std::make_pair("macAPICocoaUseNSView", "true") );

	winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
	break;
#else
	case SDL_SYSWM_X11:
		//required to make OGRE work on Linux
		winHandle = Ogre::StringConverter::toString(
			(unsigned long) wmInfo.info.x11.window);
		break;
#endif
	default:
		// in case it can not recognize the windowing system
		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
			"Unexpected WM! (SDL2)", "GraphicsSystem::initialize");
		break;
	}

	//put together the parameter list for the OGRE render window
	params.insert(
		std::make_pair("title", ApplicationConfiguration::APPLICATION_TITLE));
	params.insert(std::make_pair("gamma", "false"));
	params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
	params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	params.insert(std::make_pair("externalWindowHandle", winHandle));
#else
	params.insert(std::make_pair("parentWindowHandle", winHandle));
#endif

	// create the OGRE render window
	mWindow = Ogre::Root::getSingleton().createRenderWindow(
		ApplicationConfiguration::APPLICATION_TITLE, width, height, fullscreen,
		&params);
	return true;
}

/**
 * The main function of the simulator.
 */
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
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
		MessageBox(NULL, e.getFullDescription().c_str(),
			"An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: "
		<< e.getFullDescription().c_str() << std::endl;
#endif
	}

	return 0;
}

#ifdef __cplusplus
}

std::string SimulationManager::getTimeStamp() {
	namespace pt = boost::posix_time;
	pt::ptime now = pt::microsec_clock::local_time();
	std::stringstream ss;
	ss << now.date().year() << static_cast<int>(now.date().month()) << now.date().day()
	    << now.time_of_day().hours() << now.time_of_day().minutes() << now.time_of_day().seconds() << now.time_of_day().fractional_seconds();
	return ss.str();
}

#endif
