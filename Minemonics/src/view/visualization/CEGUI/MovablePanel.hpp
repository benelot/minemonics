#ifndef VIEW_VISUALIZATION_CEGUI_MOVABLEPANEL_HPP_
#define VIEW_VISUALIZATION_CEGUI_MOVABLEPANEL_HPP_

//# corresponding header
#include <view/visualization/CEGUI/BasePanel.hpp>

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
		GRAPHPANEL,
		FPSPANEL,
		DETAILSPANEL,
		NEW_POPULATION_PANEL,
		NEW_PLANET_PANEL,
		EDIT_PLANET_PANEL,
		EDIT_POPULATION_PANEL,
		SAVE_PANEL,
		LOAD_PANEL
	};
	MovablePanel(const std::string name, MovablePanelType type);

	void initialize(const int left, const int top, const int width,
		const int height, const bool hasTitleBar);

	virtual ~MovablePanel(void);

	void update(); /**!< Updates the movable panel. */

	virtual void showTitleBar(); /**!< Show the title bar. */

	virtual void hideTitleBar(); /**!< Hide the title bar. */

	virtual void close(); /**!< Closes the window. */

	MovablePanelType getType() const {
		return mType;
	}

	//Accessor methods
protected:
	CEGUI::Window* mBaseWidget;

private:
	CEGUI::USize mSizeWithToolbar;
	CEGUI::USize mSizeWithoutToolbar;
	MovablePanelType mType;
};

#endif /* VIEW_VISUALIZATION_CEGUI_MOVABLEPANEL_HPP_ */
