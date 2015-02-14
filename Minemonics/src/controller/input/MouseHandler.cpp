/*
 * MouseHandler.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#include "MouseHandler.h"
#include <OgreLogManager.h>
#include "SimulationManager.h"

MouseHandler::MouseHandler(SimulationManager* simulationMgr):mSimulationMgr(simulationMgr) {

}

MouseHandler::~MouseHandler() {
	// TODO Auto-generated destructor stub
}

// OIS::MouseListener
bool MouseHandler::mouseMoved(const OIS::MouseEvent &arg) {
	if (arg.state.buttonDown(OIS::MB_Right)) {
		mSimulationMgr->getCameraHandler().rotate(arg.state.Y.rel,arg.state.X.rel,0);
	}
	return true;
}
bool MouseHandler::mousePressed(const OIS::MouseEvent &arg,
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
bool MouseHandler::mouseReleased(const OIS::MouseEvent &arg,
		OIS::MouseButtonID id) {
	return true;
}

