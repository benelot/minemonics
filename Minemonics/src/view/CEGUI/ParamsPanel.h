#pragma once
//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

class ParamsPanel {
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

	ParamsPanel(int left, int top, std::string name, int width,
			VectorStringPairs items);
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

	static ParamsPanel* createParamsPanel(int left, int top, std::string name,
			int width, VectorStringPairs items);
	static void destroyParamsPanel(ParamsPanel* panel);
	CEGUI::FrameWindow*& getWidgetPanel();
};
