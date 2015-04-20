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

//# corresponding headers
#include "SimulationManager.h"

//# forward declarations
//# system headers
//## controller headers
#include <btBulletDynamicsCommon.h>

//## model headers
#include <Rng/GlobalRng.h>
#include <OgreVector3.h>

//## view headers
#include <OgreWindowEventUtilities.h>
#include <CEGUI/System.h>
#include <CEGUI/InputEvent.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/FontManager.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <boost/lexical_cast.hpp>

//# custom headers
//## base headers
//## configuration headers
#include "configuration/EnvironmentConfiguration.h"
#include "configuration/OgreSystemConfigStrings.h"
#include "configuration/ApplicationConfiguration.h"

//## controller headers
#include "controller/input/SDL2InputHandler.h"
#include "controller/camera/CameraHandler.h"
#include "controller/SaveController.h"

#include "controller/environments/Environment.h"
#include "controller/environments/Hills.h"
#include "controller/environments/Plane.h"

#include "controller/physics/RagDoll.h"

//## model headers
#include "model/evolution/population/creature/genome/Genome.h"
#include "model/evolution/population/creature/CreatureM.h"

//## view headers
#include "view/CEGUI/GUISheetHandler.h"
#include "view/CEGUI/CEGUIBuilder.h"

//## utils headers
#include "utils/Randomness.h"

BoostLogger SimulationManager::mBoostLogger;  // initialize the static variables
SimulationManager::_Init SimulationManager::_initializer;
//-------------------------------------------------------------------------------------
SimulationManager::SimulationManager(void) :
		mStateHandler(), mGUISheetHandler(), mInputHandler(), mCameraHandler(
				this), mRenderer(0), mLayout(NULL), mSystem(NULL), mTerrain(
		NULL), mDetailsPanel(
		NULL), mFpsPanel(NULL), mDragContainer(NULL), mDrawBulletDebug(true), mDebugDrawer(
		NULL), mSdlWindow(
		NULL) {

	// main frame timer initialization
	mStart = boost::posix_time::microsec_clock::local_time();
	mNow = boost::posix_time::microsec_clock::local_time();
	mRuntime = mNow - mStart;
}
//-------------------------------------------------------------------------------------
SimulationManager::~SimulationManager(void) {

	std::vector<RagDoll*>::iterator it = mRagdolls.begin();
	for (; it != mRagdolls.end(); it++) {
		(*it)->removeFromWorld();
	}

	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->removeFromWorld();
	}

	destroyScene();
	CEGUI::OgreRenderer::destroySystem();
}

void SimulationManager::destroyScene(void) {
	mPhysicsController.exitBulletPhysics();

}

//-------------------------------------------------------------------------------------
void SimulationManager::createFrameListener(void) {

	/// INPUT HANDLER

	// this next bit is for the sake of the input handler
	Ogre::LogManager::getSingletonPtr()->logMessage(
			"*** Initializing SDL2 ***");

	// set up the input handlers

	// since the input handler deals with pushing input to CEGUI, we need to give it a pointer
	// to the CEGUI System instance to use
	mStateHandler.requestStateChange(GUI);

	// make an instance of our GUI sheet handler class
	mGUISheetHandler.initialize(this, mSystem, mLayout, &mStateHandler);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	// Populate the camera container
	mCameraHandler.setCamNode(mCamera->getParentSceneNode());

	// initialize random number generator
	boost::posix_time::time_duration duration(mNow.time_of_day());
	Rng::seed(duration.total_milliseconds());

	mPhysicsController.initBulletPhysics();
	mDebugDrawer = new OgreBtDebugDrawer(mSceneMgr,false);
	mDebugDrawer->setDrawWireframe(true);
	mDebugDrawer->setDrawConstraints(true);
	mDebugDrawer->setDrawConstraintLimits(true);
	mDebugDrawer->setDrawContactPoints(true);
	mDebugDrawer->setDrawNormals(true);

	mPhysicsController.getDynamicsWorld()->setDebugDrawer(mDebugDrawer);

	if (mTerrain->mEnvironmentType == Environment::PLANE) {
		mPhysicsController.addBody(mTerrain->getBody());
	}

	//mPhysicsController.setPhysicsPaused(true);
	Randomness randomness;
	for (int i = 0; i < 10; i++) {
//		RagDoll* ragdoll = new RagDoll(this, randomness.nextDouble(10,100),
//				btVector3(randomness.nextDouble(-5000,5000), randomness.nextDouble(10,5000), randomness.nextDouble(-5000,5000)));
//		mRagdolls.push_back(ragdoll);
//		ragdoll->addToWorld();

		Creature* creature = new Creature();

		creature->initialize(this,
				Ogre::Vector3(randomness.nextDouble(-5000, 5000),
						randomness.nextDouble(10, 5000),
						randomness.nextDouble(-5000, 5000)),
				randomness.nextDouble(0, 30));
		creature->performEmbryogenesis();
		mCreatures.push_back(creature);
		creature->addToWorld();
	}
}

