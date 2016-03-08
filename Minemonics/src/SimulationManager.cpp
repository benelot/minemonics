// In case you are getting a strange error in OgreMemoryNedPooling when shutting your program down, check this:
// Main extracts
// I had the same problem. I used CEGUI library. CEGUI was linked to libOgreMain_d library and my application was linked to libOgreMain library.
// You can check this by typing:
// ldd ./your-application
// Solution is to link your application and all libraries to the same build type of Ogre library.
// http://ogre3d.org/forums/viewtopic.php?f=2&t=59691

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
#include <utils/serialization/FilesystemManipulator.hpp>

SimulationManager* SimulationManager::mSimulationManager;
BoostLogger SimulationManager::mBoostLogger;  // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
	mStateHandler(), mInputHandler(), mCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_01), mSun(NULL) {

	mSimulationManager = this; /**!< Initialize the singleton*/
	mRandomness = new Randomness(); /**!< Initialize the singleton*/
	gContactProcessedCallback = processContactCallback; /**!< set the contact processor callback */

	// main frame timer initialization
	mApplicationStart = mOgreTimer.getMilliseconds(); /**!< Initialize when the application started running */
	mInputClock = mApplicationStart; /**!< Initialize the last time the input was updated */
	mPreviousModelIteration = mApplicationStart;
	mThisModelIteration = mApplicationStart;
	mApplicationRuntime = mThisModelIteration - mApplicationStart; /**!< Initialize the application runtime */

	// sub frame time initializations
	mGraphicsStart = mApplicationStart; /** !< Initialize the last graphics start */
	mModelStart = mApplicationStart; /** !< Initialize the last model start */
	mInputStart = mApplicationStart; /** !< Initialize the last input start */

	mPhysicsStepStart = mApplicationStart; /**!< Initialize the physics step start */
	mPhysicsStepEnd = mApplicationStart; /**!< Initialize the physics step end */

	//durations
	mLastGraphicsTick = 0;
	mLastModelTick = 0;
	mLastInputTick = 0;
	mPhysicsTick = 0;

	mInputDt = 0;
	mModelAccumulator = 0;
	mFrameTime = 0;
}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Destroy Scene...";
	destroyScene(); /**!< tear down the scene */
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Destroy Scene...done.";

	// destroy the ogre renderer system
	// http://cegui.org.uk/wiki/CEGUI_In_Practice_-_Introduction
	//http://cegui.org.uk/forum/viewtopic.php?t=6166
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Shutdown CEGUI...";
	CEGUI::OgreRenderer::destroySystem();
	CEGUI::System::destroy();
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Shutdown CEGUI...done.";

	//This is used past this line because the destructors are called on it
//	mSimulationManager = NULL;
	delete mRandomness;
	mRandomness = NULL;
}

