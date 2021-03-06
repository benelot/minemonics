#ifndef VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_EDITPOPULATIONPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_EDITPOPULATIONPANEL_HPP_

//# corresponding header
#include <view/visualization/CEGUI/MovablePanel.hpp>

//# forward declarations
#pragma once
namespace CEGUI {
class Window;
} /* namespace CEGUI */

//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		A panel to configure a new population with.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class EditPopulationPanel: public MovablePanel {
public:
	EditPopulationPanel(const int left, const int top, const std::string name);
	virtual ~EditPopulationPanel(void);

protected:
	CEGUI::Window* mTextBoxLabel;
	CEGUI::Window* mTextBoxValues;
};

#endif /* VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_EDITPOPULATIONPANEL_HPP_ */
