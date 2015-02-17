#include "GUISheetHandler.h"
#include "controller/StateHandler.h"
#include "CEGUI/System.h"
#include "CEGUI/Window.h"
#include "CEGUI/WindowManager.h"
#include "CEGUI/widgets/PushButton.h"

GUISheetHandler::GUISheetHandler(CEGUI::System* system, CEGUI::Window* sheet, StateHandler* stateHandler)
{
	mSystem = system;
	mWindow = sheet;
	mStateHandler = stateHandler;

	// hook up the event handlers to the window elements
	CEGUI::PushButton* pLaunchButton = (CEGUI::PushButton *)mWindow->getChildRecursive("cmdInstantAction");
	pLaunchButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUISheetHandler::launchButtonClicked, this));

	CEGUI::PushButton* pOptionsButton = (CEGUI::PushButton *)mWindow->getChildRecursive("cmdOptions");
	pOptionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUISheetHandler::optionsButtonClicked, this));

	CEGUI::PushButton* pQuitButton = (CEGUI::PushButton *)mWindow->getChildRecursive("cmdQuit");
	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked, this));

}

GUISheetHandler::~GUISheetHandler()
{
}

bool GUISheetHandler::launchButtonClicked(const CEGUI::EventArgs &args)
{
	mStateHandler->requestStateChange(SIMULATION);
	return true;
}

bool GUISheetHandler::optionsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

bool GUISheetHandler::quitButtonClicked(const CEGUI::EventArgs &args)
{
	mStateHandler->requestStateChange(SHUTDOWN);
	return true;
}
