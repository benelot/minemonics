/*
 * OgreInputHandler.h
 *
 *  Created on: Feb 27, 2015
 *      Author: leviathan
 */

#ifndef OGREINPUTHANDLER_H_
#define OGREINPUTHANDLER_H_

#include <stdio.h>
#include <stdlib.h>

#include <utils/logging/Logger.h>

#include "ApplicationMousecode.h"
#include "ApplicationKeycode.h"

class SimulationManager;


class OgreInputHandler {
public:
	OgreInputHandler();
	virtual ~OgreInputHandler();
	void initialize(SimulationManager* simulationMgr);
	bool keyPressed(ApplicationKeycode::Keycode key);
	bool keyReleased(ApplicationKeycode::Keycode key);
	bool mouseMoved(float x,float y);
	bool mouseWheelMoved(float rel);
	bool mousePressed(ApplicationMouseCode::MouseButton button);
	bool mouseReleased(ApplicationMouseCode::MouseButton button);

	void stopCameraXDimensionMovement();

	void stopCameraYDimensionMovement();

	void stopCameraZDimensionMovement();

	void moveCameraLeft();

	void moveCameraUp();

	void moveCameraBackward();

	void moveCameraRight();

	void moveCameraDown();

	void moveCameraForward();

	void quitApplication();

private:
	// Logger
	static BoostLogger mBoostLogger;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"OgreInputHandler"));
		}
	} _initializer;

	bool mRightMousePressed;

protected:
	SimulationManager* mSimulationMgr;
};

#endif /* SDL2INPUTHANDLER_H_ */
