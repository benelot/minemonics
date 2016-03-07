//# corresponding headers
#include <stddef.h>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/Size.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
//## configuration headers
#include <configuration/GUIConfiguration.hpp>
#include <configuration/CEGUIConfiguration.hpp>
#include <view/visualization/CEGUI/MenuBar.hpp>

//## controller headers
//## model headers
//## view headers
//## utils headers

MenuBar::MenuBar() {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	//Menu bar
	mMenuBar = wmgr.createWindow(CEGUIConfiguration::CEGUI_SCHEME + "/Menubar",
		"menu");
	mMenuBar->setAlwaysOnTop(true);
	mMenuBar->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.037, 0)));
	mMenuBar->setPosition(
		CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));

	{
		//#####################
		//File menu
		CEGUI::Window *fileTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "fileTopItem");
		fileTopItem->setText(GUIConfiguration::fileName);
		mMenuBar->addChild(fileTopItem);
		CEGUI::Window *fileMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "fileMenu");
		fileTopItem->addChild(fileMenu);

		// Quit
		CEGUI::Window *quitApplicationItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::quitApplicationCmd);
		quitApplicationItem->setText(GUIConfiguration::quitApplicationName);
		fileMenu->addChild(quitApplicationItem);
	}

	{
		//#####################
		//Evaluation menu
		CEGUI::Window *evaluationTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			"evaluationTopItem");
		evaluationTopItem->setText(GUIConfiguration::evaluationName);
		mMenuBar->addChild(evaluationTopItem);
		CEGUI::Window *evaluationMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "evaluationMenu");
		evaluationTopItem->addChild(evaluationMenu);

		// Evolution Track
		CEGUI::Window *evolutionTrackItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::setEvolutionTrackCmd);
		evolutionTrackItem->setText(GUIConfiguration::setEvolutionTrackName);
		evaluationMenu->addChild(evolutionTrackItem);

		// Learning Track
		CEGUI::Window *learningTrackItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::setLearningTrackCmd);
		learningTrackItem->setText(GUIConfiguration::setLearningTrackName);
		evaluationMenu->addChild(learningTrackItem);
	}

	{
		//#####################
		//Planet menu
		CEGUI::Window *planetTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "planetTopItem");
		planetTopItem->setText("Planets");
		mMenuBar->addChild(planetTopItem);
		CEGUI::Window *planetMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "planetMenu");
		planetTopItem->addChild(planetMenu);

		// New planet
		CEGUI::Window *newPlanetItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::newPlanetCmd);
		newPlanetItem->setText(GUIConfiguration::newPlanetName);
		planetMenu->addChild(newPlanetItem);

		// Edit planet
		CEGUI::Window *editPlanetItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::editPlanetCmd);
		editPlanetItem->setText(GUIConfiguration::editPlanetName);
		planetMenu->addChild(editPlanetItem);

		// Load planet
		CEGUI::Window *loadPlanetItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			GUIConfiguration::loadPlanetCmd);
		loadPlanetItem->setText(GUIConfiguration::loadPlanetName);
		planetMenu->addChild(loadPlanetItem);
	}

	{
		//#####################
		//Evolution menu
		CEGUI::Window *evolutionTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "evolutionTopItem");
		evolutionTopItem->setText("Evolution");
		mMenuBar->addChild(evolutionTopItem);
		CEGUI::Window *evolutionMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "evolutionMenu");
		evolutionTopItem->addChild(evolutionMenu);

