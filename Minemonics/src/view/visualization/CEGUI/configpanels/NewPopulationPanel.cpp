//# corresponding header
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
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>
#include <view/visualization/CEGUI/configpanels/NewPopulationPanel.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

NewPopulationPanel::NewPopulationPanel(const int left, const int top,
	const std::string name, const int width, const int height) :
	MovablePanel(name, MovablePanel::NEW_POPULATION_PANEL), mTextBoxLabel(NULL), mTextBoxValues(
		NULL) {

	MovablePanel::initialize(left, top, width, height, false);

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

	std::string labelText = "Hello";
	std::string valuesText = "World";

	mTextBoxLabel->setText(labelText);
	mTextBoxValues->setText(valuesText);
}

NewPopulationPanel::~NewPopulationPanel(void) {
}