//-------------------------------------------------------------------------------------
bool SimulationManager::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	// update main frame timer
	mNow = boost::posix_time::microsec_clock::local_time();
	mRuntime = mNow - mStart;

	if (mWindow->isClosed() || mStateHandler.getCurrentState() == SHUTDOWN) {
		if (mVideoWriter.isInitialized()) {
			mVideoWriter.close();
		}
		return false;
	}

	// Inject input into handlers;
	mInputHandler.injectInput();

	mCameraHandler.reposition(evt.timeSinceLastFrame);

	mPhysicsController.stepBulletPhysics(evt.timeSinceLastFrame);

	updatePhysics();

	if (mDrawBulletDebug) {
		mPhysicsController.getDynamicsWorld()->debugDrawWorld();
	}

	mInfoOverlay.update();

	updatePanels();

	std::vector<MathGLWindow*>::iterator it = mGraphWindows.begin();
	for (; it != mGraphWindows.end(); it++) {
		(*it)->update(evt.timeSinceLastFrame);
	}

	//TODO: Use for creature evolution, but clean up afterwards
	// updateEvolution();

	return true;
}

void SimulationManager::updatePhysics() {

	std::vector<RagDoll*>::iterator it = mRagdolls.begin();
	for (; it != mRagdolls.end(); it++) {
		(*it)->update();
	}

	std::vector<Creature*>::iterator cit = mCreatures.begin();
	for (; cit != mCreatures.end(); cit++) {
		(*cit)->update();
	}

	const int numObjects =
			mPhysicsController.getDynamicsWorld()->getNumCollisionObjects();

	for (int i = 0; i < numObjects; i++) {
		btCollisionObject* colObj =
				mPhysicsController.getDynamicsWorld()->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(colObj);

		if (body) {

			btVector3 Point = body->getCenterOfMassPosition();

//			std::string text;
//			text.append("O: ");
////			text.append(boost::lexical_cast<std::string>((int)Point[0]));
////			text.append(",");
////			text.append(boost::lexical_cast<std::string>((int)Point[1]));
////			text.append(",");
////			text.append(boost::lexical_cast<std::string>((int)Point[2]));
////			text.append(",\n");
////			text.append("------");
//			InfoOverlayData* data = new InfoOverlayData(
//					Ogre::Vector3((float) Point[0], (float) Point[1],
//							(float) Point[2]), text);
//			mInfoOverlay.addInfo(data);

			// Get the Orientation of the rigidbody as a bullet Quaternion
			// Convert it to an Ogre quaternion
			btQuaternion btq = body->getOrientation();
			Ogre::Quaternion quart = Ogre::Quaternion(btq.w(), btq.x(), btq.y(),
					btq.z());
		}
	}
}