//		// new evolution item
//		CEGUI::Window *newEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdNewEvolution");
//		newEvolutionItem->setText("New Evolution");
//		evolutionMenu->addChild(newEvolutionItem);
//
//		// open evolution item
//		CEGUI::Window *openEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdOpenEvolution");
//		openEvolutionItem->setText("Open Evolution...");
//		evolutionMenu->addChild(openEvolutionItem);
//
//		// save evolution as...
//		CEGUI::Window *saveEvolutionAsItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdSaveEvolutionAs");
//		saveEvolutionAsItem->setText("Save Evolution as...");
//		evolutionMenu->addChild(saveEvolutionAsItem);
//
//		// close evolution
//		CEGUI::Window *closeEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdCloseEvolution");
//		closeEvolutionItem->setText("Close Evolution");
//		evolutionMenu->addChild(closeEvolutionItem);
//
//		// Run evolution
//		CEGUI::Window *runEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdRunEvolution");
//		runEvolutionItem->setText("Run Evolution");
//		evolutionMenu->addChild(runEvolutionItem);
//
//		// Pause evolution
//		CEGUI::Window *pauseEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdPauseEvolution");
//		pauseEvolutionItem->setText("Pause Evolution");
//		evolutionMenu->addChild(pauseEvolutionItem);
//
//		// Stop evolution
//		CEGUI::Window *stopEvolutionItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdStopEvolution");
//		stopEvolutionItem->setText("Stop Evolution");
//		evolutionMenu->addChild(stopEvolutionItem);
//
//		// Browse history
//		CEGUI::Window *browseHistoryItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdBrowseHistory");
//		browseHistoryItem->setText("Browse History");
//		evolutionMenu->addChild(browseHistoryItem);

	}

	{
		//#####################
		//Environment menu
		CEGUI::Window *environmentTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			"environmentTopItem");
		environmentTopItem->setText("Environment");
		mMenuBar->addChild(environmentTopItem);
		CEGUI::Window *environmentMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "evolutionMenu");
		environmentTopItem->addChild(environmentMenu);

//	// Hills...
//	CEGUI::Window *hillsItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdHills");
//	hillsItem->setText("Hills...");
//	environmentMenu->addChild(hillsItem);
//
//	// Opensea
//	CEGUI::Window *openSeaItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdOpenSea");
//	openSeaItem->setText("Open Sea");
//	environmentMenu->addChild(openSeaItem);
//
//	// Plane
//	CEGUI::Window *planeItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdPlane");
//	planeItem->setText("Plane");
//	environmentMenu->addChild(planeItem);

	}

//#####################
//Population menu
	{

		CEGUI::Window *populationTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
			"populationTopItem");
		populationTopItem->setText("Population");
		mMenuBar->addChild(populationTopItem);
		CEGUI::Window *populationMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "populationMenu");
		populationTopItem->addChild(populationMenu);

		{
			// New Population
			CEGUI::Window *newPopulationItem = wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
				GUIConfiguration::newPopulationCmd);
			newPopulationItem->setText(GUIConfiguration::newPopulationName);
			populationMenu->addChild(newPopulationItem);
		}

		{
			// Edit Population
			CEGUI::Window *editPopulationItem = wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
				GUIConfiguration::editPopulationCmd);
			editPopulationItem->setText(GUIConfiguration::editPopulationName);
			populationMenu->addChild(editPopulationItem);
		}

		{
			// Load Population
			CEGUI::Window *loadPopulationItem = wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
				GUIConfiguration::loadPopulationCmd);
			loadPopulationItem->setText(GUIConfiguration::loadPopulationName);
			populationMenu->addChild(loadPopulationItem);
		}

		{
			// Perturb Population
			CEGUI::Window *perturbPopulationItem = wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
				GUIConfiguration::perturbPopulationCmd);
			perturbPopulationItem->setText(
				GUIConfiguration::perturbPopulationName);
			populationMenu->addChild(perturbPopulationItem);
		}

//		// Open Population...
//		CEGUI::Window *openPopulationItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdOpenPopulation");
//		openPopulationItem->setText("Open Population");
//		populationMenu->addChild(openPopulationItem);

//		// Save population as...
//		CEGUI::Window *savePopulationAsItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdSavePopulationAs");
//		savePopulationAsItem->setText("Save Population as...");
//		populationMenu->addChild(savePopulationAsItem);

//		// Close population
//		CEGUI::Window *closePopulationItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
//			"cmdClosePopulation");
//		closePopulationItem->setText("Close Population");
//		populationMenu->addChild(closePopulationItem);
	}

	{
//#####################
//Creature menu
		CEGUI::Window *creatureTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "creatureTopItem");
		creatureTopItem->setText("Creature");
		mMenuBar->addChild(creatureTopItem);
		CEGUI::Window *creatureMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "creatureMenu");
		creatureTopItem->addChild(creatureMenu);