void SimulationManager::setupView(void) {
	Ogre::Camera* camera = mSceneMgr->createCamera("ObserverCamera"); /**!< Create the camera */
	mViewController.getCameraHandler().setCamera(camera);

	Ogre::Viewport* vp = mWindow->addViewport(camera); /**!< Create one viewport, entire window */
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	camera->setAspectRatio( /**!< Alter the camera aspect ratio to match the viewport */
	Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

//-------------------------------------------------------------------------------------
/**
 * Creates the scene of the application.
 */
void SimulationManager::createScene(void) {

	// file folders
	mSerializationPath = FilesystemManipulator::createFolder(".", /**!< Create the serialization top folder if necessary */
	SerializationConfiguration::TOP_FOLDER);
	FilesystemManipulator::createFolder(".", /**!< Create the logging top folder if necessary */
	LoggerConfiguration::TOP_FOLDER);

	Logger::init("logs/minemonics.log", LoggerConfiguration::LOGGING_LEVEL); /**!< Initialize the logger */
	Ogre::LogManager::getSingleton().setLogDetail(Ogre::LL_LOW); /**!< Reduce the ogre log detail */

	// drop introducing application line
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "\n"<< "########################################################";
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< ApplicationConfiguration::APPLICATION_TITLE << " #####\n";

	Ogre::RenderTarget* renderTarget = mRoot->getRenderTarget( /**!< Set render target with the current application name */
	ApplicationConfiguration::APPLICATION_TITLE);

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize ViewController...";
	mViewController.initialize(renderTarget); /**!< initialize GUI and views */
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize ViewController...done.";

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Switch state to GUI...";
	mStateHandler.requestStateChange(StateHandler::GUI); /**!< request a state change saying that the GUI is shown */
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Switch state to GUI...done.";

	// initialize the simulation's debug drawer
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize DebugDrawer...";
	mDebugDrawer.initialize(false);
	mDebugDrawer.setDebugDrawingEnabled(false);
	mDebugDrawer.setDrawWireframe(true);
	mDebugDrawer.setDrawConstraints(true);
	mDebugDrawer.setDrawConstraintLimits(true);
	mDebugDrawer.setDrawContactPoints(false);
	mDebugDrawer.setDrawNormals(false);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize DebugDrawer...done.";

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup universe...";

	mSceneMgr->setAmbientLight(
		/**!< Set default ambient light */
		Ogre::ColourValue(EnvironmentConfiguration::AMBIENT_R,
			EnvironmentConfiguration::AMBIENT_G,
			EnvironmentConfiguration::AMBIENT_B));

	// choose a random skybox
	int skyindex = Randomness::getSingleton()->nextUnifPosInt(1, 30);
	std::string skyboxstring = std::string("Examples/SpaceSkyBox")
		+ std::string(1 - (skyindex >= 10), '0')
		+ std::string(boost::lexical_cast<std::string>(skyindex));
	mSceneMgr->setSkyBox(true, skyboxstring, 4000, true);

	// setup the shadows
	mSceneMgr->setShadowTechnique(
		(mViewController.doesShowShadows()) ?
			Ogre::SHADOWTYPE_STENCIL_MODULATIVE : Ogre::SHADOWTYPE_NONE);

	//add some filtering to reduce the moiree effect
	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(
		Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);

	//Set fog color and fading function
	Ogre::ColourValue fadeColour(0, 0, 0);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0, 8000, 30000);
//	mSceneMgr->setFog(Ogre::FOG_EXP, fadeColour, 0.002);
//	mSceneMgr->setFog(Ogre::FOG_EXP2, fadeColour, 0.002);

	// set up the sun
	mSun = mSceneMgr->createLight();
	mSun->setType(Ogre::Light::LT_DIRECTIONAL);
	mSun->setDiffuseColour(Ogre::ColourValue(1, 1, 0.2));
	mSun->setSpecularColour(Ogre::ColourValue(1, 1, 0.2));
	mSun->setDirection(0, -1, -1);

	mUniverse.initialize(EvaluationConfiguration::DEFAULT_PARALLEL_EVALUATION); /**!< Initialize the universe */

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Setup universe...done.";

	mStateHandler.requestStateChange(StateHandler::SIMULATION); /**!< request a state change saying that the simulation is running */
}

//-------------------------------------------------------------------------------------
void SimulationManager::createFrameListener(void) {
	windowResized(mWindow); /**!< Set initial mouse clipping size */

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize GUI listeners...";
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this); /**!< Register as a Window and Frame listener */
	mRoot->addFrameListener(this);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize GUI listeners...done.";
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

	//##############
	// breaking conditions
	if (mWindow->isClosed()
		|| mStateHandler.getCurrentState() == StateHandler::SHUTDOWN) { /**!< shutdown the application if the application has initiated shutdown */

		if (mVideoWriter.isInitialized()) { /**!< shutdown the video writer if it is still running */
			mVideoWriter.close();
		}
		return false;
	}

	mSceneMgr->setShadowTechnique(
		(mViewController.doesShowShadows()) ?
			Ogre::SHADOWTYPE_STENCIL_MODULATIVE : Ogre::SHADOWTYPE_NONE); /**!< turn on or off the shadows. */

	//#############
	// model update
	do {
		// update timers
		mThisModelIteration = mOgreTimer.getMilliseconds();
		mFrameTime = mThisModelIteration - mPreviousModelIteration; /**!< Calculate the frame time (in Milliseconds) */
		mPreviousModelIteration = mThisModelIteration;

		mApplicationRuntime = mThisModelIteration - mApplicationStart; /**!< Update main frame timer (in Milliseconds) */

		mModelStart = mOgreTimer.getMilliseconds(); /**!< Begin with the model update (in Milliseconds)*/
		mLastGraphicsTick = mModelStart - mGraphicsStart; /**!< Update graphics timer (in Milliseconds) */

		mUniverse.setSimulationSpeed(mCurrentSimulationSpeed); /**!< Set the current simulation speed of the simulation */

		if (mCurrentSimulationSpeed == PhysicsConfiguration::SIMULATION_SPEED_09 /** If we are in speed 9 or 10*/
			|| mCurrentSimulationSpeed
				== PhysicsConfiguration::SIMULATION_SPEED_10) {
			mPhysicsTick = ApplicationConfiguration::APPLICATION_TICK /**!< calculate the remaining time for physics (in Milliseconds) */
			- mLastGraphicsTick - mLastInputTick;

			mPhysicsStepStart = mOgreTimer.getMilliseconds(); /**!< The physics updates start (in Milliseconds)*/

			while (mPhysicsTick > mPhysicsStepEnd - mPhysicsStepStart) { /**!< Update the physics until we run out of time (in Milliseconds) */
				mUniverse.update(PhysicsConfiguration::FIXED_STEP_SIZE_SEC); /**!< update the universe (in Seconds) */
				mPhysicsStepEnd = mOgreTimer.getMilliseconds(); /**!< Update the last physics step end to stop updating in time (in Milliseconds) */
			}
		} else { /**!< This mode tries to progress as much time as it is expected from the game loop*/
			if (mFrameTime > ApplicationConfiguration::APPLICATION_TICK) { /** cap frametime to make the application lose time, not the physics (in Milliseconds) */
				mFrameTime = ApplicationConfiguration::APPLICATION_TICK;
			}

			mModelAccumulator += mFrameTime; /**!< Update physics update time that we are going to use (in Milliseconds) */
			double speed = pow(2, /**!< calculate the speed of the simulation */
			PhysicsConfiguration::SIMULATION_SPEEDS[mCurrentSimulationSpeed]);

			int steps = floor(
				mModelAccumulator
					/ PhysicsConfiguration::FIXED_STEP_SIZE_MILLI); /**!< Calculate the number of full normal time steps we can take */

			if (steps > 0) { /**!< Update if we can take at least one step */
				mUniverse.update(
					speed * steps * PhysicsConfiguration::FIXED_STEP_SIZE_SEC); /**!< update the universe (in Seconds) */
				mModelAccumulator -= steps
					* PhysicsConfiguration::FIXED_STEP_SIZE_MILLI; /**!< Subtract the number of full normal time steps (in Milliseconds) */
			}
		}

		mInputStart = mOgreTimer.getMilliseconds(); /**!< Start the input update */
		mLastModelTick = mInputStart - mModelStart; /**!< Calculate the time the model update took */

		//#############
		// Input update - Game Clock part of the loop
		/** This runs once every APPLICATION_TICK milliseconds on average */
		mInputDt = mThisModelIteration - mInputClock;
		if (mInputDt >= ApplicationConfiguration::APPLICATION_TICK) {
			mInputClock = mThisModelIteration;
			mInputHandler.injectInput(); /**!< Inject input into handlers */
			mInputHandler.update(mInputClock); /**!< update elements that work on the current input state */
		}

		mGraphicsStart = mOgreTimer.getMilliseconds(); /**!< Start the graphics update */
		mLastInputTick = mGraphicsStart - mInputStart; /**!< Calculate the time the input injection took */

	} while (mStateHandler.getCurrentState()
		== StateHandler::HEADLESS_SIMULATION); /**!< In headless simulation we never update the graphics */

	//#############
	// Graphics update
	updatePanels(evt.timeSinceLastFrame); /**!< Update the information in the panels on screen */

	mViewController.update(evt.timeSinceLastFrame); /**!< Update view */

	mUniverse.drawDebugWorld(); /**!< draw the debug output if enabled */

	return true;
}

