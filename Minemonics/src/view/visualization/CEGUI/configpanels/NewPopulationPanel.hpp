#ifndef VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_NEWPOPULATIONPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_NEWPOPULATIONPANEL_HPP_

//# corresponding header
#include <view/visualization/CEGUI/MovablePanel.hpp>

//# forward declarations
class BoxSlider;
#pragma once
namespace CEGUI {
class Window;
class Combobox;
class PushButton;
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
class NewPopulationPanel: public MovablePanel {
public:
	NewPopulationPanel(const int left, const int top, const std::string name);
	~NewPopulationPanel(void);

	void onConfirmClicked();

protected:
	// labels
	CEGUI::Window* mPopulationSizeLabel;

	//configuration elements
	BoxSlider* mPopulationSizeBs;
	CEGUI::PushButton* mConfirmButton;
};

#endif /* VIEW_VISUALIZATION_CEGUI_CONFIGPANELS_NEWPOPULATIONPANEL_HPP_ */
