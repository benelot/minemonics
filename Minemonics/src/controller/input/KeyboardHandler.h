/*
 * KeyboardHandler.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef KEYBOARDHANDLER_H_
#define KEYBOARDHANDLER_H_

class SimulationManager;
#include <OISKeyboard.h>

class KeyboardHandler {
private:
	SimulationManager* mSimulationMgr;

public:
	KeyboardHandler(SimulationManager* simulationMgr);
	virtual ~KeyboardHandler();

	// OIS::KeyListener
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
};

#endif /* KEYBOARDHANDLER_H_ */
