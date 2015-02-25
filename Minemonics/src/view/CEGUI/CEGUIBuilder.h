/*
 * CEGUIBuilder.h
 *
 *  Created on: Feb 25, 2015
 *      Author: leviathan
 */

#ifndef CEGUIBUILDER_H_
#define CEGUIBUILDER_H_

class SimulationManager;
class ParamsPanel;

namespace CEGUI{
class Window;
}

#include <CEGUI/WindowManager.h>

class CEGUIBuilder {
public:
	CEGUIBuilder(SimulationManager* simulationMgr);
	virtual ~CEGUIBuilder();

	CEGUI::Window * createMenu();
	ParamsPanel* createFpsPanel();
	ParamsPanel* createDetailsPanel();
private:
	SimulationManager* mSimulationMgr;
};

#endif /* CEGUIBUILDER_H_ */
