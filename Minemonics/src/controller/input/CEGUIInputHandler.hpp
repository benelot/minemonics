/*
 * CEGUIInputHandler.h
 *
 *  Created on: Feb 17, 2015
 *      Author: leviathan
 */

#ifndef CEGUIINPUTHANDLER_H_
#define CEGUIINPUTHANDLER_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class StateHandler;

//# system headers
//## controller headers
//## model headers
//## view headers
#include <CEGUI/CEGUI.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/ApplicationKeycode.hpp>
#include <controller/input/ApplicationMousecode.hpp>
#include <controller/input/OgreInputHandler.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
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
	bool mouseMoved(float x, float y);
	bool mouseWheelMoved(float rel);
	bool mousePressed(ApplicationMouseCode::MouseButton button);
	bool mouseReleased(ApplicationMouseCode::MouseButton button);
	void windowResized(int width, int height);
	static CEGUI::MouseButton convertMouseOgretoCEGUI(
			ApplicationMouseCode::MouseButton button);
	static CEGUI::Key::Scan convertKeyOgretoCEGUI(
			ApplicationKeycode::Keycode key);
	void initializeKeyMap();

protected:
	void injectMousePosition(float x, float y);
};

#endif /* CEGUIINPUTHANDLER_H_ */
