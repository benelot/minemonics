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
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/universe/evolution/population/Population.hpp>

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
	Population* population = new Population();
	population->setSerializationPath(boost::filesystem::path(filePath).parent_path().c_str());
	population->getPopulationModel()->setPlanetModel(SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getPlanetModel());
	population->load();

	// after loading we increase the generation by one and start evolving
	population->getPopulationModel()->setCurrentGeneration(population->getPopulationModel()->getCurrentGeneration()+1);
	SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->addPopulation(population);
	this->hide();
}
