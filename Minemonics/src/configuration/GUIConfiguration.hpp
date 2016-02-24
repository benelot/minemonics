#ifndef CONFIGURATION_GUICONFIGURATION_HPP_
#define CONFIGURATION_GUICONFIGURATION_HPP_

//# corresponding headers
//# forward declarations
//# system headers
#include <string>

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

/**
 * @brief		The configuration of the GUI.
 * @details		Details
 * @date		2015-05-15
 * @author		Benjamin Ellenberger
 */
class GUIConfiguration {
public:

	//#####################
	// File menu
	static const std::string fileName;
	// Quit
	static const std::string quitApplicationName;
	static const std::string quitApplicationCmd;

	//#####################
	// Evaluation menu
	static const std::string evaluationName;
	// Evolution Track
	static const std::string setEvolutionTrackName;
	static const std::string setEvolutionTrackCmd;

	// Learning Track
	static const std::string setLearningTrackName;
	static const std::string setLearningTrackCmd;

	//#####################
	//Planet menu
	// New planet
	static const std::string newPlanetName;
	static const std::string newPlanetCmd;

	//edit planet
	static const std::string editPlanetName;
	static const std::string editPlanetCmd;

	//load planet
	static const std::string loadPlanetName;
	static const std::string loadPlanetCmd;

	//new population
	static const std::string newPopulationName;
	static const std::string newPopulationCmd;

	//edit population
	static const std::string editPopulationName;
	static const std::string editPopulationCmd;

	//load population
	static const std::string loadPopulationName;
	static const std::string loadPopulationCmd;

	//perturb population
	static const std::string perturbPopulationName;
	static const std::string perturbPopulationCmd;

	static const std::string OpenFileSaveConfirm;
	static const std::string OpenFileLoadConfirm;
//#####################
//Evolution menu
//		CEGUI::Window *evolutionTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"evolutionTopItem");
//		evolutionTopItem->setText("Evolution");
//		menuBar->addChild(evolutionTopItem);
//		CEGUI::Window *evolutionMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"evolutionMenu");
//		evolutionTopItem->addChild(evolutionMenu);

	// new evolution item
//		CEGUI::Window *newEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdNewEvolution");
//		newEvolutionItem->setText("New Evolution");
//		evolutionMenu->addChild(newEvolutionItem);

	// open evolution item
//		CEGUI::Window *openEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdOpenEvolution");
//		openEvolutionItem->setText("Open Evolution...");
//		evolutionMenu->addChild(openEvolutionItem);

	// save evolution as...
//		CEGUI::Window *saveEvolutionAsItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSaveEvolutionAs");
//		saveEvolutionAsItem->setText("Save Evolution as...");
//		evolutionMenu->addChild(saveEvolutionAsItem);

	// close evolution
//		CEGUI::Window *closeEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdCloseEvolution");
//		closeEvolutionItem->setText("Close Evolution");
//		evolutionMenu->addChild(closeEvolutionItem);

	// Run evolution
//		CEGUI::Window *runEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdRunEvolution");
//		runEvolutionItem->setText("Run Evolution");
//		evolutionMenu->addChild(runEvolutionItem);

	// Pause evolution
//		CEGUI::Window *pauseEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdPauseEvolution");
//		pauseEvolutionItem->setText("Pause Evolution");
//		evolutionMenu->addChild(pauseEvolutionItem);

	// Stop evolution
//		CEGUI::Window *stopEvolutionItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdStopEvolution");
//		stopEvolutionItem->setText("Stop Evolution");
//		evolutionMenu->addChild(stopEvolutionItem);

	// Browse history
//		CEGUI::Window *browseHistoryItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdBrowseHistory");
//		browseHistoryItem->setText("Browse History");
//		evolutionMenu->addChild(browseHistoryItem);

	//#####################
	//Environment menu
//		CEGUI::Window *environmentTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"environmentTopItem");
//		environmentTopItem->setText("Environment");
//		menuBar->addChild(environmentTopItem);
//		CEGUI::Window *environmentMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"evolutionMenu");
//		environmentTopItem->addChild(environmentMenu);

	// Hills...
//		CEGUI::Window *hillsItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdHills");
//		hillsItem->setText("Hills...");
//		environmentMenu->addChild(hillsItem);

	// Opensea
//		CEGUI::Window *openSeaItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdOpenSea");
//		openSeaItem->setText("Open Sea");
//		environmentMenu->addChild(openSeaItem);

	// Plane
//		CEGUI::Window *planeItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdPlane");
//		planeItem->setText("Plane");
//		environmentMenu->addChild(planeItem);

