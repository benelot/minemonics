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

	//File->Quit
	CEGUI::PushButton* pQuitButton = (CEGUI::PushButton *)mWindow->getChildRecursive("cmdQuitApplication");
	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked, this));


}

GUISheetHandler::~GUISheetHandler()
{
}

//File->Quit
bool GUISheetHandler::quitButtonClicked(const CEGUI::EventArgs &args)
{
	mStateHandler->requestStateChange(SHUTDOWN);
	return true;
}

//Evolution->New Evolution
bool GUISheetHandler::newEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Evolution->Open Evolution
bool GUISheetHandler::openEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Evolution->Save Evolution as...
bool GUISheetHandler::saveEvolutionAsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Close Evolution
bool GUISheetHandler::closeEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Run Evolution
bool GUISheetHandler::runEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Pause Evolution
bool GUISheetHandler::pauseEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Stop Evolution
bool GUISheetHandler::stopEvolutionButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Browse History
bool GUISheetHandler::browseHistoryButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Environment->Hills...
bool GUISheetHandler::hillsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Environment->Open Sea
bool GUISheetHandler::openSeaButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Environment->Plane
bool GUISheetHandler::planeButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Population->New Population
bool GUISheetHandler::newPopulationButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Population->Save Population as...
bool GUISheetHandler::savePopulationAsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Population->Close Population
bool GUISheetHandler::closePopulationButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Creature->New Random Creature
bool GUISheetHandler::newCreatureButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Creature->Open Creature...
bool GUISheetHandler::openCreatureButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Creature->Save Creature as...
bool GUISheetHandler::saveCreatureAsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Creature->Close Creature
bool GUISheetHandler::closeCreatureButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Creature->Record frames
bool GUISheetHandler::recordFramesButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Spawn->Box
bool GUISheetHandler::spawnBoxButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Spawn->Sphere
bool GUISheetHandler::spawnSphereButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Spawn->Capsule
bool GUISheetHandler::spawnCapsuleButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Action->Return to Origin
bool GUISheetHandler::returnToOriginButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Population->Population Size...
bool GUISheetHandler::populationSizeButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Population->Selection Style...
bool GUISheetHandler::selectionStyleButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}


//Settings->Rendering->Shadows on/off
bool GUISheetHandler::shadowsButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Fog on/off
bool GUISheetHandler::fogButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Skybox on/off
bool GUISheetHandler::skyboxButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Greenscreen on/off
bool GUISheetHandler::greenscreenButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Status on/off
bool GUISheetHandler::statusButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Polygon mode->Solid mode
bool GUISheetHandler::solidButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Polygon mode->Wireframe mode
bool GUISheetHandler::wireframeButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->0 %
bool GUISheetHandler::ambientlight0ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->10 %
bool GUISheetHandler::ambientlight10ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->20 %
bool GUISheetHandler::ambientlight20ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->30 %
bool GUISheetHandler::ambientlight30ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->40 %
bool GUISheetHandler::ambientlight40ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->50 %
bool GUISheetHandler::ambientlight50ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->60 %
bool GUISheetHandler::ambientlight60ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->70 %
bool GUISheetHandler::ambientlight70ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->80 %
bool GUISheetHandler::ambientlight80ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->90 %
bool GUISheetHandler::ambientlight90ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Ambient light->100 %
bool GUISheetHandler::ambientlight100ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Tune for Speed
bool GUISheetHandler::tuneForSpeedButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Rendering->Tune for Quality
bool GUISheetHandler::tuneForQualityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 1
bool GUISheetHandler::speed1ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 2
bool GUISheetHandler::speed2ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 3
bool GUISheetHandler::speed3ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 4
bool GUISheetHandler::speed4ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 5
bool GUISheetHandler::speed5ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 6
bool GUISheetHandler::speed6ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 7
bool GUISheetHandler::speed7ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 8
bool GUISheetHandler::speed8ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 9
bool GUISheetHandler::speed9ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Movement->Speed 10
bool GUISheetHandler::speed10ButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Pause Simulation
bool GUISheetHandler::pauseSimulationButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->No Gravity
bool GUISheetHandler::noGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Pluto Gravity
bool GUISheetHandler::plutoGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Moon Gravity
bool GUISheetHandler::moonGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Mars/Mercury Gravity
bool GUISheetHandler::marsMercuryGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Uranus Gravity
bool GUISheetHandler::uranusGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Venus/Saturn Gravity
bool GUISheetHandler::venusSaturnGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Earth Gravity
bool GUISheetHandler::earthGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Neptune Gravity
bool GUISheetHandler::neptuneGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Jupiter Gravity
bool GUISheetHandler::jupiterGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Sun Gravity
bool GUISheetHandler::sunGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//Settings->Physics->Gravity->Custom Gravity
bool GUISheetHandler::customGravityButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}

//About->Help
bool GUISheetHandler::helpButtonClicked(const CEGUI::EventArgs &args)
{
	return true;
}
