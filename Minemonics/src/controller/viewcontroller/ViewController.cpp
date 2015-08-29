//# corresponding headers
#include <controller/viewcontroller/ViewController.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <iterator>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/FontManager.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/Logger.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/NamedXMLResourceManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/System.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>
#include <OgreRenderTarget.h>
#include <Renderer.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
#include <view/visualization/CEGUI/elements/infopanels/graphpanels/MathGLPanel.hpp>
#include <view/visualization/CEGUI/elements/ShowCasePanel.hpp>
#include <view/visualization/CEGUI/elements/configpanels/NewPopulationPanel.hpp>

//## utils headers

BoostLogger ViewController::mBoostLogger; /*<! initialize the boost logger*/
ViewController::_Init ViewController::_initializer;
ViewController::ViewController() :
	mRenderer(NULL), mLayout(NULL), mSystem(NULL), mDragContainer(NULL), mEvaluationInView(
		NULL), mShowShadows(false), mSelectedPlanet(NULL), mMenuBar(NULL), mFpsPanel(
		NULL), mDetailsPanel(NULL) {
}

ViewController::~ViewController() {
	mLayout = NULL;

	mSystem = NULL;

	mEvaluationInView = NULL;

	mPlanetsInView.clear();

	mSelectedPlanet = NULL;

	mRenderer = NULL;

	delete mDragContainer;
	mDragContainer = NULL;

	delete mMenuBar;
	mMenuBar = NULL;

	delete mFpsPanel;
	mFpsPanel = NULL;

	delete mDetailsPanel;
	mDetailsPanel = NULL;
}

void ViewController::initialize(Ogre::RenderTarget* const renderTarget,
	StateHandler* const stateHandler) {

	mCameraHandler.initialize();

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
		CEGUIConfiguration::CEGUI_SCHEME + ".scheme", (CEGUI::utf8*) "GUI");

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

	// add menu
	mMenuBar = new MenuBar();
	mLayout->addChild(mMenuBar->getWindow());

	// store window width and height
	int windowWidth =
		(int) SimulationManager::getSingleton()->getWindow()->getWidth();
	int windowHeight =
		(int) SimulationManager::getSingleton()->getWindow()->getHeight();

	// add fps panel
	mFpsPanel = new FPSPanel(CEGUIConfiguration::INFOPANEL_BORDER,
		(int) windowHeight * 4.0f / 5.0f);
	mMovablePanels.push_back(mFpsPanel);

	// add details panel
	mDetailsPanel = new DetailsPanel(
		(int) windowWidth - 200 - 3 * CEGUIConfiguration::INFOPANEL_BORDER,
		(int) windowHeight / 6.0f);
	mDetailsPanel->hide();
	mMovablePanels.push_back(mDetailsPanel);

	// TODO: Add graphwindows again when used
//	mMovablePanels.push_back(
//	new MathGLPanel(400, 400, 400, 400, this,
//	SimulationManager::getSingleton()->getRoot(), 400, 400));

//	mMovablePanels.push_back(
//		new ShowCasePanel(0, 30, "ShowcasePanel", 1800, 1000));

	mMovablePanels.push_back(
		new NewPopulationPanel(40, 50, "New Population", 400, 300));

	// add all movable panels to the layout
	std::vector<MovablePanel*>::const_iterator it = mMovablePanels.begin();
	for (; it != mMovablePanels.end(); it++) {
		mLayout->addChild((*it)->getWindow());
	}

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	mSystem->getDefaultGUIContext().setRootWindow(mLayout);

	// make an instance of our GUI sheet handler class
	mGUISheetHandler.initialize(SimulationManager::getSingleton(), mSystem,
		mLayout, stateHandler);

	mInfoOverlay.initialize(mCameraHandler.getCamera());

	// TODO: Add light to the camera like a head light of a miner #134.
//	Ogre::Light* light = simulationManager->getSceneManager()->createLight(
//			"headLight");
//	light->setType(Ogre::Light::LT_DIRECTIONAL);
//	light->setPosition(simulationManager->getCamera()->getPosition());
//	light->setDirection(simulationManager->getCamera()->getDirection());
//	light->setDiffuseColour(Ogre::ColourValue::White);
//	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
//	simulationManager->getCameraHandler().getCamNode()->attachObject(light);

}

void ViewController::update(const double timeSinceLastFrame) {

	// update the information overlay
	mInfoOverlay.update();

	// reposition the camera
	mCameraHandler.reposition(timeSinceLastFrame);

}

void ViewController::notifyDisplaySizeChanged(const float width,
	const float height) {
	mSystem->notifyDisplaySizeChanged(CEGUI::Size<float>(width, height));
}

void ViewController::updateMousePosition(const float mousePositionX,
	const float mousePositionY) {
	CEGUI::Vector2f mousePos =
		mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		mousePositionX - mousePos.d_x, mousePositionY - mousePos.d_y);
}

void ViewController::addPlanetToView(Planet* const planet) {
	mPlanetsInView.push_back(planet);
}

void ViewController::removePlanetFromView(Planet* const planet) {
	for (std::vector<Planet*>::iterator pit = mPlanetsInView.begin();
		pit != mPlanetsInView.end(); pit++) {
		if ((*pit) == planet) {
			mPlanetsInView.erase(pit);
			break;
		}
	}
}