//// New random creature
//	CEGUI::Window *newCreatureItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdNewCreature");
//	newCreatureItem->setText("New Random Creature [F5]");
//	creatureMenu->addChild(newCreatureItem);
//
//// Open creature...
//	CEGUI::Window *openCreatureItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdOpenCreature");
//	openCreatureItem->setText("Open Creature...");
//	creatureMenu->addChild(openCreatureItem);
//
//// Save creature as...
//	CEGUI::Window *saveCreatureAsItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSaveCreatureAs");
//	saveCreatureAsItem->setText("Save Creature As...");
//	creatureMenu->addChild(saveCreatureAsItem);
//
//// Close creature
//	CEGUI::Window *closeCreatureItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdCloseCreature");
//	closeCreatureItem->setText("Close Creature");
//	creatureMenu->addChild(closeCreatureItem);
//
//// Record frames
//	CEGUI::Window *recordFramesItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdRecordFrames");
//	recordFramesItem->setText("Record Frames [CTRL+R]");
//	creatureMenu->addChild(recordFramesItem);
	}

	{
//#####################
//Spawn menu
		CEGUI::Window *spawnTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "spawnTopItem");
		spawnTopItem->setText("Spawn");
		mMenuBar->addChild(spawnTopItem);
		CEGUI::Window *spawnMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "spawnMenu");
		spawnTopItem->addChild(spawnMenu);

//// spawn Box
//		CEGUI::Window *spawnBoxItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpawnBox");
//		spawnBoxItem->setText("Box [2]");
//		spawnMenu->addChild(spawnBoxItem);
//
//// spawn Sphere
//		CEGUI::Window *spawnSphereItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpawnSphere");
//		spawnSphereItem->setText("Sphere [3]");
//		spawnMenu->addChild(spawnSphereItem);
//
//// spawn Capsule
//		CEGUI::Window *spawnCapsuleItem = wmgr.createWindow(
//			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpawnCapsule");
//		spawnCapsuleItem->setText("Capsule [6]");
//		spawnMenu->addChild(spawnCapsuleItem);
	}

	{
//#####################
// Action menu
		CEGUI::Window *actionTopItem = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "actionTopItem");
		actionTopItem->setText("Action");
		mMenuBar->addChild(actionTopItem);
		CEGUI::Window *actionMenu = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "actionMenu");
		actionTopItem->addChild(actionMenu);

//// Return to origin
//	CEGUI::Window *returnToOriginItem = wmgr.createWindow(
//		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdReturnToOrigin");
//	returnToOriginItem->setText("Return to Origin [K]");
//	actionMenu->addChild(returnToOriginItem);

	}

//#####################
//Settings menu
	CEGUI::Window *settingsTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "settingsTopItem");
	settingsTopItem->setText("Settings");
	mMenuBar->addChild(settingsTopItem);
	CEGUI::Window *settingsMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "settingsMenu");
	settingsTopItem->addChild(settingsMenu);

// Evolution menu
	CEGUI::Window *evolutionSettingsTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		"evolutionSettingsTopItem");
	evolutionSettingsTopItem->setText("Evolution");
	settingsMenu->addChild(evolutionSettingsTopItem);
	CEGUI::Window *evolutionSettingsMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
		"evolutionSettingsMenu");
	evolutionSettingsTopItem->addChild(evolutionSettingsMenu);

//Population menu
	CEGUI::Window *populationSettingsTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		"populationSettingsTopItem");
	populationSettingsTopItem->setText("Population");
	settingsMenu->addChild(populationSettingsTopItem);
	CEGUI::Window *populationSettingsMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
		"populationSettingsMenu");
	populationSettingsTopItem->addChild(populationSettingsMenu);

// Population size
	CEGUI::Window *populationSizeItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdPopulationSize");
	populationSizeItem->setText("Population Size...");
	populationSettingsMenu->addChild(populationSizeItem);