	//#####################
	//Population menu
//		CEGUI::Window *populationTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"populationTopItem");
//		populationTopItem->setText("Population");
//		menuBar->addChild(populationTopItem);
//		CEGUI::Window *populationMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"populationMenu");
//		populationTopItem->addChild(populationMenu);

	// New Population
//		CEGUI::Window *newPopulationItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdNewPopulation");
//		newPopulationItem->setText("New Population");
//		populationMenu->addChild(newPopulationItem);

	// Open Population...
//		CEGUI::Window *openPopulationItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdOpenPopulation");
//		openPopulationItem->setText("Open Population");
//		populationMenu->addChild(openPopulationItem);

	// Save population as...
//		CEGUI::Window *savePopulationAsItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSavePopulationAs");
//		savePopulationAsItem->setText("Save Population as...");
//		populationMenu->addChild(savePopulationAsItem);

	// Close population
//		CEGUI::Window *closePopulationItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdClosePopulation");
//		closePopulationItem->setText("Close Population");
//		populationMenu->addChild(closePopulationItem);

	//#####################
	//Creature menu
//		CEGUI::Window *creatureTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"creatureTopItem");
//		creatureTopItem->setText("Creature");
//		menuBar->addChild(creatureTopItem);
//		CEGUI::Window *creatureMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"creatureMenu");
//		creatureTopItem->addChild(creatureMenu);

	// New random creature
//		CEGUI::Window *newCreatureItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdNewCreature");
//		newCreatureItem->setText("New Random Creature [F5]");
//		creatureMenu->addChild(newCreatureItem);

	// Open creature...
//		CEGUI::Window *openCreatureItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdOpenCreature");
//		openCreatureItem->setText("Open Creature...");
//		creatureMenu->addChild(openCreatureItem);

	// Save creature as...
//		CEGUI::Window *saveCreatureAsItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSaveCreatureAs");
//		saveCreatureAsItem->setText("Save Creature As...");
//		creatureMenu->addChild(saveCreatureAsItem);

	// Close creature
//		CEGUI::Window *closeCreatureItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdCloseCreature");
//		closeCreatureItem->setText("Close Creature");
//		creatureMenu->addChild(closeCreatureItem);

	// Record frames
//		CEGUI::Window *recordFramesItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdRecordFrames");
//		recordFramesItem->setText("Record Frames [CTRL+R]");
//		creatureMenu->addChild(recordFramesItem);

	//#####################
	//Spawn menu
//		CEGUI::Window *spawnTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"spawnTopItem");
//		spawnTopItem->setText("Spawn");
//		menuBar->addChild(spawnTopItem);
//		CEGUI::Window *spawnMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"spawnMenu");
//		spawnTopItem->addChild(spawnMenu);

	// spawn Box
//		CEGUI::Window *spawnBoxItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpawnBox");
//		spawnBoxItem->setText("Box [2]");
//		spawnMenu->addChild(spawnBoxItem);

	// spawn Sphere
//		CEGUI::Window *spawnSphereItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpawnSphere");
//		spawnSphereItem->setText("Sphere [3]");
//		spawnMenu->addChild(spawnSphereItem);

	// spawn Capsule
//		CEGUI::Window *spawnCapsuleItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpawnCapsule");
//		spawnCapsuleItem->setText("Capsule [6]");
//		spawnMenu->addChild(spawnCapsuleItem);

	//#####################
	// Action menu
//		CEGUI::Window *actionTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"actionTopItem");
//		actionTopItem->setText("Action");
//		menuBar->addChild(actionTopItem);
//		CEGUI::Window *actionMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"actionMenu");
//		actionTopItem->addChild(actionMenu);

	// Return to origin
//		CEGUI::Window *returnToOriginItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdReturnToOrigin");
//		returnToOriginItem->setText("Return to Origin [K]");
//		actionMenu->addChild(returnToOriginItem);

	//#####################
	//Settings menu
//		CEGUI::Window *settingsTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"settingsTopItem");
//		settingsTopItem->setText("Settings");
//		menuBar->addChild(settingsTopItem);
//		CEGUI::Window *settingsMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"settingsMenu");
//		settingsTopItem->addChild(settingsMenu);

	// Evolution menu
//		CEGUI::Window *evolutionSettingsTopItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "evolutionSettingsTopItem");
//		evolutionSettingsTopItem->setText("Evolution");
//		settingsMenu->addChild(evolutionSettingsTopItem);
//		CEGUI::Window *evolutionSettingsMenu = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "evolutionSettingsMenu");
//		evolutionSettingsTopItem->addChild(evolutionSettingsMenu);

