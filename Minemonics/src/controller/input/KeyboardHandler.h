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
#include <utils/logging/Logger.h>

class KeyboardHandler {
private:
	SimulationManager* mSimulationMgr;

	// Static logger
	static BoostLogger logger;

	static class _Init {
	public:
		_Init() {
			logger.add_attribute("ClassName",boost::log::attributes::constant < std::string > ("KeyboardHandler"));
		}
	} _initializer;

public:
	KeyboardHandler(SimulationManager* simulationMgr);
	virtual ~KeyboardHandler();

	// OIS::KeyListener
	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
};

#endif /* KEYBOARDHANDLER_H_ */
