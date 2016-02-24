#pragma once
//# corresponding header
//# forward declarations
class SimulationManager;
class StateHandler;
namespace CEGUI {
class EventArgs;
class System;
class Window;
} /* namespace CEGUI */

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
#include <utils/logging/Logger.hpp>

/**
 * @brief		The GUI sheet handler picks up the inputs via the menu.
 * @details		Details
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class GUISheetHandler {
public:
	GUISheetHandler();
	~GUISheetHandler();

	void initialize(CEGUI::System* const system, CEGUI::Window* const sheet);

	// CEGUI event handlers. You can name these whatever you like, as long as they have the proper
	// signature: bool <method name>(const CEGUI::EventArgs &args)

	//#####################
	//File menu
	//File->Quit
	bool quitButtonClicked(const CEGUI::EventArgs &args);

	//#####################
	//Evaluation menu
	//Evaluation->Evolution Track
	bool evolutionTrackButtonClicked(const CEGUI::EventArgs &args);

	//Evaluation->Learning Track
	bool learningTrackButtonClicked(const CEGUI::EventArgs &args);

	//Planets->New Planet
	bool newPlanetButtonClicked(const CEGUI::EventArgs &args);

	//Planets->Edit Planet
	bool editPlanetButtonClicked(const CEGUI::EventArgs &args);

	//Planets->Load Planet
	bool loadPlanetButtonClicked(const CEGUI::EventArgs &args);

	//Evolution->New Evolution
	bool newEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Evolution->Open Evolution
	bool openEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Evolution->Save Evolution as...
	bool saveEvolutionAsButtonClicked(const CEGUI::EventArgs &args);

	//Close Evolution
	bool closeEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Run Evolution
	bool runEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Pause Evolution
	bool pauseEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Stop Evolution
	bool stopEvolutionButtonClicked(const CEGUI::EventArgs &args);

	//Browse History
	bool browseHistoryButtonClicked(const CEGUI::EventArgs &args);

	//Environment->Hills...
	bool hillsButtonClicked(const CEGUI::EventArgs &args);

	//Environment->Open Sea
	bool openSeaButtonClicked(const CEGUI::EventArgs &args);

	//Environment->Plane
	bool planeButtonClicked(const CEGUI::EventArgs &args);

	//Population->New Population
	bool newPopulationButtonClicked(const CEGUI::EventArgs &args);

	//Population->Edit Population
	bool editPopulationButtonClicked(const CEGUI::EventArgs &args);

	//Population->Load Population
	bool loadPopulationButtonClicked(const CEGUI::EventArgs &args);

	//Planets->Perturb Population
	bool perturbPopulationButtonClicked(
		const CEGUI::EventArgs &args);

	//Population->Save Population as...
	bool savePopulationAsButtonClicked(const CEGUI::EventArgs &args);

	//Population->Close Population
	bool closePopulationButtonClicked(const CEGUI::EventArgs &args);

	//Creature->New Random Creature
	bool newCreatureButtonClicked(const CEGUI::EventArgs &args);

	//Creature->Open Creature...
	bool openCreatureButtonClicked(const CEGUI::EventArgs &args);

	//Creature->Save Creature as...
	bool saveCreatureAsButtonClicked(const CEGUI::EventArgs &args);

	//Creature->Close Creature
	bool closeCreatureButtonClicked(const CEGUI::EventArgs &args);

	//Creature->Record frames
	bool recordFramesButtonClicked(const CEGUI::EventArgs &args);

	//Spawn->Box
	bool spawnBoxButtonClicked(const CEGUI::EventArgs &args);

	//Spawn->Sphere
	bool spawnSphereButtonClicked(const CEGUI::EventArgs &args);

	//Spawn->Capsule
	bool spawnCapsuleButtonClicked(const CEGUI::EventArgs &args);

	//Action->Return to Origin
	bool returnToOriginButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Population->Population Size...
	bool populationSizeButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Population->Selection Style...
	bool selectionStyleButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Shadows on/off
	bool shadowsButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Fog on/off
	bool fogButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Skybox on/off
	bool skyboxButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Greenscreen on/off
	bool greenscreenButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Status on/off
	bool statusButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Polygon mode->Solid mode
	bool solidButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Polygon mode->Wireframe mode
	bool wireframeButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->0 %
	bool ambientlight0ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->10 %
	bool ambientlight10ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->20 %
	bool ambientlight20ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->30 %
	bool ambientlight30ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->40 %
	bool ambientlight40ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->50 %
	bool ambientlight50ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->60 %
	bool ambientlight60ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->70 %
	bool ambientlight70ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->80 %
	bool ambientlight80ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->90 %
	bool ambientlight90ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Ambient light->100 %
	bool ambientlight100ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Tune for Speed
	bool tuneForSpeedButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Rendering->Tune for Quality
	bool tuneForQualityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 1
	bool speed1ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 2
	bool speed2ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 3
	bool speed3ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 4
	bool speed4ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 5
	bool speed5ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 6
	bool speed6ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 7
	bool speed7ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 8
	bool speed8ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 9
	bool speed9ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Movement->Speed 10
	bool speed10ButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Pause Simulation
	bool pauseSimulationButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->No Gravity
	bool noGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Pluto Gravity
	bool plutoGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Moon Gravity
	bool moonGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Mars/Mercury Gravity
	bool marsMercuryGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Uranus Gravity
	bool uranusGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Venus/Saturn Gravity
	bool venusSaturnGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Earth Gravity
	bool earthGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Neptune Gravity
	bool neptuneGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Jupiter Gravity
	bool jupiterGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Sun Gravity
	bool sunGravityButtonClicked(const CEGUI::EventArgs &args);

	//Settings->Physics->Gravity->Custom Gravity
	bool customGravityButtonClicked(const CEGUI::EventArgs &args);

	//About->Help
	bool helpButtonClicked(const CEGUI::EventArgs &args);

private:
	CEGUI::System* mSystem; /**!< pointer to the CEGUI System instance */
	CEGUI::Window* mWindow; /**!< pointer to the layout sheet window */

	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
				boost::log::attributes::constant<std::string>(
					"GUISheetHandler"));
		}
	} _initializer;
};