	//Population menu
//		CEGUI::Window *populationSettingsTopItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "populationSettingsTopItem");
//		populationSettingsTopItem->setText("Population");
//		settingsMenu->addChild(populationSettingsTopItem);
//		CEGUI::Window *populationSettingsMenu = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "populationSettingsMenu");
//		populationSettingsTopItem->addChild(populationSettingsMenu);

	// Population size
//		CEGUI::Window *populationSizeItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdPopulationSize");
//		populationSizeItem->setText("Population Size...");
//		populationSettingsMenu->addChild(populationSizeItem);

	// Selection style
//		CEGUI::Window *selectionStyleItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSelectionStyle");
//		selectionStyleItem->setText("Selection Style...");
//		populationSettingsMenu->addChild(selectionStyleItem);

	// Creature
//		CEGUI::Window *creatureSettingsTopItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "creatureSettingsTopItem");
//		creatureSettingsTopItem->setText("Creature");
//		settingsMenu->addChild(creatureSettingsTopItem);
//		CEGUI::Window *creatureSettingsMenu = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "creatureSettingsMenu");
//		creatureSettingsTopItem->addChild(creatureSettingsMenu);

	// Rendering
//		CEGUI::Window *renderingTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"renderingTopItem");
//		renderingTopItem->setText("Rendering");
//		settingsMenu->addChild(renderingTopItem);

	// Rendering menu
//		CEGUI::Window *renderingMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"renderingMenu");
//		renderingTopItem->addChild(renderingMenu);

	// Shadows on/off
//		CEGUI::Window *shadowsItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdShadows");
//		shadowsItem->setText("Shadows on/off [H]");
//		renderingMenu->addChild(shadowsItem);

	// Fog on/off
//		CEGUI::Window *fogItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdFog");
//		fogItem->setText("Fog on/off [F]");
//		renderingMenu->addChild(fogItem);

	// Skybox on/off
//		CEGUI::Window *skyboxItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSkybox");
//		skyboxItem->setText("Skybox on/off [B]");
//		renderingMenu->addChild(skyboxItem);

	// Greenscreen on/off
//		CEGUI::Window *greenscreenItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdGreenscreen");
//		greenscreenItem->setText("Greenscreen on/off");
//		renderingMenu->addChild(greenscreenItem);

	// Status on/off
//		CEGUI::Window *statusItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdStatus");
//		statusItem->setText("Status on/off");
//		renderingMenu->addChild(statusItem);

	// Polygon mode
//		CEGUI::Window *polygonModeTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"polygonModeTopItem");
//		polygonModeTopItem->setText("Polygon mode");
//		renderingMenu->addChild(polygonModeTopItem);

	// Polygon mode menu
//		CEGUI::Window *polygonModeMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"polygonModeMenu");
//		polygonModeTopItem->addChild(polygonModeMenu);

	// Solid
//		CEGUI::Window *solidModeItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSolidMode");
//		solidModeItem->setText("Solid mode");
//		polygonModeMenu->addChild(solidModeItem);

	// Wireframe
//		CEGUI::Window *wireframeModeItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdWireframeMode");
//		wireframeModeItem->setText("Wireframe mode");
//		polygonModeMenu->addChild(wireframeModeItem);

	// Ambient light
	static const std::string ambientLightName;

	// 0 %
	static const std::string ambientLight0Name;
	static const std::string ambientLight0Cmd;

	// 10 %
	static const std::string ambientLight10Name;
	static const std::string ambientLight10Cmd;

	// 20 %
	static const std::string ambientLight20Name;
	static const std::string ambientLight20Cmd;

	// 30 %
	static const std::string ambientLight30Name;
	static const std::string ambientLight30Cmd;

	// 40 %
	static const std::string ambientLight40Name;
	static const std::string ambientLight40Cmd;

	// 50 %
	static const std::string ambientLight50Name;
	static const std::string ambientLight50Cmd;

	// 60 %
	static const std::string ambientLight60Name;
	static const std::string ambientLight60Cmd;

	// 70 %
	static const std::string ambientLight70Name;
	static const std::string ambientLight70Cmd;

	// 80 %
	static const std::string ambientLight80Name;
	static const std::string ambientLight80Cmd;

	// 90 %
	static const std::string ambientLight90Name;
	static const std::string ambientLight90Cmd;

	// 100 %
	static const std::string ambientLight100Name;
	static const std::string ambientLight100Cmd;

