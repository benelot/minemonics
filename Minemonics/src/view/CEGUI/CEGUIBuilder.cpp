/*
 * CEGUIBuilder.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: leviathan
 */

#include "view/CEGUI/CEGUIBuilder.h"

// CEGUI includes
#include <CEGUI/System.h>
#include <CEGUI/InputEvent.h>
#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/SchemeManager.h>
#include <CEGUI/FontManager.h>
#include "view/CEGUI/ParamsPanel.h"

#include "SimulationManager.h"

CEGUIBuilder::CEGUIBuilder(SimulationManager* simulationMgr) {
	mSimulationMgr = simulationMgr;

}

CEGUIBuilder::~CEGUIBuilder() {
	// TODO Auto-generated destructor stub
}

CEGUI::Window* CEGUIBuilder::createMenu() {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	//Menu bar
	CEGUI::Window *menuBar = wmgr.createWindow("Ogremonics/Menubar", "menu");
	menuBar->setSize(CEGUI::USize(CEGUI::UDim(1, 0), CEGUI::UDim(0.037, 0)));
	menuBar->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));

	//#####################
	//File menu
	CEGUI::Window *fileTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"fileTopItem");
	fileTopItem->setText("File");
	menuBar->addChild(fileTopItem);
	CEGUI::Window *fileMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"fileMenu");
	fileTopItem->addChild(fileMenu);

	//quit item
	CEGUI::Window *quitApplicationItem = wmgr.createWindow("Ogremonics/MenuItem",
			"cmdQuitApplication");
	quitApplicationItem->setText("Quit [Q]");
	fileMenu->addChild(quitApplicationItem);

	//#####################
	//Evolution menu
	CEGUI::Window *evolutionTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"evolutionTopItem");
	evolutionTopItem->setText("Evolution");
	menuBar->addChild(evolutionTopItem);
	CEGUI::Window *evolutionMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"evolutionMenu");
	evolutionTopItem->addChild(evolutionMenu);

	// new evolution item
	CEGUI::Window *newEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"cmdNewEvolution");
	newEvolutionItem->setText("New Evolution");
	evolutionMenu->addChild(newEvolutionItem);

	// open evolution item
	CEGUI::Window *openEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"openEvolutionItem");
	openEvolutionItem->setText("Open Evolution...");
	evolutionMenu->addChild(openEvolutionItem);

	// save evolution as...
	CEGUI::Window *saveEvolutionAsItem = wmgr.createWindow("Ogremonics/MenuItem",
			"saveEvolutionAsItem");
	saveEvolutionAsItem->setText("Save Evolution as...");
	evolutionMenu->addChild(saveEvolutionAsItem);

	// close evolution
	CEGUI::Window *closeEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"closeEvolutionItem");
	closeEvolutionItem->setText("Close Evolution");
	evolutionMenu->addChild(closeEvolutionItem);

	// Run evolution
	CEGUI::Window *runEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"runEvolutionItem");
	runEvolutionItem->setText("Run Evolution");
	evolutionMenu->addChild(runEvolutionItem);

	// Pause evolution
	CEGUI::Window *pauseEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"pauseEvolutionItem");
	pauseEvolutionItem->setText("Pause Evolution");
	evolutionMenu->addChild(pauseEvolutionItem);

	// Stop evolution
	CEGUI::Window *stopEvolutionItem = wmgr.createWindow("Ogremonics/MenuItem",
			"stopEvolutionItem");
	stopEvolutionItem->setText("Stop Evolution");
	evolutionMenu->addChild(stopEvolutionItem);

	// Browse history
	CEGUI::Window *browseHistoryItem = wmgr.createWindow("Ogremonics/MenuItem",
			"browseHistoryItem");
	browseHistoryItem->setText("Browse History");
	evolutionMenu->addChild(browseHistoryItem);

	//#####################
	//Environment menu
	CEGUI::Window *environmentTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"environmentTopItem");
	environmentTopItem->setText("Environment");
	menuBar->addChild(environmentTopItem);
	CEGUI::Window *environmentMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"evolutionMenu");
	environmentTopItem->addChild(environmentMenu);

	// Hills...
	CEGUI::Window *hillsItem = wmgr.createWindow("Ogremonics/MenuItem",
			"hillsItem");
	hillsItem->setText("Hills...");
	environmentMenu->addChild(hillsItem);

	// Opensea
	CEGUI::Window *openSeaItem = wmgr.createWindow("Ogremonics/MenuItem",
			"openSeaItem");
	openSeaItem->setText("Open Sea");
	environmentMenu->addChild(openSeaItem);

	// Plane
	CEGUI::Window *planeItem = wmgr.createWindow("Ogremonics/MenuItem",
			"planeItem");
	planeItem->setText("Plane");
	environmentMenu->addChild(planeItem);

	//#####################
	//Population menu
	CEGUI::Window *populationTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"populationTopItem");
	populationTopItem->setText("Population");
	menuBar->addChild(populationTopItem);
	CEGUI::Window *populationMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"populationMenu");
	populationTopItem->addChild(populationMenu);

	// New Population
	CEGUI::Window *newPopulationItem = wmgr.createWindow("Ogremonics/MenuItem",
			"newPopulationItem");
	newPopulationItem->setText("New Population");
	populationMenu->addChild(newPopulationItem);

	// Open Population...
	CEGUI::Window *openPopulationItem = wmgr.createWindow("Ogremonics/MenuItem",
			"openPopulationItem");
	openPopulationItem->setText("Open Population");
	populationMenu->addChild(openPopulationItem);

	// Save population as...
	CEGUI::Window *savePopulationAsItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "savePopulationAsItem");
	savePopulationAsItem->setText("Save Population as...");
	populationMenu->addChild(savePopulationAsItem);

	// Close population
	CEGUI::Window *closePopulationItem = wmgr.createWindow("Ogremonics/MenuItem",
			"closePopulationItem");
	closePopulationItem->setText("Close Population");
	populationMenu->addChild(closePopulationItem);

	//#####################
	//Creature menu
	CEGUI::Window *creatureTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"creatureTopItem");
	creatureTopItem->setText("Creature");
	menuBar->addChild(creatureTopItem);
	CEGUI::Window *creatureMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"creatureMenu");
	creatureTopItem->addChild(creatureMenu);

	// New random creature
	CEGUI::Window *newCreatureItem = wmgr.createWindow("Ogremonics/MenuItem",
			"newCreatureItem");
	newCreatureItem->setText("New Random Creature [F5]");
	creatureMenu->addChild(newCreatureItem);

	// Open creature...
	CEGUI::Window *openCreatureItem = wmgr.createWindow("Ogremonics/MenuItem",
			"openCreatureItem");
	openCreatureItem->setText("Open Creature...");
	creatureMenu->addChild(openCreatureItem);

	// Save creature as...
	CEGUI::Window *saveCreatureAsItem = wmgr.createWindow("Ogremonics/MenuItem",
			"saveCreatureAsItem");
	saveCreatureAsItem->setText("Save Creature As...");
	creatureMenu->addChild(saveCreatureAsItem);

	// Close creature
	CEGUI::Window *closeCreatureItem = wmgr.createWindow("Ogremonics/MenuItem",
			"closeCreatureItem");
	closeCreatureItem->setText("Close Creature");
	creatureMenu->addChild(closeCreatureItem);

	// Record frames
	CEGUI::Window *recordFramesItem = wmgr.createWindow("Ogremonics/MenuItem",
			"recordFramesItem");
	recordFramesItem->setText("Record Frames [CTRL+R]");
	creatureMenu->addChild(recordFramesItem);

	//#####################
	//Spawn menu
	CEGUI::Window *spawnTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"spawnTopItem");
	spawnTopItem->setText("Spawn");
	menuBar->addChild(spawnTopItem);
	CEGUI::Window *spawnMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"spawnMenu");
	spawnTopItem->addChild(spawnMenu);

	// spawn Box
	CEGUI::Window *spawnBoxItem = wmgr.createWindow("Ogremonics/MenuItem",
			"quitItem");
	spawnBoxItem->setText("Box [2]");
	spawnMenu->addChild(spawnBoxItem);

	// spawn Sphere
	CEGUI::Window *spawnSphereItem = wmgr.createWindow("Ogremonics/MenuItem",
			"spawnSphereItem");
	spawnSphereItem->setText("Sphere [3]");
	spawnMenu->addChild(spawnSphereItem);

	// spawn Capsule
	CEGUI::Window *spawnCapsuleItem = wmgr.createWindow("Ogremonics/MenuItem",
			"spawnCapsuleItem");
	spawnCapsuleItem->setText("Capsule [6]");
	spawnMenu->addChild(spawnCapsuleItem);

	//#####################
	// Action menu
	CEGUI::Window *actionTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"actionTopItem");
	actionTopItem->setText("Action");
	menuBar->addChild(actionTopItem);
	CEGUI::Window *actionMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"fileMenu");
	actionTopItem->addChild(actionMenu);

	// Return to origin
	CEGUI::Window *returnToOriginItem = wmgr.createWindow("Ogremonics/MenuItem",
			"returnToOriginItem");
	returnToOriginItem->setText("Return to Origin [K]");
	actionMenu->addChild(returnToOriginItem);

	//#####################
	//Settings menu
	CEGUI::Window *settingsTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"settingsTopItem");
	settingsTopItem->setText("Settings");
	menuBar->addChild(settingsTopItem);
	CEGUI::Window *settingsMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"settingsMenu");
	settingsTopItem->addChild(settingsMenu);

	// Evolution menu
	CEGUI::Window *evolutionSettingsTopItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "evolutionSettingsTopItem");
	evolutionSettingsTopItem->setText("Evolution");
	settingsMenu->addChild(evolutionSettingsTopItem);
	CEGUI::Window *evolutionSettingsMenu = wmgr.createWindow(
			"Ogremonics/PopupMenu", "evolutionSettingsMenu");
	evolutionSettingsTopItem->addChild(evolutionSettingsMenu);

	//Population menu
	CEGUI::Window *populationSettingsTopItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "populationSettingsTopItem");
	populationSettingsTopItem->setText("Population");
	settingsMenu->addChild(populationSettingsTopItem);
	CEGUI::Window *populationSettingsMenu = wmgr.createWindow(
			"Ogremonics/PopupMenu", "populationSettingsMenu");
	populationSettingsTopItem->addChild(populationSettingsMenu);

	// Population size
	CEGUI::Window *populationSizeItem = wmgr.createWindow("Ogremonics/MenuItem",
			"populationSizeItem");
	populationSizeItem->setText("Population Size...");
	populationSettingsMenu->addChild(populationSizeItem);

	// Selection style
	CEGUI::Window *selectionStyleItem = wmgr.createWindow("Ogremonics/MenuItem",
			"selectionStyleItem");
	selectionStyleItem->setText("Selection Style...");
	populationSettingsMenu->addChild(selectionStyleItem);

	// Creature
	CEGUI::Window *creatureSettingsTopItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "creatureSettingsTopItem");
	creatureSettingsTopItem->setText("Creature");
	settingsMenu->addChild(creatureSettingsTopItem);
	CEGUI::Window *creatureSettingsMenu = wmgr.createWindow(
			"Ogremonics/PopupMenu", "creatureSettingsMenu");
	creatureSettingsTopItem->addChild(creatureSettingsMenu);

	// Rendering
	CEGUI::Window *renderingTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"renderingTopItem");
	renderingTopItem->setText("Rendering");
	settingsMenu->addChild(renderingTopItem);

	// Rendering menu
	CEGUI::Window *renderingMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"renderingMenu");
	renderingTopItem->addChild(renderingMenu);

	// Shadows on/off
	CEGUI::Window *shadowsItem = wmgr.createWindow("Ogremonics/MenuItem",
			"shadowsItem");
	shadowsItem->setText("Shadows on/off [H]");
	renderingMenu->addChild(shadowsItem);

	// Fog on/off
	CEGUI::Window *fogItem = wmgr.createWindow("Ogremonics/MenuItem", "fogItem");
	fogItem->setText("Fog on/off [F]");
	renderingMenu->addChild(fogItem);

	// Skybox on/off
	CEGUI::Window *skyboxItem = wmgr.createWindow("Ogremonics/MenuItem",
			"skyboxItem");
	skyboxItem->setText("Skybox on/off [B]");
	renderingMenu->addChild(skyboxItem);

	// Greenscreen on/off
	CEGUI::Window *greenscreenItem = wmgr.createWindow("Ogremonics/MenuItem",
			"greenscreenItem");
	greenscreenItem->setText("Greenscreen on/off");
	renderingMenu->addChild(greenscreenItem);

	// Status on/off
	CEGUI::Window *statusItem = wmgr.createWindow("Ogremonics/MenuItem",
			"statusItem");
	statusItem->setText("Status on/off");
	renderingMenu->addChild(statusItem);

	// Polygon mode
	CEGUI::Window *polygonModeTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"polygonModeTopItem");
	polygonModeTopItem->setText("Polygon mode");
	renderingMenu->addChild(polygonModeTopItem);

	// Polygon mode menu
	CEGUI::Window *polygonModeMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"polygonModeMenu");
	polygonModeTopItem->addChild(polygonModeMenu);

	// Solid
	CEGUI::Window *solidModeItem = wmgr.createWindow("Ogremonics/MenuItem",
			"solidModeItem");
	solidModeItem->setText("Solid mode");
	polygonModeMenu->addChild(solidModeItem);

	// Wireframe
	CEGUI::Window *wireframeModeItem = wmgr.createWindow("Ogremonics/MenuItem",
			"wireframeModeItem");
	wireframeModeItem->setText("Wireframe mode");
	polygonModeMenu->addChild(wireframeModeItem);

	// Ambient light
	CEGUI::Window *ambientLightTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLightTopItem");
	ambientLightTopItem->setText("Ambient light");
	renderingMenu->addChild(ambientLightTopItem);

	// Ambient light menu
	CEGUI::Window *ambientLightMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"ambientLightMenu");
	ambientLightTopItem->addChild(ambientLightMenu);

	// 0 %
	CEGUI::Window *ambientLight0Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight0Item");
	ambientLight0Item->setText("0 %");
	ambientLightMenu->addChild(ambientLight0Item);

	// 10 %
	CEGUI::Window *ambientLight10Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight10Item");
	ambientLight10Item->setText("10 %");
	ambientLightMenu->addChild(ambientLight10Item);

	// 20 %
	CEGUI::Window *ambientLight20Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight20Item");
	ambientLight20Item->setText("20 %");
	ambientLightMenu->addChild(ambientLight20Item);

	// 30 %
	CEGUI::Window *ambientLight30Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight30Item");
	ambientLight30Item->setText("30 %");
	ambientLightMenu->addChild(ambientLight30Item);

	// 40 %
	CEGUI::Window *ambientLight40Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight40Item");
	ambientLight40Item->setText("40 %");
	ambientLightMenu->addChild(ambientLight40Item);

	// 50 %
	CEGUI::Window *ambientLight50Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight50Item");
	ambientLight50Item->setText("50 %");
	ambientLightMenu->addChild(ambientLight50Item);

	// 60 %
	CEGUI::Window *ambientLight60Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight60Item");
	ambientLight60Item->setText("60 %");
	ambientLightMenu->addChild(ambientLight60Item);

	// 70 %
	CEGUI::Window *ambientLight70Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight70Item");
	ambientLight70Item->setText("70 %");
	ambientLightMenu->addChild(ambientLight70Item);

	// 80 %
	CEGUI::Window *ambientLight80Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight80Item");
	ambientLight80Item->setText("80 %");
	ambientLightMenu->addChild(ambientLight80Item);

	// 90 %
	CEGUI::Window *ambientLight90Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight90Item");
	ambientLight90Item->setText("90 %");
	ambientLightMenu->addChild(ambientLight90Item);

	// 100 %
	CEGUI::Window *ambientLight100Item = wmgr.createWindow("Ogremonics/MenuItem",
			"ambientLight100Item");
	ambientLight100Item->setText("100 %");
	ambientLightMenu->addChild(ambientLight100Item);

	// Tune for speed
	CEGUI::Window *tuneForSpeedItem = wmgr.createWindow("Ogremonics/MenuItem",
			"tuneForSpeedItem");
	tuneForSpeedItem->setText("Tune for Speed [Keypad -]");
	renderingMenu->addChild(tuneForSpeedItem);

	// Tune for quality
	CEGUI::Window *tuneForQualityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"tuneForQualityItem");
	tuneForQualityItem->setText("Tune for Quality [Keypad +]");
	renderingMenu->addChild(tuneForQualityItem);

	// Movement
	CEGUI::Window *movementTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"movementTopItem");
	movementTopItem->setText("Movement");
	settingsMenu->addChild(movementTopItem);

	// Movement menu
	CEGUI::Window *movementMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"movementMenu");
	movementTopItem->addChild(movementMenu);

	// Speed 1
	CEGUI::Window *speed1Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed1Item");
	speed1Item->setText("Speed 1 [ALT-1]");
	movementMenu->addChild(speed1Item);

	// Speed 2
	CEGUI::Window *speed2Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed2Item");
	speed2Item->setText("Speed 2 [ALT-2]");
	movementMenu->addChild(speed2Item);

	// Speed 3
	CEGUI::Window *speed3Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed3Item");
	speed3Item->setText("Speed 3 [ALT-3]");
	movementMenu->addChild(speed3Item);

	// Speed 4
	CEGUI::Window *speed4Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed4Item");
	speed4Item->setText("Speed 4 [ALT-4]");
	movementMenu->addChild(speed4Item);

	// Speed 5
	CEGUI::Window *speed5Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed5Item");
	speed5Item->setText("Speed 5 [ALT-5]");
	movementMenu->addChild(speed5Item);

	// Speed 6
	CEGUI::Window *speed6Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed6Item");
	speed6Item->setText("Speed 6 [ALT-6]");
	movementMenu->addChild(speed6Item);

	// Speed 7
	CEGUI::Window *speed7Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed7Item");
	speed7Item->setText("Speed 7 [ALT-7]");
	movementMenu->addChild(speed7Item);

	// Speed 8
	CEGUI::Window *speed8Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed8Item");
	speed8Item->setText("Speed 8 [ALT-8]");
	movementMenu->addChild(speed8Item);

	// Speed 9
	CEGUI::Window *speed9Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed9Item");
	speed9Item->setText("Speed 9 [ALT-9]");
	movementMenu->addChild(speed9Item);

	// Speed 10
	CEGUI::Window *speed10Item = wmgr.createWindow("Ogremonics/MenuItem",
			"speed10Item");
	speed10Item->setText("Speed 10 [ALT-10]");
	movementMenu->addChild(speed10Item);

	// Physics
	CEGUI::Window *physicsTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"physicsTopItem");
	physicsTopItem->setText("Physics");
	settingsMenu->addChild(physicsTopItem);

	// Physics menu
	CEGUI::Window *physicsMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"physicsMenu");
	physicsTopItem->addChild(physicsMenu);

	// Pause simulation
	CEGUI::Window *pauseSimulationItem = wmgr.createWindow("Ogremonics/MenuItem",
			"pauseSimulationItem");
	pauseSimulationItem->setText("Pause Simulation");
	physicsMenu->addChild(pauseSimulationItem);

	// gravity
	CEGUI::Window *gravityTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"gravityTopItem");
	gravityTopItem->setText("Gravity");
	physicsMenu->addChild(gravityTopItem);

	//gravity menu
	CEGUI::Window *gravityMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"gravityMenu");
	gravityTopItem->addChild(gravityMenu);

	// No gravity
	CEGUI::Window *noGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"noGravityItem");
	noGravityItem->setText("No Gravity");
	gravityMenu->addChild(noGravityItem);

	// Pluto gravity 0.059
	CEGUI::Window *plutoGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"plutoGravityItem");
	plutoGravityItem->setText("Pluto Gravity 0.059 g");
	gravityMenu->addChild(plutoGravityItem);

	// Moon gravity 0.166
	CEGUI::Window *moonGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"moonGravityItem");
	moonGravityItem->setText("Moon Gravity 0.166 g");
	gravityMenu->addChild(moonGravityItem);

	// Mars/Mercury gravity 0.377/0.378
	CEGUI::Window *marsMercuryGravityItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "marsMercuryGravityItem");
	marsMercuryGravityItem->setText("Mars/Mercury Gravity 0.377 g");
	gravityMenu->addChild(marsMercuryGravityItem);

	// Uranus gravity 0.889
	CEGUI::Window *uranusGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"uranusGravityItem");
	uranusGravityItem->setText("Uranus Gravity 0.899 g");
	gravityMenu->addChild(uranusGravityItem);

	// Venus/Saturn gravity 0.907/0.916
	CEGUI::Window *venusSaturnGravityItem = wmgr.createWindow(
			"Ogremonics/MenuItem", "venusSaturnGravityItem");
	venusSaturnGravityItem->setText("Venus/Saturn Gravity 0.91 g");
	gravityMenu->addChild(venusSaturnGravityItem);

	// Earth gravity 1
	CEGUI::Window *earthGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"earthGravityItem");
	earthGravityItem->setText("Earth Gravity 1 g");
	gravityMenu->addChild(earthGravityItem);

	// Neptune gravity 1.12
	CEGUI::Window *neptuneGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"neptuneGravityItem");
	neptuneGravityItem->setText("Neptune Gravity 1.12 g");
	gravityMenu->addChild(neptuneGravityItem);

	// Jupiter gravity 2.36
	CEGUI::Window *jupiterGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"jupiterGravityItem");
	jupiterGravityItem->setText("Jupiter Gravity 2.36 g");
	gravityMenu->addChild(jupiterGravityItem);

	// Sun gravity 27.930682977
	CEGUI::Window *sunGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"sunGravityItem");
	sunGravityItem->setText("Sun Gravity 27.9 g");
	gravityMenu->addChild(sunGravityItem);

	// Custom gravity...
	CEGUI::Window *customGravityItem = wmgr.createWindow("Ogremonics/MenuItem",
			"customGravityItem");
	customGravityItem->setText("Custom Gravity");
	gravityMenu->addChild(customGravityItem);

	//#####################
	// Help menu
	CEGUI::Window *helpTopItem = wmgr.createWindow("Ogremonics/MenuItem",
			"helpTopItem");
	helpTopItem->setText("Help");
	menuBar->addChild(helpTopItem);
	CEGUI::Window *helpMenu = wmgr.createWindow("Ogremonics/PopupMenu",
			"helpMenu");
	helpTopItem->addChild(helpMenu);

	// About
	CEGUI::Window *aboutItem = wmgr.createWindow("Ogremonics/MenuItem",
			"aboutItem");
	aboutItem->setText("About");
	helpMenu->addChild(aboutItem);

	return menuBar;
}