// Selection style
	CEGUI::Window *selectionStyleItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSelectionStyle");
	selectionStyleItem->setText("Selection Style...");
	populationSettingsMenu->addChild(selectionStyleItem);

// Creature
	CEGUI::Window *creatureSettingsTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		"creatureSettingsTopItem");
	creatureSettingsTopItem->setText("Creature");
	settingsMenu->addChild(creatureSettingsTopItem);
	CEGUI::Window *creatureSettingsMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu",
		"creatureSettingsMenu");
	creatureSettingsTopItem->addChild(creatureSettingsMenu);

// Rendering
	CEGUI::Window *renderingTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "renderingTopItem");
	renderingTopItem->setText("Rendering");
	settingsMenu->addChild(renderingTopItem);

// Rendering menu
	CEGUI::Window *renderingMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "renderingMenu");
	renderingTopItem->addChild(renderingMenu);

// Shadows on/off
	CEGUI::Window *shadowsItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdShadows");
	shadowsItem->setText("Shadows on/off [H]");
	renderingMenu->addChild(shadowsItem);

// Fog on/off
	CEGUI::Window *fogItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdFog");
	fogItem->setText("Fog on/off [F]");
	renderingMenu->addChild(fogItem);

// Skybox on/off
	CEGUI::Window *skyboxItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSkybox");
	skyboxItem->setText("Skybox on/off [B]");
	renderingMenu->addChild(skyboxItem);

// Greenscreen on/off
	CEGUI::Window *greenscreenItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdGreenscreen");
	greenscreenItem->setText("Greenscreen on/off");
	renderingMenu->addChild(greenscreenItem);

// Status on/off
	CEGUI::Window *statusItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdStatus");
	statusItem->setText("Status on/off");
	renderingMenu->addChild(statusItem);

// Polygon mode
	CEGUI::Window *polygonModeTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "polygonModeTopItem");
	polygonModeTopItem->setText("Polygon mode");
	renderingMenu->addChild(polygonModeTopItem);

// Polygon mode menu
	CEGUI::Window *polygonModeMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "polygonModeMenu");
	polygonModeTopItem->addChild(polygonModeMenu);

// Solid
	CEGUI::Window *solidModeItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSolidMode");
	solidModeItem->setText("Solid mode");
	polygonModeMenu->addChild(solidModeItem);

// Wireframe
	CEGUI::Window *wireframeModeItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdWireframeMode");
	wireframeModeItem->setText("Wireframe mode");
	polygonModeMenu->addChild(wireframeModeItem);

// Ambient light
	CEGUI::Window *ambientLightTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "ambientLightTopItem");
	ambientLightTopItem->setText("Ambient light");
	renderingMenu->addChild(ambientLightTopItem);

// Ambient light menu
	CEGUI::Window *ambientLightMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "ambientLightMenu");
	ambientLightTopItem->addChild(ambientLightMenu);

// 0 %
	CEGUI::Window *ambientLight0Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight0Cmd);
	ambientLight0Item->setText(GUIConfiguration::ambientLight0Name);
	ambientLightMenu->addChild(ambientLight0Item);

// 10 %
	CEGUI::Window *ambientLight10Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight10Cmd);
	ambientLight10Item->setText(GUIConfiguration::ambientLight10Name);
	ambientLightMenu->addChild(ambientLight10Item);

// 20 %
	CEGUI::Window *ambientLight20Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight20Cmd);
	ambientLight20Item->setText(GUIConfiguration::ambientLight20Name);
	ambientLightMenu->addChild(ambientLight20Item);

// 30 %
	CEGUI::Window *ambientLight30Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight30Cmd);
	ambientLight30Item->setText(GUIConfiguration::ambientLight30Name);
	ambientLightMenu->addChild(ambientLight30Item);

// 40 %
	CEGUI::Window *ambientLight40Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight40Cmd);
	ambientLight40Item->setText(GUIConfiguration::ambientLight40Name);
	ambientLightMenu->addChild(ambientLight40Item);

