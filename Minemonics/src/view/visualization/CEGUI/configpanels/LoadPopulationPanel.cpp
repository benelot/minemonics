//# corresponding header
#include <view/visualization/CEGUI/configpanels/LoadPopulationPanel.hpp>

//# system header
#include <stddef.h>
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

LoadPopulationPanel::LoadPopulationPanel(const int left, const int top,
	const std::string name) : FileDialog(left,
		top, name,MovablePanel::LOAD_PANEL)
{

}

LoadPopulationPanel::~LoadPopulationPanel(void) {
}

void LoadPopulationPanel::openFile(std::string filePath) {
}
