#ifndef CEGUIINPUTHANDLER_H_
#define CEGUIINPUTHANDLER_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class StateHandler;

//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <CEGUI/CEGUI.h>
#include <CEGUI/InputEvent.h>

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
 * @brief		The CEGUI Input handler handles the input coming from the lower hardware input layer and handles it in the context of the CEGUI.
 * @details		Details
 * @date		2015-02-17
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

protected:
	/**
	 * Initialize the CEGUIInputHandler
	 * @param stateHandler The statehandler of the application
	 * @param simulationMgr The simulation manager of the application.
	 */
	void initialize(StateHandler* stateHandler,
			SimulationManager* simulationMgr);

	/**
	 * Inject time impulse to give the input layer a notion of time.
	 * @param tick Number of ticks that passed.
	 */
	void injectTimeImpulse(double tick);

	// CEGUI::KeyListener
	/**
	 * Is triggered if a key is pressed.
	 * @param key The key code of the key
	 * @return If the key event has been used by the handler.
	 */
	bool keyPressed(ApplicationKeycode::Keycode key);

	/**
	 * Is triggered if a key is released.
	 * @param key The key code of the key.
	 * @return If the key event has been used by the handler.
	 */
	bool keyReleased(ApplicationKeycode::Keycode key);

	// CEGUI::MouseListener

	/**
	 * Is triggered if the mouse is moved.
	 * @param x How much the mouse moved in x direction.
	 * @param y How much the mouse moved in y direction.
	 * @return If the mouse move event has been used by the handler.
	 */
	bool mouseMoved(float x, float y);

	/**
	 * Is triggered if the mouse wheel is moved.
	 * @param rel The movement of the mouse wheel.
	 * @return If the mouse wheel movement event has been used by the handler.
	 */
	bool mouseWheelMoved(float rel);

	/**
	 * Is triggered if a mouse button is pressed.
	 * @param button The mouse button code.
	 * @return If the mouse button event has been used by the handler.
	 */
	bool mousePressed(ApplicationMouseCode::MouseButton button);

	/**
	 * Is triggered if a mouse button is released.
	 * @param button The mouse button code.
	 * @return If the mouse button event has been used by the handler.
	 */
	bool mouseReleased(ApplicationMouseCode::MouseButton button);

	/**
	 * Is triggered if the window has been resized.
	 * @param width The new width of the window.
	 * @param height The new height of the window.
	 */
	void windowResized(int width, int height);

	/**
	 * Inject the mouse absolute position.
	 * @param x The absolute x position of the mouse.
	 * @param y The absolute y position of the mouse.
	 */
	void injectMousePosition(float x, float y);
};

#endif /* CEGUIINPUTHANDLER_H_ */
