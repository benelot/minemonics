//# corresponding header
#include <view/visualization/CEGUI/configpanels/NewPlanetPanel.hpp>

//# forward declarations
//# system headers
#include <stddef.h>
#include <string>

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

//## controller headers
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/Planet.hpp>

//## model headers
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>

//## utils headers

NewPlanetPanel::NewPlanetPanel(const int left, const int top,
	const std::string name) :
	MovablePanel(name, MovablePanel::NEW_PLANET_PANEL), mEnvironmentTypeLabel(
		NULL) {
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
		// physics controller type
		mPhysicsControllerTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mPhysicsControllerTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mPhysicsControllerTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);

		mPhysicsControllerTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalOffset, 0)));
		mPhysicsControllerTypeLabel->setText("Physics Controller Type: ");
		mBaseWidget->addChild(mPhysicsControllerTypeLabel);

		// Physics Controller type Combobox
		mPhysicsControllerTypeCb =
			static_cast<CEGUI::Combobox*>(wmgr.createWindow(
				CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mPhysicsControllerTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"RigidBody Dynamicsworld", PhysicsController::RigidbodyModel);
		mPhysicsControllerTypeCb->addItem(itemCombobox);

		itemCombobox = new CEGUI::ListboxTextItem(
			"Featherstone MultiBody Dynamicsworld",
			PhysicsController::FeatherstoneModel);
		mPhysicsControllerTypeCb->addItem(itemCombobox);
		mPhysicsControllerTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mPhysicsControllerTypeCb->setItemSelectState(itemCombobox, true);
		mPhysicsControllerTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mPhysicsControllerTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mPhysicsControllerTypeCb);
		i++;
	}

	{
		// Environment type
		mEnvironmentTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEnvironmentTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEnvironmentTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);

		mEnvironmentTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEnvironmentTypeLabel->setText("Environment type: ");
		mBaseWidget->addChild(mEnvironmentTypeLabel);

		// Environment type Combobox
		mEnvironmentTypeCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mEnvironmentTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Plane", Environment::PLANE);
		mEnvironmentTypeCb->addItem(itemCombobox);
		mEnvironmentTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mEnvironmentTypeCb->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("Hills", Environment::HILLS);
		mEnvironmentTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("Open Sea",
			Environment::OPENSEA);
		mEnvironmentTypeCb->addItem(itemCombobox);

		mEnvironmentTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mEnvironmentTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0.0f)));
		mBaseWidget->addChild(mEnvironmentTypeCb);
		i++;
	}

	{
		// Evaluation time
		mEvaluationTimeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEvaluationTimeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEvaluationTimeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mEvaluationTimeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTimeLabel->setText("Evaluation time: ");
		mBaseWidget->addChild(mEvaluationTimeLabel);

		mEvaluationTimeBs = new BoxSlider("EvaluationTimeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mEvaluationTimeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mBaseWidget->addChild(mEvaluationTimeBs);
		i++;
	}

	{
		// Evaluation type
		mEvaluationTypeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mEvaluationTypeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mEvaluationTypeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mEvaluationTypeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTypeLabel->setText("Evaluation type: ");
		mBaseWidget->addChild(mEvaluationTypeLabel);

		// Evaluation type Combobox
		mEvaluationTypeCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mEvaluationTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Individual evaluation", EvolutionModel::INDIVIDUAL_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		mEvaluationTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mEvaluationTypeCb->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("N Individuals Tournament",
			EvolutionModel::N_INDIVIDUALS_TOURNAMENT_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("Whole Population Tournament",
			EvolutionModel::POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem(
			"N Individuals from each Population Tournament",
			EvolutionModel::N_POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("N Populations Tournament",
			EvolutionModel::N_POPULATION_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("All Populations Tournament",
			EvolutionModel::POPULATIONS_EVALUATION);
		mEvaluationTypeCb->addItem(itemCombobox);

		mEvaluationTypeCb->setSize(
			CEGUI::USize(CEGUI::UDim(0, rightColWidth * width),
				CEGUI::UDim(0, 200)));
		mEvaluationTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mEvaluationTypeCb->subscribeEvent(
			CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber(&NewPlanetPanel::onValueChanged, this));
		mBaseWidget->addChild(mEvaluationTypeCb);
		i++;
	}

	{
		// Tournament size
		mTournamentSizeLabel = wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Label");
		mTournamentSizeLabel->setSize(
			CEGUI::USize(CEGUI::UDim(0, leftColWidth * width),
				CEGUI::UDim(0, CEGUIConfiguration::INFOPANEL_TEXT_HEIGHT)));
		mTournamentSizeLabel->setHorizontalAlignment(CEGUI::HA_LEFT);
		mTournamentSizeLabel->setPosition(
			CEGUI::UVector2(CEGUI::UDim(0.0, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mTournamentSizeLabel->setText("Tournament size: ");
		mTournamentSizeLabel->hide();
		mBaseWidget->addChild(mTournamentSizeLabel);

		mTournamentSizeBs = new BoxSlider("TournamentSizeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mTournamentSizeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * i + verticalOffset, 0)));
		mTournamentSizeBs->hide();
		mBaseWidget->addChild(mTournamentSizeBs);
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
			CEGUI::Event::Subscriber(&NewPlanetPanel::onConfirmClicked, this));
		mBaseWidget->addChild(mConfirmButton);
	}
}

NewPlanetPanel::~NewPlanetPanel(void) {
}

void NewPlanetPanel::onValueChanged() {
	EvolutionModel::EvaluationType evaluationType =
		(EvolutionModel::EvaluationType) mEvaluationTypeCb->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item

	switch (evaluationType) {
	case EvolutionModel::INDIVIDUAL_EVALUATION:
	case EvolutionModel::POPULATION_EVALUATION:
	case EvolutionModel::POPULATIONS_EVALUATION:
		mTournamentSizeLabel->hide();
		mTournamentSizeBs->hide();
		break;
	default:
		mTournamentSizeLabel->show();
		mTournamentSizeBs->show();
		break;
	}
}

void NewPlanetPanel::onConfirmClicked() {
	PhysicsController::PhysicsModelType modelType =
		(PhysicsController::PhysicsModelType) mPhysicsControllerTypeCb->getID(); // Retrieve the model type

	Environment::EnvironmentType environmentType =
		(Environment::EnvironmentType) mEnvironmentTypeCb->getSelectedItem()->getID(); // Retrieve the environment type

	int evaluationTime = mEvaluationTimeBs->getCurrentValue();

	EvolutionModel::EvaluationType evaluationType =
		(EvolutionModel::EvaluationType) mEvaluationTypeCb->getSelectedItem()->getID(); // Retrieve the evaluation type

	//TODO: Tournament size is not used yet
	int tournamentSize = mTournamentSizeBs->getCurrentValue(); // Retrieve the tournament size

	SimulationManager::getSingleton()->getUniverse().addPlanet(
		new Planet(modelType, environmentType, evaluationTime));
	this->hide();
}
