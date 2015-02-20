/*
 * KeyboardHandler.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include <OISKeyboard.h>
#include <OISMouse.h>

#include "OISInputHandler.h"

#include "SimulationManager.h"

BoostLogger OISInputHandler::mBoostLogger;    // initialize the static variables
OISInputHandler::_Init OISInputHandler::_initializer;
OISInputHandler::OISInputHandler(SimulationManager* simulationMgr) :
		mSimulationMgr(simulationMgr), mMouse(NULL), mKeyboard(NULL), mInputManager(
		NULL) {
}

OISInputHandler::~OISInputHandler() {
	if (mInputManager) {
		mInputManager->destroyInputObject(mMouse);
		mInputManager->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputManager);
		mInputManager = 0;
	}
}

void OISInputHandler::capture() {
	if (mInputManager) {
		//part of the workaround for keyboard grab
		mMouse->capture();
		mKeyboard->capture();
	}
}

//-------------------------------------------------------------------------------------
bool OISInputHandler::keyPressed(const OIS::KeyEvent &arg) {
	switch (arg.key) {
	case OIS::KC_UP:
	case OIS::KC_W:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move forward!";
		mSimulationMgr->getCameraHandler().moveZ(-1);
		break;

		case OIS::KC_DOWN:
		case OIS::KC_S:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Camera move backward!";
		mSimulationMgr->getCameraHandler().moveZ(1);
		break;

		case OIS::KC_LEFT:
		case OIS::KC_A:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Camera move left!";
		mSimulationMgr->getCameraHandler().moveX(-1);
		break;

		case OIS::KC_RIGHT:
		case OIS::KC_D:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Camera move right!";
		mSimulationMgr->getCameraHandler().moveX(1);
		break;

		case OIS::KC_PGDOWN:
		case OIS::KC_E:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Camera move down!";
		mSimulationMgr->getCameraHandler().moveY(-1);
		break;

		case OIS::KC_PGUP:
		case OIS::KC_Q:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Camera move up!";
		mSimulationMgr->getCameraHandler().moveY(1);
		break;

		case OIS::KC_ESCAPE:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Key::Shutdown application!";
		mSimulationMgr->getStateHandler()->requestStateChange(SHUTDOWN);
		break;
		default:
		break;
	}
	return true;
}
//-------------------------------------------------------------------------------------
bool OISInputHandler::keyReleased(const OIS::KeyEvent &arg) {
	switch (arg.key) {
	case OIS::KC_UP:
	case OIS::KC_W:
	case OIS::KC_DOWN:
	case OIS::KC_S:
		mSimulationMgr->getCameraHandler().moveZ(0);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mSimulationMgr->getCameraHandler().moveX(0);
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mSimulationMgr->getCameraHandler().moveY(0);
		break;

	default:
		break;
	}
	return true;
}

// OIS::MouseListener
bool OISInputHandler::mouseMoved(const OIS::MouseEvent &arg) {
	if (arg.state.buttonDown(OIS::MB_Right)) {
		mSimulationMgr->getCameraHandler().rotate(arg.state.Y.rel,
				arg.state.X.rel, 0);
	}
	return true;
}
bool OISInputHandler::mousePressed(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	switch (id) {
	case OIS::MB_Left:
		Ogre::LogManager::getSingleton().logMessage("Mouse left-click");
		break;
	case OIS::MB_Right:
		Ogre::LogManager::getSingleton().logMessage("Mouse right-click");
		break;
	default:
		break;
	}
	return true;
}
bool OISInputHandler::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return true;
}

OIS::Keyboard*& OISInputHandler::getKeyboard() {
	return mKeyboard;
}

OIS::Mouse*& OISInputHandler::getMouse() {
	return mMouse;
}
