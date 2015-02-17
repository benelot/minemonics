/*
 * CEGUIInputHandler.h
 *
 *  Created on: Feb 17, 2015
 *      Author: leviathan
 */

#ifndef CEGUIINPUTHANDLER_H_
#define CEGUIINPUTHANDLER_H_

class SimulationManager;
class StateHandler;

#include <CEGUI/CEGUI.h>

#include "OISInputHandler.h"

class CEGUIInputHandler: public OISInputHandler {
private:
	unsigned long mhWnd;
	StateHandler *mStateHandler;
public:
	CEGUIInputHandler(StateHandler* stateHandler, unsigned long hWnd,
			SimulationManager* simulationMgr);
	virtual ~CEGUIInputHandler();
	// OIS::KeyListener
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	// OIS::MouseListener
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
	static CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
};

#endif /* CEGUIINPUTHANDLER_H_ */
