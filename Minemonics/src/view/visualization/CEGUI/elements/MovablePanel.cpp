//# corresponding header
#include <view/visualization/CEGUI/elements/MovablePanel.hpp>

//## system headers
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

//## controller headers
//## model headers
//## view headers
//## utils headers

MovablePanel::MovablePanel(const std::string name) :
BasePanel(name) {
}

void MovablePanel::initialize(const int left, const int top, const int width,
const int height, const bool hasTitleBar) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

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
	delete mFrameWindow;
	mFrameWindow = NULL;
}

void MovablePanel::update() {

}

void MovablePanel::showTitleBar() {
	mFrameWindow->setSizingEnabled(true);
	mFrameWindow->setTitleBarEnabled(true);
	mFrameWindow->setSize(mSizeWithToolbar);
	mFrameWindow->notifyScreenAreaChanged(true);
}

void MovablePanel::hideTitleBar() {
	mFrameWindow->setSizingEnabled(false);
	mFrameWindow->setTitleBarEnabled(false);
	mFrameWindow->setSize(mSizeWithoutToolbar);
	mFrameWindow->notifyScreenAreaChanged(true);
}
