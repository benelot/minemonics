#ifndef VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_
#define VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_

//# corresponding header
#include <view/visualization/CEGUI/MovablePanel.hpp>

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
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		A panel to display name value pairs.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class ParamsPanel: public MovablePanel {
public:
	typedef std::vector<std::string> VectorString;
	typedef std::pair<std::string, std::string> PairString;
	typedef std::vector<PairString> VectorStringPairs;

public:
	ParamsPanel(const std::string name, MovablePanelType type);
	~ParamsPanel(void);

	void initialize(const int left, const int top, const int width,
		const bool hasTitleBar, VectorStringPairs items);
	void setParamValue(const int index, const std::string value,
		const bool autoUpdate = true);
	std::string getParamValue(const int index);
	void update();
	size_t size();

protected:
	CEGUI::Window* mTextBoxLabel;
	CEGUI::Window* mTextBoxValues;
	VectorString mParams;
};

#endif /* VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_ */

