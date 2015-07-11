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
//## controller headers
//## model headers
//## view headers
#include <view/visualization/CEGUI/CEGUIBuilder.hpp>
#include <view/visualization/panels/ParamsPanel.hpp>

//## utils headers

BoostLogger ViewController::mBoostLogger; /*<! initialize the boost logger*/
ViewController::_Init ViewController::_initializer;
ViewController::ViewController() :
		mRenderer(NULL), mLayout(NULL), mSystem(NULL), mDetailsPanel(NULL), mFpsPanel(
		NULL), mDragContainer(NULL), mEvaluationInView(NULL) {
	// TODO Auto-generated constructor stub

}

ViewController::~ViewController() {
	// TODO Auto-generated destructor stub
}

void ViewController::initialize(SimulationManager* simulationManager,
		Ogre::RenderTarget* renderTarget, StateHandler* stateHandler) {

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

	CEGUIBuilder ceguiBuilder(simulationManager);
	CEGUI::Window* menu = ceguiBuilder.createMenu();
	menu->setAlwaysOnTop(true);
	mLayout->addChild(menu);

	mFpsPanel = ceguiBuilder.createFpsPanel();
	mLayout->addChild(getFpsPanel()->getWidgetPanel());
	mDetailsPanel = ceguiBuilder.createDetailsPanel();
	mLayout->addChild(getDetailsPanel()->getWidgetPanel());

	// TODO: Add graphwindows again when used
	//	mGraphWindows.push_back(
	//			new MathGLPanel(this, 400, 400,
	//					CEGUI::USize(CEGUI::UDim(0.2f, 0), CEGUI::UDim(0.2f, 0)),
	//					CEGUI::USize(CEGUI::UDim(0.8f, 0), CEGUI::UDim(0.8f, 0))));

	std::vector<MathGLPanel*>::iterator it = mGraphWindows.begin();
	for (; it != mGraphWindows.end(); it++) {
		mLayout->addChild((*it)->getMathGlWindow());
	}

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	mSystem->getDefaultGUIContext().setRootWindow(mLayout);

	// make an instance of our GUI sheet handler class
	mGUISheetHandler.initialize(simulationManager, mSystem, mLayout,
			stateHandler);

	mInfoOverlay.initialize(simulationManager->getCamera());

	//TODO: Add light to the camera like a head light of a miner
	//	Ogre::Light* light = mSceneMgr->createLight("tstLight");
	//	light->setType(Ogre::Light::LT_DIRECTIONAL);
	//	light->setDirection(lightdir);
	//	light->setDiffuseColour(Ogre::ColourValue::White);
	//	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

}

void ViewController::update(double timeSinceLastFrame) {

	// update the information overlay
	mInfoOverlay.update();

}

void ViewController::notifyDisplaySizeChanged(float width, float height) {
	mSystem->notifyDisplaySizeChanged(CEGUI::Size<float>(width, height));
}

void ViewController::updateMousePosition(float mousePositionX,
		float mousePositionY) {
	CEGUI::Vector2f mousePos =
			mSystem->getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
			mousePositionX - mousePos.d_x, mousePositionY - mousePos.d_y);
}

void ViewController::addPlanet(Planet* planet) {
}