	// Tune for speed
//		CEGUI::Window *tuneForSpeedItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdTuneForSpeed");
//		tuneForSpeedItem->setText("Tune for Speed [Keypad -]");
//		renderingMenu->addChild(tuneForSpeedItem);

	// Tune for quality
//		CEGUI::Window *tuneForQualityItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdTuneForQuality");
//		tuneForQualityItem->setText("Tune for Quality [Keypad +]");
//		renderingMenu->addChild(tuneForQualityItem);

	// Movement
//		CEGUI::Window *movementTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"movementTopItem");
//		movementTopItem->setText("Movement");
//		settingsMenu->addChild(movementTopItem);

	// Movement menu
//		CEGUI::Window *movementMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"movementMenu");
//		movementTopItem->addChild(movementMenu);

	// Speed 1
//		CEGUI::Window *speed1Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed1");
//		speed1Item->setText("Speed 1 [ALT-1]");
//		movementMenu->addChild(speed1Item);

	// Speed 2
//		CEGUI::Window *speed2Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed2");
//		speed2Item->setText("Speed 2 [ALT-2]");
//		movementMenu->addChild(speed2Item);

	// Speed 3
//		CEGUI::Window *speed3Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed3");
//		speed3Item->setText("Speed 3 [ALT-3]");
//		movementMenu->addChild(speed3Item);

	// Speed 4
//		CEGUI::Window *speed4Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed4");
//		speed4Item->setText("Speed 4 [ALT-4]");
//		movementMenu->addChild(speed4Item);

	// Speed 5
//		CEGUI::Window *speed5Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed5");
//		speed5Item->setText("Speed 5 [ALT-5]");
//		movementMenu->addChild(speed5Item);

	// Speed 6
//		CEGUI::Window *speed6Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed6");
//		speed6Item->setText("Speed 6 [ALT-6]");
//		movementMenu->addChild(speed6Item);

	// Speed 7
//		CEGUI::Window *speed7Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed7");
//		speed7Item->setText("Speed 7 [ALT-7]");
//		movementMenu->addChild(speed7Item);

	// Speed 8
//		CEGUI::Window *speed8Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed8");
//		speed8Item->setText("Speed 8 [ALT-8]");
//		movementMenu->addChild(speed8Item);

	// Speed 9
//		CEGUI::Window *speed9Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed9");
//		speed9Item->setText("Speed 9 [ALT-9]");
//		movementMenu->addChild(speed9Item);

	// Speed 10
//		CEGUI::Window *speed10Item = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"cmdSpeed10");
//		speed10Item->setText("Speed 10 [ALT-10]");
//		movementMenu->addChild(speed10Item);

	// Physics
//		CEGUI::Window *physicsTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"physicsTopItem");
//		physicsTopItem->setText("Physics");
//		settingsMenu->addChild(physicsTopItem);

	// Physics menu
//		CEGUI::Window *physicsMenu = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
//				"physicsMenu");
//		physicsTopItem->addChild(physicsMenu);

	// Pause simulation
//		CEGUI::Window *pauseSimulationItem = wmgr.createWindow(
//				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdPauseSimulation");
//		pauseSimulationItem->setText("Pause Simulation");
//		physicsMenu->addChild(pauseSimulationItem);

	// gravity
//		CEGUI::Window *gravityTopItem = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//				"gravityTopItem");
//		gravityTopItem->setText("Gravity");
//		physicsMenu->addChild(gravityTopItem);

	// No gravity
	static const std::string noGravityName;
	static const std::string noGravityCmd;

	// Pluto gravity 0.059
	static const std::string plutoGravityName;
	static const std::string plutoGravityCmd;

	// Moon gravity 0.166
	static const std::string moonGravityName;
	static const std::string moonGravityCmd;

	// Mars/Mercury gravity 0.377/0.378
	static const std::string marsMercuryGravityName;
	static const std::string marsMercuryGravityCmd;

	// Uranus gravity 0.889
	static const std::string uranusGravityName;
	static const std::string uranusGravityCmd;

	// Venus/Saturn gravity 0.907/0.916
	static const std::string venusSaturnGravityName;
	static const std::string venusSaturnGravityCmd;

	// Earth gravity 1
	static const std::string earthGravityName;
	static const std::string earthGravityCmd;

	// Neptune gravity 1.12
	static const std::string neptuneGravityName;
	static const std::string neptuneGravityCmd;

	// Jupiter gravity 2.36
	static const std::string jupiterGravityName;
	static const std::string jupiterGravityCmd;

	// Sun gravity 27.930682977
	static const std::string sunGravityName;
	static const std::string sunGravityCmd;

};

#endif /* CONFIGURATION_GUICONFIGURATION_HPP_ */
