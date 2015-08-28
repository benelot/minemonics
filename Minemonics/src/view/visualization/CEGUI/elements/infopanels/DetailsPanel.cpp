/*
 * DetailsPanel.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: leviathan
 */

#include <view/visualization/CEGUI/elements/infopanels/DetailsPanel.hpp>

DetailsPanel::DetailsPanel(const int left, const int top) :
ParamsPanel("Debug") {
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
	items.push_back(ParamsPanel::PairString("Filtering", "Anisotropic"));	// 9
	items.push_back(ParamsPanel::PairString("Poly Mode", "Solid"));		// 10

	ParamsPanel::initialize(left, top, 200, false, items);
}

DetailsPanel::~DetailsPanel() {
// TODO Auto-generated destructor stub
}

