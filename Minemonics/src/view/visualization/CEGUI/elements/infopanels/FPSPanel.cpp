/*
 * FPSPanel.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: leviathan
 */

#include <configuration/CEGUIConfiguration.hpp>
#include <OgreRenderWindow.h>
#include <SimulationManager.hpp>
#include <view/visualization/CEGUI/elements/infopanels/FPSPanel.hpp>
#include <string>
#include <utility>
#include <vector>

FPSPanel::FPSPanel(const int left, const int top) :
ParamsPanel("FPS") {
	ParamsPanel::VectorStringPairs items;

	items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
	items.push_back(ParamsPanel::PairString("Run time", "0"));		// 1
	items.push_back(ParamsPanel::PairString("Info", "Idle."));		// 2

	ParamsPanel::initialize(left, top, 180, false, items);
}

FPSPanel::~FPSPanel() {
	// TODO Auto-generated destructor stub
}

