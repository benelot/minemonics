//# corresponding headers
#include <view/visualization/CEGUI/infopanels/FPSPanel.hpp>

//# forward declarations
//# system headers
#include <string>
#include <utility>
#include <vector>

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

FPSPanel::FPSPanel(const int left, const int top) :
ParamsPanel("FPS", MovablePanel::FPSPANEL) {
	ParamsPanel::VectorStringPairs items;

	items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
	items.push_back(ParamsPanel::PairString("Run time", "0"));		// 1
	items.push_back(ParamsPanel::PairString("Info", "Idle."));		// 2

	ParamsPanel::initialize(left, top, 180, false, items);
}

FPSPanel::~FPSPanel() {
	
}

