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

#include "OgreInputHandler.h"

#include <utils/logging/Logger.h>

#include "controller/input/ApplicationKeycode.h"
#include "controller/input/ApplicationMousecode.h"

class CEGUIInputHandler: public OgreInputHandler {
private:
	StateHandler *mStateHandler;

	// Logger
	static BoostLogger mBoostLogger;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"CEGUIInputHandler"));
		}
	} _initializer;

	double mCEGUIlastTick;
public:
	CEGUIInputHandler();
	virtual ~CEGUIInputHandler();
	void initialize(StateHandler* stateHandler,
			SimulationManager* simulationMgr);
	// CEGUI::KeyListener
	bool keyPressed(ApplicationKeycode::Keycode key);
	bool keyReleased(ApplicationKeycode::Keycode key);
	void injectTimeImpulse(double tick);

	// CEGUI::MouseListener
	bool mouseMoved(float x,float y);
	bool mouseWheelMoved(float rel);
	bool mousePressed(ApplicationMouseCode::MouseButton button);
	bool mouseReleased(ApplicationMouseCode::MouseButton button);
	void windowResized(int width,int height);
	static CEGUI::MouseButton convertMouseOgretoCEGUI(
			ApplicationMouseCode::MouseButton button);
	static CEGUI::Key::Scan convertKeyOgretoCEGUI(ApplicationKeycode::Keycode key);
	void initializeKeyMap();

protected:
	void injectMousePosition(float x,float y);
};

#endif /* CEGUIINPUTHANDLER_H_ */