//TODO: Use for creature evolution, but clean up afterwards
void SimulationManager::updateEvolution() {
//
//	//
//	// maximization task
//	//
//	int i = 0;
//	parents.setMaximize();
//	offsprings.setMaximize();
//
//	//
//	// initialize all chromosomes of parent population
//	//
//	for (i = 0; i < parents.size(); ++i)
//		parents[i][0].initialize();
//
//	//
//	// evaluate parents (only needed for elitist strategy)
//	//
//	if (EvolutionConfiguration::EVOLUTION_SELECTION_ELITISTS_QTY > 0)
//		for (i = 0; i < parents.size(); ++i) {
//			jury.setEvaluationSubject(parents[i][0]);
//			jury.evaluateFitness();
//			parents[i].setFitness(jury.getFitness());
//		}
//
//	//
//	// recombine by crossing over two parents
//	//
//	offsprings = parents;
//	for (i = 0; i < offsprings.size() - 1; i += 2)
//		if (Rng::coinToss(EvolutionConfiguration::CrossProb))
//			offsprings[i][0].crossover(offsprings[i + 1][0],
//					EvolutionConfiguration::CrossPoints);
//	//
//	// mutate by flipping bits
//	//
//	for (i = 0; i < offsprings.size(); ++i)
//		offsprings[i][0].flip(EvolutionConfiguration::FlipProb);
//	//
//	// evaluate objective function
//	//
//	for (i = 0; i < offsprings.size(); ++i) {
//		jury.setEvaluationSubject((offsprings[i][0]));
//		jury.evaluateFitness();
//		offsprings[i].setFitness(jury.getFitness());
//	}
//	//
//	// scale fitness values and use proportional selection
//	//
//	//offsprings.linearDynamicScaling(window, t);
//	parents.selectProportional(offsprings,
//			EvolutionConfiguration::EVOLUTION_SELECTION_ELITISTS_QTY);
//
//	t++;
//	//
//	// print out best value found so far
//	//
//	std::cout << "Generation " << t << "s best individual has fitness value "
//			<< "\t" << parents.best().fitnessValue() << std::endl;

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

				if (mTerrain->mEnvironmentType == Environment::HILLS) {
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
	mStateHandler.requestStateChange(SHUTDOWN);
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

	Ogre::RenderTarget* renderTarget = mRoot->getRenderTarget(
			ApplicationConfiguration::APPLICATION_TITLE);

// CEGUI
// with a scene manager and window, we can create a the GUI renderer

// new way to instantiate a CEGUIOgreRenderer (Ogre 1.9)
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem(*renderTarget);

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

// hide the CEGUI mouse cursor (defined in the look-n-feel)
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
	menu->setAlwaysOnTop(true);
	mLayout->addChild(menu);

	setFpsPanel(ceguiBuilder.createFpsPanel());
	mLayout->addChild(getFpsPanel()->getWidgetPanel());
	setDetailsPanel(ceguiBuilder.createDetailsPanel());
	mLayout->addChild(getDetailsPanel()->getWidgetPanel());

	mGraphWindows.push_back(
			new MathGLWindow(this, 400, 400,
					CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.2f, 0)),
					CEGUI::USize(CEGUI::UDim(0.8f, 0), CEGUI::UDim(0.8f, 0))));

	std::vector<MathGLWindow*>::iterator it = mGraphWindows.begin();
	for (; it != mGraphWindows.end(); it++) {
		mLayout->addChild((*it)->getMathGlWindow());
	}

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	mSystem->getDefaultGUIContext().setRootWindow(mLayout);

// ###################
// We create a test scene for testing SDL and bullet
// ###################
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Creating test environment for basic setups...";
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);

	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(
			Ogre::RSC_INFINITE_FAR_PLANE)) {
		mCamera->setFarClipDistance(0); // enable infinite far clip distance if we can
	}

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

	switch (EnvironmentConfiguration::ENVIRONMENT_TYPE) {
	case Environment::HILLS: {
		mTerrain = new Hills();
		((Hills*) mTerrain)->initialize(this, light);
		break;
	}
	case Environment::PLANE: {
		mTerrain = new Plane();
		((Plane*) mTerrain)->initialize(this, light);
		break;
	}
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

	mInfoOverlay.initialize(mCamera);
}

