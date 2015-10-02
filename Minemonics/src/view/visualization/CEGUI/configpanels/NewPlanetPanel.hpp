#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_NewPlanetPanel_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_NewPlanetPanel_HPP_

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
 * @brief		A panel to configure a new planet with.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class NewPlanetPanel: public MovablePanel {
public:
	NewPlanetPanel(const int left, const int top, const std::string name);
	~NewPlanetPanel(void);

	void onValueChanged();
	void onConfirmClicked();

protected:
	// labels
	CEGUI::Window* mPhysicsControllerTypeLabel;
	CEGUI::Window* mEnvironmentTypeLabel;
	CEGUI::Window* mEvaluationTimeLabel;
	CEGUI::Window* mEvaluationTypeLabel;
	CEGUI::Window* mTournamentSizeLabel;

	//configuration elements
	CEGUI::Combobox* mPhysicsControllerTypeCb;
	CEGUI::Combobox* mEnvironmentTypeCb;
	BoxSlider* mEvaluationTimeBs;
	CEGUI::Combobox* mEvaluationTypeCb;
	BoxSlider* mTournamentSizeBs;
	CEGUI::PushButton* mConfirmButton;
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_CONFIGPANELS_NewPlanetPanel_HPP_ */
