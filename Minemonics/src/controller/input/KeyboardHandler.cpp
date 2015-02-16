/*
 * KeyboardHandler.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "KeyboardHandler.h"
#include "SimulationManager.h"

BoostLogger KeyboardHandler::logger;                     // initialize the static variables
KeyboardHandler::_Init KeyboardHandler::_initializer;

KeyboardHandler::KeyboardHandler(SimulationManager* simulationMgr):mSimulationMgr(simulationMgr) {

}

KeyboardHandler::~KeyboardHandler() {
	// TODO Auto-generated destructor stub
}

//-------------------------------------------------------------------------------------
bool KeyboardHandler::keyPressed(const OIS::KeyEvent &arg) {
	switch (arg.key) {
	case OIS::KC_UP:
	case OIS::KC_W:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move forward!";
		mSimulationMgr->getCameraHandler().moveZ(-1);
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move backward!";
		mSimulationMgr->getCameraHandler().moveZ(1);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move left!";
		mSimulationMgr->getCameraHandler().moveX(-1);
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move right!";
		mSimulationMgr->getCameraHandler().moveX(1);
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move down!";
		mSimulationMgr->getCameraHandler().moveY(-1);
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Camera move up!";
		mSimulationMgr->getCameraHandler().moveY(1);
		break;

	case OIS::KC_ESCAPE:
		BOOST_LOG_SEV(logger, boost::log::trivial::info) << "Key::Shutdown application!";
		mSimulationMgr->enableShutdown();
		break;
	default:
		break;
	}
	return true;
}
//-------------------------------------------------------------------------------------
bool KeyboardHandler::keyReleased(const OIS::KeyEvent &arg) {
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

