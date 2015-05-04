#ifndef SDL2INPUTHANDLER_H_
#define SDL2INPUTHANDLER_H_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/CEGUIInputHandler.hpp>

//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>


/**
 * @brief		The SDL2 input handler handles the input coming directly from the hardware layer SDL2 manages and hands the inputs up to its connecting input handlers.
 * @details		Details
 * @date		2015-02-27
 * @author		Benjamin Ellenberger
 */
class SDL2InputHandler: public CEGUIInputHandler {
public:
	SDL2InputHandler();
	virtual ~SDL2InputHandler();
	void initialize(StateHandler* stateHandler,
			SimulationManager* simulationMgr);
	void destroy();
	void injectInput();
	void injectTimePulse();

	int getMousePositionX();
	int getMousePositionY();

private:
	// Logger
	static BoostLogger mBoostLogger;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"SDL2InputHandler"));
		}
	} _initializer;

	int mLastMouseX;
	int mLastMouseY;
};

#endif /* SDL2INPUTHANDLER_H_ */
