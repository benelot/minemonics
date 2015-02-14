/*
 * KeyboardHandler.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "KeyboardHandler.h"
#include "SimulationManager.h"

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
		mSimulationMgr->getCameraHandler().move(0,0,-1);
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		mSimulationMgr->getCameraHandler().move(0,0,1);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		mSimulationMgr->getCameraHandler().move(-1,0,0);
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mSimulationMgr->getCameraHandler().move(1,0,0);
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
		mSimulationMgr->getCameraHandler().move(0,-1,0);
		break;

	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mSimulationMgr->getCameraHandler().move(0,1,0);
		break;

	case OIS::KC_ESCAPE:
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
		mSimulationMgr->getCameraHandler().move(0,0,0);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		mSimulationMgr->getCameraHandler().move(0,0,0);
		break;

	case OIS::KC_PGDOWN:
	case OIS::KC_E:
	case OIS::KC_PGUP:
	case OIS::KC_Q:
		mSimulationMgr->getCameraHandler().move(0,0,0);
		break;

	default:
		break;
	}
	return true;
}

