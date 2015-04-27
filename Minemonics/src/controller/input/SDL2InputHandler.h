/*
 * SDL2InputHandler.h
 *
 *  Created on: Feb 27, 2015
 *      Author: leviathan
 */

#ifndef SDL2INPUTHANDLER_H_
#define SDL2INPUTHANDLER_H_

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
#include <SDL.h>

//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include "ApplicationMousecode.h"
#include "ApplicationKeycode.h"
#include "CEGUIInputHandler.h"

//## model headers
//## view headers
//## utils headers
#include "utils/logging/Logger.h"

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
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

	ApplicationMouseCode::MouseButton convertMouseSDL2toOgre(Uint8 button);
	ApplicationKeycode::Keycode convertKeySDL2toOgre(SDL_Keycode key);
};

#endif /* SDL2INPUTHANDLER_H_ */
