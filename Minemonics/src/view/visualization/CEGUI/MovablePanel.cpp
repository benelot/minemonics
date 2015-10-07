//# corresponding header
#include <view/visualization/CEGUI/MovablePanel.hpp>

//# system headers
//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Event.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/String.h>
#include <CEGUI/SubscriberSlot.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/widgets/GroupBox.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

MovablePanel::MovablePanel(const std::string name, MovablePanelType type) :
	BasePanel(name), mType(type), mBaseWidget(NULL) {
}

void MovablePanel::initialize(const int left, const int top, const int width,
	const int height, const bool hasTitleBar) {
	BasePanel::initialize(left, top, width, height, hasTitleBar);
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	mBaseWidget = static_cast<CEGUI::GroupBox*>(wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/GroupBox", mName + "_Panel"));
	mBaseWidget->setText(mName);
	mBaseWidget->setSize(
		CEGUI::USize(CEGUI::UDim(0, width), CEGUI::UDim(0, height)));
	mFrameWindow->addChild(mBaseWidget);

	mFrameWindow->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
		CEGUI::Event::Subscriber(&MovablePanel::close, this));

	mSizeWithoutToolbar = CEGUI::USize(
		CEGUI::UDim(0, width + 2 * CEGUIConfiguration::INFOPANEL_BORDER),
		CEGUI::UDim(0, height + 2 * CEGUIConfiguration::INFOPANEL_BORDER));

	mSizeWithToolbar = CEGUI::USize(
		CEGUI::UDim(0, width + 2 * CEGUIConfiguration::INFOPANEL_BORDER),
		CEGUI::UDim(0,
			2 * CEGUIConfiguration::INFOPANEL_CAPTION + height
				+ 2 * CEGUIConfiguration::INFOPANEL_BORDER));

	if (hasTitleBar) {
		mFrameWindow->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0, left), CEGUI::UDim(0, top)));
		// set widget size
		mFrameWindow->setSize(mSizeWithToolbar);
		showTitleBar();
	} else {
		mFrameWindow->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0, left), CEGUI::UDim(0, top)));
		// set widget size
		mFrameWindow->setSize(mSizeWithoutToolbar);
		hideTitleBar();
	}
}

MovablePanel::~MovablePanel(void) {
	delete ((CEGUI::FrameWindow*)mFrameWindow);
	mFrameWindow = NULL;
}

void MovablePanel::update() {

}

void MovablePanel::showTitleBar() {
	mBaseWidget->setText("");
	mFrameWindow->setSizingEnabled(true);
	mFrameWindow->setTitleBarEnabled(true);
	mFrameWindow->setSize(mSizeWithToolbar);
	mFrameWindow->notifyScreenAreaChanged(true);
}

void MovablePanel::hideTitleBar() {
	mBaseWidget->setText(mName);
	mFrameWindow->setSizingEnabled(false);
	mFrameWindow->setTitleBarEnabled(false);
	mFrameWindow->setSize(mSizeWithoutToolbar);
	mFrameWindow->notifyScreenAreaChanged(true);
}

void MovablePanel::close() {
	hide();
}
