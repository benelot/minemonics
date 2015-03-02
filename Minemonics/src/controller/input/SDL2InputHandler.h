/*
 * SDL2InputHandler.h
 *
 *  Created on: Feb 27, 2015
 *      Author: leviathan
 */

#ifndef SDL2INPUTHANDLER_H_
#define SDL2INPUTHANDLER_H_

#include "CEGUIInputHandler.h"

#include "ApplicationMousecode.h"
#include "ApplicationKeycode.h"

#include <utils/logging/Logger.h>

#include <SDL.h>

class SDL2InputHandler: public CEGUIInputHandler  {
public:
	SDL2InputHandler();
	virtual ~SDL2InputHandler();
	void initialize(StateHandler* stateHandler, SimulationManager* simulationMgr);
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

	int mouseX;
	int mouseY;

	ApplicationMouseCode::MouseButton convertMouseSDL2toOgre(Uint8 button);
	ApplicationKeycode::Keycode convertKeySDL2toOgre(SDL_Keycode key);
};

#endif /* SDL2INPUTHANDLER_H_ */
