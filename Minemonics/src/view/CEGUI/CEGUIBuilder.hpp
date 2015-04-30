/*
 * CEGUIBuilder.h
 *
 *  Created on: Feb 25, 2015
 *      Author: leviathan
 */

#ifndef CEGUIBUILDER_H_
#define CEGUIBUILDER_H_

//# corresponding header
//# forward declarations
class SimulationManager;
class ParamsPanel;

namespace CEGUI {
class Window;
}

//# system headers
//## controller headers
//## model headers
//## view headers
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
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
