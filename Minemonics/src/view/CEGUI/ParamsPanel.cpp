//# corresponding header
#include <configuration/CEGUIConfiguration.hpp>
#include <view/CEGUI/ParamsPanel.hpp>

//# forward declarations
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

ParamsPanel::ParamsPanel(int left, int top, std::string name, int width,
		VectorStringPairs items) :
		mWidgetPanel(NULL), mTextBoxLabel(NULL), mTextBoxValues(NULL), mRootGui(
		NULL) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	// Panel
	mWidgetPanel = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow(
			"Ogremonics/Group", name + "_Panel"));
	mWidgetPanel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0, left), CEGUI::UDim(0, top)));
	mWidgetPanel->setSize(
			CEGUI::USize(CEGUI::UDim(0, width),
					CEGUI::UDim(0,
							CEGUIConfiguration::INFOPANEL_CAPTION
									+ CEGUIConfiguration::INFOPANEL_BORDER
									+ CEGUIConfiguration::INFOPANEL_TEXT
											* items.size()
									+ CEGUIConfiguration::INFOPANEL_BORDER)));
	mWidgetPanel->setText(name);

	// Items
	// + Names
	mTextBoxLabel = wmgr.createWindow("Ogremonics/Label", name + "_Label");
	mWidgetPanel->addChild(mTextBoxLabel);
	mTextBoxLabel->setPosition(
			CEGUI::UVector2(
					CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_BORDER),
					CEGUI::UDim(0, 0)));
	mTextBoxLabel->setSize(
			CEGUI::USize(
					CEGUI::UDim(0,
							(int) (CEGUIConfiguration::INFOPANEL_COL1
									* (float) (width
											- 2
													* CEGUIConfiguration::INFOPANEL_BORDER))),
					CEGUI::UDim(0,
							CEGUIConfiguration::INFOPANEL_TEXT
									* items.size())));
	std::string labelText = "";
	// + Values
	mTextBoxValues = wmgr.createWindow("Ogremonics/Label", name + "_Values");
	mWidgetPanel->addChild(mTextBoxValues);
	mTextBoxValues->setPosition(
			CEGUI::UVector2(
					CEGUI::UDim(0,
							CEGUIConfiguration::INFOPANEL_BORDER
									+ (int) (CEGUIConfiguration::INFOPANEL_COL1
											* (float) (width
													- 2
															* CEGUIConfiguration::INFOPANEL_BORDER))),
					CEGUI::UDim(0, 0)));
	mTextBoxValues->setSize(
			CEGUI::USize(
					CEGUI::UDim(0,
							(int) (CEGUIConfiguration::INFOPANEL_COL2
									* (float) (width
											- 2
													* CEGUIConfiguration::INFOPANEL_BORDER))),
					CEGUI::UDim(0,
							CEGUIConfiguration::INFOPANEL_TEXT
									* items.size())));
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
	_destroy();
}

void ParamsPanel::_destroy() {
	if (mTextBoxValues != NULL && mWidgetPanel != NULL)
		mWidgetPanel->destroyChild(mTextBoxValues);
	mTextBoxValues = NULL;
	if (mTextBoxLabel != NULL && mWidgetPanel != NULL)
		mWidgetPanel->destroyChild(mTextBoxLabel);
	mTextBoxLabel = NULL;
}

void ParamsPanel::setParamValue(int index, std::string value, bool autoUpdate) {
	if (index < 0 || index >= mParams.size())
		return;
	mParams[index] = value;
	if (autoUpdate)
		update();
}

std::string ParamsPanel::getParamValue(int index) {
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

int ParamsPanel::getWidth() {
	return (mWidgetPanel != NULL) ? mWidgetPanel->getWidth().d_offset : 0;
}

int ParamsPanel::getHeight() {
	return (mWidgetPanel != NULL) ? mWidgetPanel->getHeight().d_offset : 0;
}

void ParamsPanel::hide() {
	if (mWidgetPanel != NULL)
		mWidgetPanel->setVisible(false);
}

void ParamsPanel::show() {
	if (mWidgetPanel != NULL)
		mWidgetPanel->setVisible(true);
}

bool ParamsPanel::isVisible() {
	return (mWidgetPanel != NULL) ? mWidgetPanel->isVisible() : false;
}

ParamsPanel* ParamsPanel::createParamsPanel(int left, int top, std::string name,
		int width, VectorStringPairs items) {
	ParamsPanel* ppp = new ParamsPanel(left, top, name, width, items);
	return ppp;
}

CEGUI::FrameWindow*& ParamsPanel::getWidgetPanel() {
	return mWidgetPanel;
}

void ParamsPanel::destroyParamsPanel(ParamsPanel* panel) {
	panel->_destroy();
	delete panel;
	panel = NULL;
}
