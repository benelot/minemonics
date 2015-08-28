//# corresponding header
#include <view/visualization/CEGUI/elements/BasePanel.hpp>

//## system headers
#include <stddef.h>
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

BasePanel::BasePanel(const std::string name) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	// Initialize panel
	mFrameWindow = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow(
	"Ogremonics/FrameWindow", name + "_Panel"));

	// set widget name
	mFrameWindow->setText(name);

	// set tooltip text
	mFrameWindow->setTooltipText(name);
	mName = name;
}

BasePanel::~BasePanel(void) {
	delete mFrameWindow;
	mFrameWindow = NULL;
}

void BasePanel::initialize(const int left, const int top, const int width,
const int height, bool withTitleBar) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	// set widget position
	mFrameWindow->setPosition(
	CEGUI::UVector2(CEGUI::UDim(0, left), CEGUI::UDim(0, top)));

	// set widget size
	mFrameWindow->setSize(
	CEGUI::USize(CEGUI::UDim(0, width), CEGUI::UDim(0, height)));

	mFrameWindow->setSizingEnabled(withTitleBar);
	mFrameWindow->setTitleBarEnabled(withTitleBar);
}

void BasePanel::update() {

}

void BasePanel::setPosition(const int left, const int top) {
	mFrameWindow->setPosition(
	CEGUI::UVector2(CEGUI::UDim(0, left), CEGUI::UDim(0, top)));
}

void BasePanel::hide() {
	if (mFrameWindow != NULL)
		mFrameWindow->setVisible(false);
}

void BasePanel::show() {
	if (mFrameWindow != NULL)
		mFrameWindow->setVisible(true);
}