ParamsPanel* CEGUIBuilder::createFpsPanel() {
	ParamsPanel::VectorStringPairs items;

	items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
	items.push_back(ParamsPanel::PairString("Run time", "0"));		// 1
	items.push_back(ParamsPanel::PairString("Info","Idle."));		// 2
	ParamsPanel* fpsPanel = ParamsPanel::createParamsPanel(CEGUI_INFOPANEL_BORDER,
			(int) mSimulationMgr->getWindow()->getHeight()
					- (3 * CEGUI_INFOPANEL_BORDER + CEGUI_INFOPANEL_CAPTION
							+ CEGUI_INFOPANEL_TEXT * items.size()), "FPS", 150,
			items);
	return fpsPanel;
}

ParamsPanel*CEGUIBuilder::createDetailsPanel() {
	ParamsPanel::VectorStringPairs items;

	items.push_back(ParamsPanel::PairString("cam.pX", "0"));		// 0
	items.push_back(ParamsPanel::PairString("cam.pY", "0"));		// 1
	items.push_back(ParamsPanel::PairString("cam.pZ", "0"));		// 2
	items.push_back(ParamsPanel::PairString("", ""));		// 3
	items.push_back(ParamsPanel::PairString("cam.oW", "0"));		// 4
	items.push_back(ParamsPanel::PairString("cam.oX", "0"));		// 5
	items.push_back(ParamsPanel::PairString("cam.oY", "0"));		// 6
	items.push_back(ParamsPanel::PairString("cam.oZ", "0"));		// 7
	items.push_back(ParamsPanel::PairString("", ""));		// 8
	items.push_back(ParamsPanel::PairString("Filtering", "None"));		// 9
	items.push_back(ParamsPanel::PairString("Poly Mode", "Solid"));		// 10
	ParamsPanel* detailsPanel = ParamsPanel::createParamsPanel(
			(int) mSimulationMgr->getWindow()->getWidth() - 200 - CEGUI_INFOPANEL_BORDER,
			CEGUI_INFOPANEL_BORDER * 4, "Debug", 200, items);
	detailsPanel->hide();
	return detailsPanel;
}
