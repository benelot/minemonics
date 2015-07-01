#ifndef VIEW_VISUALIZATION_CEGUI_CEGUIBUILDER_H_
#define VIEW_VISUALIZATION_CEGUI_CEGUIBUILDER_H_

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
 * @brief		The CEGUI Builder creates CEGUI panels for the GUI interface.
 * @details		Details
 * @date		2015-02-25
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

#endif /* VIEW_VISUALIZATION_CEGUI_CEGUIBUILDER_H_ */
