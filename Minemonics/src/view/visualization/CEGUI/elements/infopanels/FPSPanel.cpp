//# corresponding headers
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
#include <view/visualization/CEGUI/elements/infopanels/FPSPanel.hpp>
#include <view/visualization/CEGUI/elements/MovablePanel.hpp>

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
	// TODO Auto-generated destructor stub
}