// 50 %
	CEGUI::Window *ambientLight50Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight50Cmd);
	ambientLight50Item->setText(GUIConfiguration::ambientLight50Name);
	ambientLightMenu->addChild(ambientLight50Item);

// 60 %
	CEGUI::Window *ambientLight60Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight60Cmd);
	ambientLight60Item->setText(GUIConfiguration::ambientLight60Name);
	ambientLightMenu->addChild(ambientLight60Item);

// 70 %
	CEGUI::Window *ambientLight70Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight70Cmd);
	ambientLight70Item->setText(GUIConfiguration::ambientLight70Name);
	ambientLightMenu->addChild(ambientLight70Item);

// 80 %
	CEGUI::Window *ambientLight80Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight80Cmd);
	ambientLight80Item->setText(GUIConfiguration::ambientLight80Name);
	ambientLightMenu->addChild(ambientLight80Item);

// 90 %
	CEGUI::Window *ambientLight90Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight90Cmd);
	ambientLight90Item->setText(GUIConfiguration::ambientLight90Name);
	ambientLightMenu->addChild(ambientLight90Item);

// 100 %
	CEGUI::Window *ambientLight100Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::ambientLight100Cmd);
	ambientLight100Item->setText(GUIConfiguration::ambientLight100Name);
	ambientLightMenu->addChild(ambientLight100Item);

// Tune for speed
	CEGUI::Window *tuneForSpeedItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdTuneForSpeed");
	tuneForSpeedItem->setText("Tune for Speed [Keypad -]");
	renderingMenu->addChild(tuneForSpeedItem);

// Tune for quality
	CEGUI::Window *tuneForQualityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdTuneForQuality");
	tuneForQualityItem->setText("Tune for Quality [Keypad +]");
	renderingMenu->addChild(tuneForQualityItem);

// Movement
	CEGUI::Window *movementTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "movementTopItem");
	movementTopItem->setText("Movement");
	settingsMenu->addChild(movementTopItem);

// Movement menu
	CEGUI::Window *movementMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "movementMenu");
	movementTopItem->addChild(movementMenu);

// Speed 1
	CEGUI::Window *speed1Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed1");
	speed1Item->setText("Speed 1 [ALT-1]");
	movementMenu->addChild(speed1Item);

// Speed 2
	CEGUI::Window *speed2Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed2");
	speed2Item->setText("Speed 2 [ALT-2]");
	movementMenu->addChild(speed2Item);

// Speed 3
	CEGUI::Window *speed3Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed3");
	speed3Item->setText("Speed 3 [ALT-3]");
	movementMenu->addChild(speed3Item);

// Speed 4
	CEGUI::Window *speed4Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed4");
	speed4Item->setText("Speed 4 [ALT-4]");
	movementMenu->addChild(speed4Item);

// Speed 5
	CEGUI::Window *speed5Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed5");
	speed5Item->setText("Speed 5 [ALT-5]");
	movementMenu->addChild(speed5Item);

// Speed 6
	CEGUI::Window *speed6Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed6");
	speed6Item->setText("Speed 6 [ALT-6]");
	movementMenu->addChild(speed6Item);

// Speed 7
	CEGUI::Window *speed7Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed7");
	speed7Item->setText("Speed 7 [ALT-7]");
	movementMenu->addChild(speed7Item);

// Speed 8
	CEGUI::Window *speed8Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed8");
	speed8Item->setText("Speed 8 [ALT-8]");
	movementMenu->addChild(speed8Item);

// Speed 9
	CEGUI::Window *speed9Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed9");
	speed9Item->setText("Speed 9 [ALT-9]");
	movementMenu->addChild(speed9Item);

// Speed 10
	CEGUI::Window *speed10Item = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdSpeed10");
	speed10Item->setText("Speed 10 [ALT-10]");
	movementMenu->addChild(speed10Item);

// Physics
	CEGUI::Window *physicsTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "physicsTopItem");
	physicsTopItem->setText("Physics");
	settingsMenu->addChild(physicsTopItem);

// Physics menu
	CEGUI::Window *physicsMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "physicsMenu");
	physicsTopItem->addChild(physicsMenu);

