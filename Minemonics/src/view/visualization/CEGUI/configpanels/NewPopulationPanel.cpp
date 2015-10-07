//# corresponding header
#include <view/visualization/CEGUI/configpanels/NewPopulationPanel.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <string>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/Element.h>
#include <CEGUI/Singleton.h>
#include <CEGUI/UDim.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/Combobox.h>
#include <CEGUI/widgets/ListboxItem.h>
#include <CEGUI/widgets/ListboxTextItem.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/WindowManager.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>
#include <configuration/EvolutionConfiguration.hpp>

//## controller headers
#include <controller/universe/evolution/population/Population.hpp>

//## model headers
//## view headers
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>

//## utils headers

NewPopulationPanel::NewPopulationPanel(const int left, const int top,
	const std::string name) :
	MovablePanel(name, MovablePanel::NEW_POPULATION_PANEL) {

	int width = 600;
	int height = 600;

	float verticalOffset = 0.1f;
	float verticalStep = 0.16f;
	float i = 0;

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	float leftColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_LEFT_COL_WIDTH;
	float rightColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_RIGHT_COL_WIDTH;

	{
		// Population size
		mPopulationSizeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mPopulationSizeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mPopulationSizeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mPopulationSizeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mPopulationSizeLabel->setText("Population size: ");
		mBaseWidget->addChild(mPopulationSizeLabel);

		mPopulationSizeBs = new BoxSlider("PopulationSizeBoxSlider",
			rightColWidth * width, 100, 1000, "[0-9]*");
		mPopulationSizeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mBaseWidget->addChild(mPopulationSizeBs);
		i++;
	}

	{
		/* Button */
		mConfirmButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mConfirmButton->setText("Create");
		mConfirmButton->setSize(
			CEGUI::USize(CEGUI::UDim(0, 150), CEGUI::UDim(0, 20)));
		mConfirmButton->setPosition(
			CEGUI::UVector2(
				CEGUI::UDim(leftColWidth + rightColWidth / 1.5f, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mConfirmButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&NewPopulationPanel::onConfirmClicked,
				this));
		mBaseWidget->addChild(mConfirmButton);
	}
}

NewPopulationPanel::~NewPopulationPanel(void) {
}

void NewPopulationPanel::onConfirmClicked() {

	int populationSize = mPopulationSizeBs->getCurrentValue();

	Population* population = new Population();
	population->initialize(NULL, populationSize,
		EvolutionConfiguration::ROOT_POSITION);
	SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->addPopulation(
		population);
	close();
}
