/*
 * CEGUIInputHandler.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: leviathan
 */

// view
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <CEGUI/GUIContext.h>

// controller
#include <OISKeyboard.h>
#include <OISMouse.h>

// view
#include <OgreStringConverter.h>

// base
#include "SimulationManager.h"

// controller
#include "controller/input/CEGUIInputHandler.h"
#include "controller/StateHandler.h"

// logging
#include "utils/logging/Logger.h"

CEGUIInputHandler::CEGUIInputHandler(StateHandler* stateHandler,
		unsigned long hWnd, SimulationManager* simulationMgr) :
		OISInputHandler(simulationMgr) {
	pl.insert(
			OIS::ParamList::value_type("WINDOW",
					Ogre::StringConverter::toString(hWnd)));
//The mouse should never be bound to the window
#if defined OIS_WIN32_PLATFORM
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	pl.insert(
			std::make_pair(std::string("x11_mouse_grab"),
					std::string("false")));
	pl.insert(
			std::make_pair(std::string("x11_mouse_hide"),
					std::string("false")));

	//TODO: Fix keyboard grab problem
//	pl.insert(std::make_pair(std::string("x11_keyboard_grab"),std::string("false")));
	pl.insert(
			std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
#endif

	mhWnd = hWnd;

	initializeInputHandler();

	mStateHandler = stateHandler;
}

CEGUIInputHandler::~CEGUIInputHandler() {
	//OISInputHandler is called automatically
}

//-------------------------------------------------------------------------------------
bool CEGUIInputHandler::keyPressed(const OIS::KeyEvent &arg) {

	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectKeyDown((CEGUI::Key::Scan) arg.key);
	context.injectChar(arg.text);

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "RawKey::" << arg.text;

	if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
			{
		if (!mSimulationMgr->getFpsPanel()->getWidgetPanel()->isVisible()) {
			ParamsPanel::VectorStringPairs items;
			items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
			mSimulationMgr->getFpsPanel()->getWidgetPanel()->setVisible(false);
		} else {
			bool simple = mSimulationMgr->getFpsPanel()->size() == 1;
			mSimulationMgr->getFpsPanel()->getWidgetPanel()->setVisible(true);
		}
	} else if (arg.key == OIS::KC_G) // toggle visibility of even rarer debugging details
			{
		if (mSimulationMgr->getDetailsPanel()->isVisible())
			mSimulationMgr->getDetailsPanel()->hide();
		else
			mSimulationMgr->getDetailsPanel()->show();
	} else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
			{
		Ogre::String newVal;
		Ogre::TextureFilterOptions tfo;
		unsigned int aniso;

		switch (mSimulationMgr->getDetailsPanel()->getParamValue(9)[0]) {
		case 'B':
			newVal = "Trilinear";
			tfo = Ogre::TFO_TRILINEAR;
			aniso = 1;
			break;
		case 'T':
			newVal = "Anisotropic";
			tfo = Ogre::TFO_ANISOTROPIC;
			aniso = 8;
			break;
		case 'A':
			newVal = "None";
			tfo = Ogre::TFO_NONE;
			aniso = 1;
			break;
		default:
			newVal = "Bilinear";
			tfo = Ogre::TFO_BILINEAR;
			aniso = 1;
		}

		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
		mSimulationMgr->getDetailsPanel()->setParamValue(9, newVal);
	} else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
			{
		Ogre::String newVal;
		Ogre::PolygonMode pm;

		switch (mSimulationMgr->getCamera()->getPolygonMode()) {
		case Ogre::PM_SOLID:
			newVal = "Wireframe";
			pm = Ogre::PM_WIREFRAME;
			break;
		case Ogre::PM_WIREFRAME:
			newVal = "Points";
			pm = Ogre::PM_POINTS;
			break;
		default:
			newVal = "Solid";
			pm = Ogre::PM_SOLID;
		}

		mSimulationMgr->getCamera()->setPolygonMode(pm);
		mSimulationMgr->getDetailsPanel()->setParamValue(10, newVal);
	} else if (arg.key == OIS::KC_F5)   // refresh all textures
			{
		Ogre::TextureManager::getSingleton().reloadAll();
	} else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
			{
		//TODO: Find way to print screeen
		//mSimulationMgr->getLayout()->writeContentsToTimestampedFile("screenshot", ".jpg");
	} else if (arg.key == OIS::KC_ESCAPE) {
		mSimulationMgr->quit();
	}

	//hand value down to OIS
	return OISInputHandler::keyPressed(arg);
}
//-------------------------------------------------------------------------------------
bool CEGUIInputHandler::keyReleased(const OIS::KeyEvent &arg) {

	//If CEGUI used the input, then return
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
			(CEGUI::Key::Scan) arg.key))
		return true;

	//hand value down to OIS
	return OISInputHandler::keyReleased(arg);
}

void CEGUIInputHandler::initializeInputHandler() {
	if (mInputManager == NULL) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "initializing OIS input handler...";
		mInputManager = OIS::InputManager::createInputSystem(pl);
		mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(
						OIS::OISMouse, true));
		mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(
						OIS::OISKeyboard, true));
		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);
	}
}

void CEGUIInputHandler::destroyInputHandler() {

	if (mInputManager != NULL) {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "destroying OIS input handler...";
		mInputManager->destroyInputObject(mKeyboard);
		mInputManager->destroyInputObject(mMouse);
		mKeyboard = NULL;
		mMouse = NULL;

		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = NULL;
	}
}

// OIS::MouseListener
bool CEGUIInputHandler::mouseMoved(const OIS::MouseEvent &arg) {
	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();

	// Scroll wheel.
	if (arg.state.Z.rel)
		context.injectMouseWheelChange(arg.state.Z.rel / 120.0f);

	context.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);

	return OISInputHandler::mouseMoved(arg);
}
bool CEGUIInputHandler::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Mouse button " << id << " pressed";
	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();

	if (context.injectMouseButtonDown(convertButton(id)))
		return true;
	return OISInputHandler::mousePressed(arg, id);

}
bool CEGUIInputHandler::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	CEGUI::GUIContext& context =
			CEGUI::System::getSingleton().getDefaultGUIContext();
	if (context.injectMouseButtonUp(convertButton(id)))
		return true;
	return OISInputHandler::mouseReleased(arg, id);
}

CEGUI::MouseButton CEGUIInputHandler::convertButton(
		OIS::MouseButtonID buttonID) {
	switch (buttonID) {
	case OIS::MB_Left:
		return CEGUI::LeftButton;
		break;

	case OIS::MB_Right:
		return CEGUI::RightButton;
		break;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;
		break;

	default:
		return CEGUI::NoButton;
		break;
	}
	return CEGUI::NoButton;
}

