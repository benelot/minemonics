/*
 * MouseHandler.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef MOUSEHANDLER_H_
#define MOUSEHANDLER_H_

#include <OISMouse.h>
class SimulationManager;

class MouseHandler {
private:
	SimulationManager* mSimulationMgr;

public:
	MouseHandler(SimulationManager* simulationMgr);
	virtual ~MouseHandler();

	// OIS::MouseListener
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg,
			OIS::MouseButtonID id);
};

#endif /* MOUSEHANDLER_H_ */
