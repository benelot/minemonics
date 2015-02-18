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
private:
	// Logger
	static BoostLogger mBoostLogger;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"OISInputHandler"));
		}
	} _initializer;
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

	// Accessor methods
	OIS::Keyboard*& getKeyboard();
	OIS::Mouse*& getMouse();

protected:
	SimulationManager* mSimulationMgr;

	OIS::InputManager* mInputManager;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;
};

#endif /* OISINPUTHANDLER_H_ */
