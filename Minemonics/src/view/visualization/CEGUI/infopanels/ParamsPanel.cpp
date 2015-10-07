//# corresponding header
#include <view/visualization/CEGUI/infopanels/ParamsPanel.hpp>

//# system headers
#include <stddef.h>
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

ParamsPanel::ParamsPanel(const std::string name, MovablePanelType type) :
	MovablePanel(name, type), mTextBoxLabel(NULL), mTextBoxValues(NULL) {
}

void ParamsPanel::initialize(const int left, const int top, const int width,
	const bool hasTitleBar, VectorStringPairs items) {

	int height = CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT * items.size()
		+ CEGUIConfiguration::INFOPANEL_CAPTION;
	MovablePanel::initialize(left, top, width, height, hasTitleBar);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	// Items
	// + Names
	mTextBoxLabel = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Label", mName + "_Label");

	mTextBoxLabel->setSize(
		CEGUI::USize(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_LEFT_COL_WIDTH
					* (float) (width))),
			CEGUI::UDim(0, height - CEGUIConfiguration::INFOPANEL_CAPTION)));

	mTextBoxLabel->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
	mBaseWidget->addChild(mTextBoxLabel);

	// + Values
	mTextBoxValues = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/Label", mName + "_Values");

	mTextBoxValues->setSize(
		CEGUI::USize(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_RIGHT_COL_WIDTH
					* (float) (width))),
			CEGUI::UDim(0, height - CEGUIConfiguration::INFOPANEL_CAPTION)));

	mTextBoxValues->setPosition(
		CEGUI::UVector2(
			CEGUI::UDim(0,
				(int) (CEGUIConfiguration::INFOPANEL_LEFT_COL_WIDTH
					* (float) (width))), CEGUI::UDim(0, 0)));
	mBaseWidget->addChild(mTextBoxValues);

	std::string labelText = "";
	std::string valuesText = "";
	// + Content
	for (VectorStringPairs::iterator iter = items.begin(); iter != items.end();
		++iter) {
		if (iter->first.size() > 1) {
			labelText.append(iter->first);
			labelText.append(":");
			valuesText.append(iter->second);
		}
		labelText.append("\n");
		valuesText.append("\n");
		mParams.push_back(iter->second);
	}
	mTextBoxLabel->setText(labelText);
	mTextBoxValues->setText(valuesText);
}

ParamsPanel::~ParamsPanel(void) {
	delete mTextBoxValues;
	mTextBoxValues = NULL;

	delete mTextBoxLabel;
	mTextBoxLabel = NULL;
}

void ParamsPanel::setParamValue(const int index, const std::string value,
	const bool autoUpdate) {
	if (index < 0 || index >= mParams.size())
		return;
	mParams[index] = value;
	if (autoUpdate)
		update();
}

std::string ParamsPanel::getParamValue(const int index) {
	if (index < 0 || index >= mParams.size())
		return "";
	else
		return mParams[index];
}

void ParamsPanel::update() {
	std::string valuesText = "";
	for (VectorString::iterator iter = mParams.begin(); iter != mParams.end();
		++iter) {
		valuesText.append(*iter);
		valuesText.append("\n");
	}
	mTextBoxValues->setText(valuesText);
}

size_t ParamsPanel::size() {
	return mParams.size();
}
