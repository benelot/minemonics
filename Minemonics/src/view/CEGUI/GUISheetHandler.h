#pragma once

#include "CEGUI/Window.h"

namespace CEGUI
{
	class System;
	class Window;
}

class StateHandler;

class GUISheetHandler
{
public:
	GUISheetHandler(CEGUI::System* pSystem, CEGUI::Window* pSheet, StateHandler* pSimulation);
	~GUISheetHandler();

	// CEGUI event handlers. You can name these whatever you like, so long as they have the proper 
	// signature: bool <method name>(const CEGUI::EventArgs &args)
	bool quitButtonClicked(const CEGUI::EventArgs &args);
	bool optionsButtonClicked(const CEGUI::EventArgs &args);
	bool launchButtonClicked(const CEGUI::EventArgs &args);

private:
	CEGUI::System* mSystem;	// pointer to the CEGUI System instance
	CEGUI::Window* mWindow;	// pointer to the layout sheet window
	StateHandler* mStateHandler;	// pointer to the Simulation controller
};
