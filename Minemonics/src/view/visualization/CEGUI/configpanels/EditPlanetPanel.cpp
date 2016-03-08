//# corresponding header
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
//## configuration headers
#include <configuration/CEGUIConfiguration.hpp>

//## controller headers
#include <controller/universe/environments/Environment.hpp>

//## model headers
#include <model/universe/evolution/EvolutionModel.hpp>

//## view headers
#include <view/visualization/CEGUI/elements/BoxSlider.hpp>
#include <view/visualization/CEGUI/configpanels/EditPlanetPanel.hpp>

//## utils headers

EditPlanetPanel::EditPlanetPanel(const int left, const int top,
	const std::string name) :
	MovablePanel(name, MovablePanel::EDIT_PLANET_PANEL), mEnvironmentTypeLabel(
	NULL) {
	int width = 600;
	int height = 600;

	float verticalOffset = 0.1f;
	float verticalStep = 0.2f;

	MovablePanel::initialize(left, top, width, height, false);

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

	float leftColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_LEFT_COL_WIDTH;
	float rightColWidth = CEGUIConfiguration::NEW_PLANET_PANEL_RIGHT_COL_WIDTH;

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
				CEGUI::UDim(verticalOffset, 0)));
		mEnvironmentTypeLabel->setText("Environment type: ");
		mBaseWidget->addChild(mEnvironmentTypeLabel);

		// Environment type Combobox
		mEnvironmentTypeCb = static_cast<CEGUI::Combobox*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Combobox"));
		mEnvironmentTypeCb->setReadOnly(true);
		CEGUI::ListboxTextItem* itemCombobox = new CEGUI::ListboxTextItem(
			"Plane", EnvironmentModel::PLANE);
		mEnvironmentTypeCb->addItem(itemCombobox);
		mEnvironmentTypeCb->setText(itemCombobox->getText()); // Copy the item's text into the Editbox
		mEnvironmentTypeCb->setItemSelectState(itemCombobox, true);
		itemCombobox = new CEGUI::ListboxTextItem("Hills",
			EnvironmentModel::HILLS);
		mEnvironmentTypeCb->addItem(itemCombobox);
		itemCombobox = new CEGUI::ListboxTextItem("Open Sea",
			EnvironmentModel::OPENSEA);
		mEnvironmentTypeCb->addItem(itemCombobox);

		mEnvironmentTypeCb->setWidth(CEGUI::UDim(0, rightColWidth * width));
		mEnvironmentTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalOffset, 0.0f)));
		mBaseWidget->addChild(mEnvironmentTypeCb);
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
				CEGUI::UDim(verticalStep * 1.0f + verticalOffset, 0)));
		mEvaluationTimeLabel->setText("Evaluation time: ");
		mBaseWidget->addChild(mEvaluationTimeLabel);

		mEvaluationTimeBs = new BoxSlider("EvaluationTimeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mEvaluationTimeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * 1.0f + verticalOffset, 0)));
		mBaseWidget->addChild(mEvaluationTimeBs);

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
				CEGUI::UDim(verticalStep * 2.0f + verticalOffset, 0)));
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

		mEvaluationTypeCb->setWidth(CEGUI::UDim(0, rightColWidth * width));
		mEvaluationTypeCb->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0.0f),
				CEGUI::UDim(verticalStep * 2.0f + verticalOffset, 0)));
		mEvaluationTypeCb->subscribeEvent(
			CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber(&EditPlanetPanel::onValueChanged, this));
		mBaseWidget->addChild(mEvaluationTypeCb);

		//	CEGUI::String valueCombobox = mEnvironmentTypeCb->getText(); // Retrieve the displayed text
		//	uint idCombobox = mEnvironmentTypeCb->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item

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
				CEGUI::UDim(verticalStep * 3.0f + verticalOffset, 0)));
		mTournamentSizeLabel->setText("Tournament size: ");
		mTournamentSizeLabel->hide();
		mBaseWidget->addChild(mTournamentSizeLabel);

		mTournamentSizeBs = new BoxSlider("TournamentSizeBoxSlider",
			rightColWidth * width, 100, 10, "[0-9]*");
		mTournamentSizeBs->setPosition(
			CEGUI::UVector2(CEGUI::UDim(leftColWidth, 0),
				CEGUI::UDim(verticalStep * 3.0f + verticalOffset, 0)));
		mTournamentSizeBs->hide();
		mBaseWidget->addChild(mTournamentSizeBs);

	}

	{
		/* Button */
		mConfirmButton = static_cast<CEGUI::PushButton*>(wmgr.createWindow(
			CEGUIConfiguration::CEGUI_SCHEME + "/Button"));
		mConfirmButton->setText("New Planet");
		mConfirmButton->setPosition(
			CEGUI::UVector2(
				CEGUI::UDim(leftColWidth + rightColWidth / 2.0f, 0.0f),
				CEGUI::UDim(verticalStep * 4.0f + verticalOffset, 0.0f)));
		mConfirmButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&EditPlanetPanel::onConfirmClicked, this));
		mBaseWidget->addChild(mConfirmButton);
	}
}