void SimulationManager::updatePanels(Ogre::Real timeSinceLastFrame) {

	/** Update all movable panels in view */
	for (std::vector<MovablePanel*>::iterator it =
		mViewController.getMovablePanels().begin();
		it != mViewController.getMovablePanels().end(); it++) {
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

	/** Update the fps panel */
	if (mViewController.getFpsPanel() != NULL) {
		if (mViewController.getFpsPanel()->isVisible()) // if fps panel is visible, then update its contents
		{
			if (mViewController.getFpsPanel()->size() == 3) {
				mViewController.getFpsPanel()->setParamValue(0,
					Ogre::StringConverter::toString(mWindow->getLastFPS()),
					true);
				mViewController.getFpsPanel()->setParamValue(1,
					Ogre::StringConverter::toString(mApplicationRuntime), true);

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

	/** Update the details panel if visible */
	if (mViewController.getDetailsPanel() != NULL) {
		if (mViewController.getDetailsPanel()->isVisible()) /**!< if details panel is visible, then update its contents */
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
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)<< "Repositioning CEGUI pointer...";
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	mViewController.updateMousePosition(mInputHandler.getMousePositionX(), /**!< Align CEGUI mouse with SDL2 mouse */
		mInputHandler.getMousePositionY());

	int wwidth, wheight;
	SDL_GetWindowSize(mSdlWindow, &wwidth, &wheight);
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	mWindow->resize(width, height);
#else
	mWindow->windowMovedOrResized();
#endif

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace) << "Notifying CEGUI of resize....";
	mViewController.notifyDisplaySizeChanged(width, height);
}

/**
 * What to do if the window focus has changed.
 * @param rw The handle of the render window whose focus has changed.
 */
void SimulationManager::windowFocusChange(Ogre::RenderWindow* rw) {
	if (rw->isVisible()) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)<< "Window has gained focus...";

		mViewController.updateMousePosition(mInputHandler.getMousePositionX(), /**!< Align CEGUI mouse with SDL mouse */
			mInputHandler.getMousePositionY());
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace) << "Window has lost focus...";
	}
}
//-------------------------------------------------------------------------------------

/**
 * Destroy the scene if the application is quit.
 */
void SimulationManager::destroyScene(void) {
	mUniverse.teardown();
//	delete mSun;
//	mSun = NULL;
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

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize InputHandler...";
	mInputHandler.initialize();
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize InputHandler...done.";

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize SDL...";
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Cannot initialize SDL2!", "GraphicsSystem::initialize");
	}
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize SDL...done.";

	// Show the configuration dialog and initialize the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize Ogre3D...";
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
	std::vector<std::string> elems;
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

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Initialize Ogre3D...done.";

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

/**
 * Create a timestamp anything that needs one.
 * @return
 */
std::string SimulationManager::getTimeStamp() {
	namespace pt = boost::posix_time;
	pt::ptime now = pt::microsec_clock::local_time();
	std::stringstream ss;
	ss << now.date().year() << static_cast<int>(now.date().month())
		<< now.date().day() << now.time_of_day().hours()
		<< now.time_of_day().minutes() << now.time_of_day().seconds()
		<< now.time_of_day().fractional_seconds();
	return ss.str();
}

#endif