//Adjust mouse clipping area
void SimulationManager::windowResized(Ogre::RenderWindow* rw) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Repositioning CEGUI pointer...";
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	int x,y;
	SDL_GetMouseState(&x,&y);

	// Align CEGUI mouse with SDL2 mouse
	CEGUI::Vector2f mousePos =
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
			x - mousePos.d_x, y- mousePos.d_y);
	int w, h;
	SDL_GetWindowSize(mSdlWindow, &w, &h);
#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX
	mWindow->resize(w, h);
#else
	mWindow->windowMovedOrResized();
#endif

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Notifying CEGUI of resize....";
	mSystem->notifyDisplaySizeChanged(CEGUI::Size<float>(width,height));
}

void SimulationManager::windowFocusChange(Ogre::RenderWindow* rw) {
	if (rw->isVisible()) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Window has gained focus...";

		// Align CEGUI mouse with SDL mouse
		CEGUI::Vector2f mousePos =
		mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
				mInputHandler.getMousePositionX() - mousePos.d_x, mInputHandler.getMousePositionY() - mousePos.d_y);
	}
	else
	{
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Window has lost focus...";
	}
}

CEGUI::System*& SimulationManager::getCEGUISystem() {
	return mSystem;
}

bool SimulationManager::configure(void) {

	mInputHandler.initialize(&mStateHandler, this);

	if (SDL_Init( SDL_INIT_EVERYTHING) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
				"Cannot initialize SDL2!", "GraphicsSystem::initialize");
	}

	// Show the configuration dialog and initialize the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if (!mRoot->restoreConfig()) {
		if (!mRoot->showConfigDialog()) {
			mStateHandler.requestStateChange(SHUTDOWN);
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

	//parse numbers
	char* end;
	int width = strtol(elems.at(0).c_str(), &end, 10);
	int height = strtol(elems.at(1).c_str(), &end, 10);

	int screen = 0;
	int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
	int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

	bool fullscreen = (cfgOpts[OgreConf::FULL_SCREEN].currentValue
			== OgreConf::YES);
	if (fullscreen) {
		posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
		posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
	}

	mSdlWindow = SDL_CreateWindow(
			ApplicationConfiguration::APPLICATION_TITLE.c_str(), // window title
			posX,               // initial x position
			posY,               // initial y position
			width,              // width, in pixels
			height,             // height, in pixels
			SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0)
					| SDL_WINDOW_RESIZABLE);

	//Get the native whnd
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
	// Windows code
	winHandle = Ogre::StringConverter::toString( (unsigned long)wmInfo.info.win.window );
	break;
#elif __MACOSX__
	case SDL_SYSWM_COCOA:
	//required to make OGRE play nice with our window
	params.insert( std::make_pair("macAPI", "cocoa") );
	params.insert( std::make_pair("macAPICocoaUseNSView", "true") );

	winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
	break;
#else
	case SDL_SYSWM_X11:
		winHandle = Ogre::StringConverter::toString(
				(unsigned long) wmInfo.info.x11.window);
		break;
#endif
	default:
		OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED,
				"Unexpected WM! (SDL2)", "GraphicsSystem::initialize");
		break;
	}

	params.insert(
			std::make_pair("title",
					ApplicationConfiguration::APPLICATION_TITLE));
	params.insert(std::make_pair("gamma", "true"));
	params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
	params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	params.insert( std::make_pair("externalWindowHandle", winHandle) );
#else
	params.insert(std::make_pair("parentWindowHandle", winHandle));
#endif

	mWindow = Ogre::Root::getSingleton().createRenderWindow(
			ApplicationConfiguration::APPLICATION_TITLE, width, height,
			fullscreen, &params);
	return true;
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
