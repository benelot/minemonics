#ifndef VIEW_VISUALIZATION_CEGUI_ELEMENTS_MOVABLEPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_ELEMENTS_MOVABLEPANEL_HPP_

//# corresponding header
#include <view/visualization/CEGUI/elements/BasePanel.hpp>

//# forward declarations
#pragma once
namespace CEGUI {
class FrameWindow;
class Window;
} /* namespace CEGUI */

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <CEGUI/Size.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		A baseclass panel for movable panels.
 * @details		Details
 * @date		2015-08-28
 * @author		Benjamin Ellenberger
 */
class MovablePanel: public BasePanel {
public:
	enum MovablePanelType {
		GRAPHPANEL, FPSPANEL, DETAILSPANEL
	};
	MovablePanel(const std::string name, MovablePanelType type);

	void initialize(const int left, const int top, const int width,
	const int height, const bool hasTitleBar);

	~MovablePanel(void);

	void update(); /**!< Updates the movable panel. */

	void showTitleBar(); /**!< Show the title bar. */

	void hideTitleBar(); /**!< Hide the title bar. */

	MovablePanelType getType() const {
		return mType;
	}

	//Accessor methods

private:
	CEGUI::USize mSizeWithToolbar;
	CEGUI::USize mSizeWithoutToolbar;
	MovablePanelType mType;
};

#endif /* VIEW_VISUALIZATION_CEGUI_ELEMENTS_MOVABLEPANEL_HPP_ */
