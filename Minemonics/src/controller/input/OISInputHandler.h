/*
 * KeyboardHandler.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef OISINPUTHANDLER_H_
#define OISINPUTHANDLER_H_

class SimulationManager;

namespace OIS {
	class KeyEvent;
	class MouseEvent;
}

#include <utils/logging/Logger.h>

class OISInputHandler: public OIS::KeyListener, public OIS::MouseListener {
public:
	OISInputHandler(SimulationManager* simulationMgr);
	virtual ~OISInputHandler();

	void capture();

	// OIS::KeyListener
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);

	// OIS::MouseListener
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
protected:
	SimulationManager* mSimulationMgr;

    OIS::InputManager* mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;

	// Static logger
	static BoostLogger logger;
};


#endif /* OISINPUTHANDLER_H_ */
