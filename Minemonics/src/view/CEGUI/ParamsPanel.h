#pragma once
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#define CEGUI_INFOPANEL_CAPTION 15
#define CEGUI_INFOPANEL_TEXT 30
#define CEGUI_INFOPANEL_BORDER 10
#define CEGUI_INFOPANEL_COL1 0.5f
#define CEGUI_INFOPANEL_COL2 0.5f

class ParamsPanel
{
public:
	typedef std::vector<std::string> VectorString;
	typedef std::pair<std::string, std::string> PairString;
	typedef std::vector<PairString> VectorStringPairs;

protected:
	CEGUI::Window* mRootGui;
	CEGUI::FrameWindow* mWidgetPanel;
	CEGUI::Window* mTextBoxLabel;
	CEGUI::Window* mTextBoxValues;
	VectorString mParams;

	ParamsPanel(int left, int top, std::string name, int width, VectorStringPairs items, CEGUI::Window* myRootGui);
	void _destroy();
public:
	~ParamsPanel(void);

	void setParamValue(int index, std::string value, bool autoUpdate = true);
	std::string getParamValue(int index);
	void update();
	size_t size();
	int getWidth();
	int getHeight();
	void hide();
	void show();
	bool isVisible();

	static ParamsPanel* createParamsPanel(int left, int top, std::string name, int width, VectorStringPairs items, CEGUI::Window* myRootGui);
	static void destroyParamsPanel(ParamsPanel* panel);
};