EditPlanetPanel::~EditPlanetPanel(void) {
	//Cleanup according to
	// http://cegui.org.uk/wiki/CEGUI_In_Practice_-_Introduction
	// http://cegui.org.uk/forum/viewtopic.php?t=1535
//	if (mEnvironmentTypeLabel) {
//		mBaseWidget->removeChild(mEnvironmentTypeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEnvironmentTypeLabel);
////		delete mEnvironmentTypeLabel;
//	}
//	mEnvironmentTypeLabel = NULL;
//
//	if (mEvaluationTimeLabel) {
//		mBaseWidget->removeChild(mEvaluationTimeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTimeLabel);
////		delete mEvaluationTimeLabel;
//	}
//	mEvaluationTimeLabel = NULL;
//
//	if (mEvaluationTypeLabel) {
//		mBaseWidget->removeChild(mEvaluationTypeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTypeLabel);
////		delete mEvaluationTypeLabel;
//	}
//	mEvaluationTypeLabel = NULL;
//
//	if (mTournamentSizeLabel) {
//		mBaseWidget->removeChild(mTournamentSizeLabel);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTournamentSizeLabel);
////		delete mTournamentSizeLabel;
//	}
//	mTournamentSizeLabel = NULL;
//
//	if (mEnvironmentTypeCb) {
//		mBaseWidget->removeChild(mEnvironmentTypeCb);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEnvironmentTypeCb);
////		delete mEnvironmentTypeCb;
//	}
//	mEnvironmentTypeCb = NULL;
//
//	if (mEvaluationTimeBs) {
//		mBaseWidget->removeChild(mEvaluationTimeBs);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTimeBs);
////		delete mEvaluationTimeBs;
//	}
//	mEvaluationTimeBs = NULL;
//
//	if (mEvaluationTypeCb) {
//		mBaseWidget->removeChild(mEvaluationTypeCb);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mEvaluationTypeCb);
////		delete mEvaluationTypeCb;
//	}
//	mEvaluationTypeCb = NULL;
//
//	if (mTournamentSizeBs) {
//		mBaseWidget->removeChild(mTournamentSizeBs);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mTournamentSizeBs);
////		delete mTournamentSizeBs;
//	}
//	mTournamentSizeBs = NULL;
//
//	if (mConfirmButton) {
//		mBaseWidget->removeChild(mConfirmButton);
//		CEGUI::WindowManager::getSingleton().destroyWindow(mConfirmButton);
////		delete mConfirmButton;
//	}
//	mConfirmButton = NULL;
}

void EditPlanetPanel::onValueChanged() {
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

void EditPlanetPanel::onConfirmClicked() {
	EnvironmentModel::EnvironmentType environmentType =
		(EnvironmentModel::EnvironmentType) mEnvironmentTypeCb->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item

	int evaluationTime = mEvaluationTimeBs->getCurrentValue();

	EvolutionModel::EvaluationType evaluationType =
		(EvolutionModel::EvaluationType) mEvaluationTypeCb->getSelectedItem()->getID(); // Retrieve the ID of the selected combobox item

	int tournamentSize = mTournamentSizeBs->getCurrentValue();
}