// Pause simulation
	CEGUI::Window *pauseSimulationItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdPauseSimulation");
	pauseSimulationItem->setText("Pause Simulation");
	physicsMenu->addChild(pauseSimulationItem);

// gravity
	CEGUI::Window *gravityTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "gravityTopItem");
	gravityTopItem->setText("Gravity");
	physicsMenu->addChild(gravityTopItem);

//gravity menu
	CEGUI::Window *gravityMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "gravityMenu");
	gravityTopItem->addChild(gravityMenu);

// No gravity
	CEGUI::Window *noGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::noGravityCmd);
	noGravityItem->setText(GUIConfiguration::noGravityName);
	gravityMenu->addChild(noGravityItem);

// Pluto gravity 0.059
	CEGUI::Window *plutoGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::plutoGravityCmd);
	plutoGravityItem->setText(GUIConfiguration::plutoGravityName);
	gravityMenu->addChild(plutoGravityItem);

// Moon gravity 0.166
	CEGUI::Window *moonGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::moonGravityCmd);
	moonGravityItem->setText(GUIConfiguration::moonGravityName);
	gravityMenu->addChild(moonGravityItem);

// Mars/Mercury gravity 0.377/0.378
	CEGUI::Window *marsMercuryGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::marsMercuryGravityCmd);
	marsMercuryGravityItem->setText(GUIConfiguration::marsMercuryGravityName);
	gravityMenu->addChild(marsMercuryGravityItem);

// Uranus gravity 0.889
	CEGUI::Window *uranusGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::uranusGravityCmd);
	uranusGravityItem->setText(GUIConfiguration::uranusGravityName);
	gravityMenu->addChild(uranusGravityItem);

// Venus/Saturn gravity 0.907/0.916
	CEGUI::Window *venusSaturnGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::venusSaturnGravityCmd);
	venusSaturnGravityItem->setText(GUIConfiguration::venusSaturnGravityName);
	gravityMenu->addChild(venusSaturnGravityItem);

// Earth gravity 1
	CEGUI::Window *earthGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::earthGravityCmd);
	earthGravityItem->setText(GUIConfiguration::earthGravityName);
	gravityMenu->addChild(earthGravityItem);

// Neptune gravity 1.12
	CEGUI::Window *neptuneGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::neptuneGravityCmd);
	neptuneGravityItem->setText(GUIConfiguration::neptuneGravityName);
	gravityMenu->addChild(neptuneGravityItem);

// Jupiter gravity 2.36
	CEGUI::Window *jupiterGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::jupiterGravityCmd);
	jupiterGravityItem->setText(GUIConfiguration::jupiterGravityName);
	gravityMenu->addChild(jupiterGravityItem);

// Sun gravity 27.930682977
	CEGUI::Window *sunGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem",
		GUIConfiguration::sunGravityCmd);
	sunGravityItem->setText(GUIConfiguration::sunGravityName);
	gravityMenu->addChild(sunGravityItem);

// Custom gravity...
	CEGUI::Window *customGravityItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdCustomGravity");
	customGravityItem->setText("Custom Gravity");
	gravityMenu->addChild(customGravityItem);

//#####################
// Help menu
	CEGUI::Window *helpTopItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "helpTopItem");
	helpTopItem->setText("Help");
	mMenuBar->addChild(helpTopItem);
	CEGUI::Window *helpMenu = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/PopupMenu", "helpMenu");
	helpTopItem->addChild(helpMenu);

// About
	CEGUI::Window *aboutItem = wmgr.createWindow(
		CEGUIConfiguration::CEGUI_SCHEME + "/MenuItem", "cmdAbout");
	aboutItem->setText("About");
	helpMenu->addChild(aboutItem);
}

MenuBar::~MenuBar() {
	//Cleanup according to
	// http://cegui.org.uk/wiki/CEGUI_In_Practice_-_Introduction
	// http://cegui.org.uk/forum/viewtopic.php?t=1535

	if (mMenuBar) {
		CEGUI::WindowManager::getSingleton().destroyWindow(mMenuBar);
//	delete mMenuBar;
	}
	mMenuBar = NULL;
}

