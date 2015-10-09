#ifndef VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_
#define VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_

//# corresponding header
#include <view/visualization/panels/InfoPanel.hpp>

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
class ParamsPanel: public InfoPanel {
public:
	typedef std::vector<std::string> VectorString;
	typedef std::pair<std::string, std::string> PairString;
	typedef std::vector<PairString> VectorStringPairs;

protected:
	ParamsPanel(const int left, const int top, const std::string name,
			const int width, VectorStringPairs items);

	void _destroy();
public:
	~ParamsPanel(void);

	void setParamValue(const int index, const std::string value,
			const bool autoUpdate = true);

	std::string getParamValue(const int index);

	void update();

	size_t size();

	int getWidth();

	int getHeight();

	void hide();

	void show();

	bool isVisible();

	static ParamsPanel* createParamsPanel(const int left, const int top,
			const std::string name, const int width,
			const VectorStringPairs items);

	static void destroyParamsPanel(ParamsPanel* panel);

	CEGUI::FrameWindow*& getWidgetPanel();

protected:
	CEGUI::Window* mRootGui;
	CEGUI::FrameWindow* mWidgetPanel;
	CEGUI::Window* mTextBoxLabel;
	CEGUI::Window* mTextBoxValues;
	VectorString mParams;
};

#endif /* VIEW_VISUALIZATION_PANELS_PARAMSPANEL_H_ */

