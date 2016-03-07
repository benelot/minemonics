//# corresponding headers
#include <view/visualization/CEGUI/GUISheetHandler.hpp>

//# forward declarations
//# system headers
#include <stddef.h>

//## controller headers
//## model headers
#include <OgreColourValue.h>
#include <OgreSceneManager.h>
#include <boost/lexical_cast.hpp>

//## view headers
#include <CEGUI/Event.h>
#include <CEGUI/String.h>
#include <CEGUI/SubscriberSlot.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/Window.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/GUIConfiguration.hpp>
#include <configuration/PhysicsConfiguration.hpp>

//## controller headers
#include <controller/StateHandler.hpp>
#include <controller/universe/environments/Environment.hpp>
#include <controller/universe/Planet.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
#include <model/universe/environments/EnvironmentModel.hpp>
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
//## utils headers

BoostLogger GUISheetHandler::mBoostLogger; /*<! initialize the boost logger*/
GUISheetHandler::_Init GUISheetHandler::_initializer;
GUISheetHandler::GUISheetHandler() :
	mLayout(NULL) {

}

GUISheetHandler::~GUISheetHandler() {
	if (mLayout) {
		CEGUI::WindowManager::getSingleton().destroyWindow(mLayout);
	}
	mLayout = NULL;
}

void GUISheetHandler::initialize(CEGUI::Window* const layout) {
	mLayout = layout;

	// hook up the event handlers to the window elements
	{
		//#####################
		//File menu
		//File->Quit
		CEGUI::PushButton* quitButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::quitApplicationCmd);
		quitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
				this));
	}

	{
		//#####################
		//Evaluation menu
		//Evaluation->Evolution Track
		CEGUI::PushButton* evolutionTrackButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::setEvolutionTrackCmd);
		evolutionTrackButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				&GUISheetHandler::evolutionTrackButtonClicked, this));

		//Evaluation->Learning Track
		CEGUI::PushButton* learningTrackButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::setLearningTrackCmd);
		learningTrackButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				&GUISheetHandler::learningTrackButtonClicked, this));
	}

	{
		//#####################
		//Planet menu
		//Planets->New Planet
		CEGUI::PushButton* newPlanetButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::newPlanetCmd);
		newPlanetButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&GUISheetHandler::newPlanetButtonClicked,
				this));

		//Planets->Edit Planet
		CEGUI::PushButton* editPlanetButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::editPlanetCmd);
		editPlanetButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&GUISheetHandler::editPlanetButtonClicked,
				this));

		//Planets->Load Planet
		CEGUI::PushButton* loadPlanetButton =
			(CEGUI::PushButton*) mLayout->getChildRecursive(
				GUIConfiguration::loadPlanetCmd);
		loadPlanetButton->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&GUISheetHandler::loadPlanetButtonClicked,
				this));
	}

//Evolution->Open Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Evolution->Save Evolution as...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Close Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Run Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Pause Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Stop Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Browse History
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Evolution->New Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Evolution->Open Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Evolution->Save Evolution as...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Close Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Run Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Pause Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Stop Evolution
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Browse History
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Environment->Hills...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Environment->Deep Sea
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Environment->Plane
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

	{
		{
			//Population->New Population
			CEGUI::PushButton* newPopulationButton =
				(CEGUI::PushButton*) mLayout->getChildRecursive(
					GUIConfiguration::newPopulationCmd);
			newPopulationButton->subscribeEvent(CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(
					&GUISheetHandler::newPopulationButtonClicked, this));
		}

		{
			//Population->Edit Population
			CEGUI::PushButton* editPopulationButton =
				(CEGUI::PushButton*) mLayout->getChildRecursive(
					GUIConfiguration::editPopulationCmd);
			editPopulationButton->subscribeEvent(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(
					&GUISheetHandler::editPopulationButtonClicked, this));
		}

		{
			//Population->Load Population
			CEGUI::PushButton* loadPopulationButton =
				(CEGUI::PushButton*) mLayout->getChildRecursive(
					GUIConfiguration::loadPopulationCmd);
			loadPopulationButton->subscribeEvent(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(
					&GUISheetHandler::loadPopulationButtonClicked, this));
		}

		{
			//Population->Perturb Population
			CEGUI::PushButton* perturbPopulationButton =
				(CEGUI::PushButton*) mLayout->getChildRecursive(
					GUIConfiguration::perturbPopulationCmd);
			perturbPopulationButton->subscribeEvent(
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(
					&GUISheetHandler::perturbPopulationButtonClicked, this));
		}
	}

//Population->Save Population as...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Population->Close Population
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Creature->New Random Creature
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Creature->Open Creature...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Creature->Save Creature as...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Creature->Close Creature
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Creature->Record frames
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Spawn->Box
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Spawn->Sphere
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Spawn->Capsule
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Action->Return to Origin
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Population->Population Size...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Population->Selection Style...
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Shadows on/off
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Fog on/off
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitGUISheetHandlerButtonClicked,
//					this));

//Settings->Rendering->Skybox on/off
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Greenscreen on/off
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Status on/off
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));GUISheetHandler

//Settings->Rendering->Polygon mode->Solid mode
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Polygon mode->Wireframe mode
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Ambient light->0 %
	CEGUI::PushButton* pAmbientLight0Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight0Cmd);
	pAmbientLight0Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight0ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->10 %
	CEGUI::PushButton* pAmbientLight10Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight10Cmd);
	pAmbientLight10Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight10ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->20 %
	CEGUI::PushButton* pAmbientLight20Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight20Cmd);
	pAmbientLight20Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight20ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->30 %
	CEGUI::PushButton* pAmbientLight30Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight30Cmd);
	pAmbientLight30Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight30ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->40 %
	CEGUI::PushButton* pAmbientLight40Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight40Cmd);
	pAmbientLight40Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight40ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->50 %
	CEGUI::PushButton* pAmbientLight50Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight50Cmd);
	pAmbientLight50Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight50ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->60 %
	CEGUI::PushButton* pAmbientLight60Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight60Cmd);
	pAmbientLight60Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight60ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->70 %
	CEGUI::PushButton* pAmbientLight70Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight70Cmd);
	pAmbientLight70Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight70ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->80 %
	CEGUI::PushButton* pAmbientLight80Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight80Cmd);
	pAmbientLight80Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight80ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->90 %
	CEGUI::PushButton* pAmbientLight90Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight90Cmd);
	pAmbientLight90Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight90ButtonClicked,
			this));

	//Settings->Rendering->Ambient light->100 %
	CEGUI::PushButton* pAmbientLight100Button =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::ambientLight100Cmd);
	pAmbientLight100Button->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::ambientlight100ButtonClicked,
			this));

	//Settings->Rendering->Tune for Speed
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Rendering->Tune for Quality
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 1
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 2
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 3
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 4
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 5
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 6
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 7
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 8
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 9
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Movement->Speed 10
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Physics->Pause Simulation
//	CEGUI::PushButton* pQuitButton =
//			(CEGUI::PushButton *) mWindow->getChildRecursive(
//					"cmdQuitApplication");
//	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked,
//			CEGUI::Event::Subscriber(&GUISheetHandler::quitButtonClicked,
//					this));

//Settings->Physics->Gravity->No Gravity
	CEGUI::PushButton* pNoGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::noGravityCmd);
	pNoGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::noGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Pluto Gravity
	CEGUI::PushButton* pPlutoGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive("cmdPlutoGravity");
	pPlutoGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::plutoGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Moon Gravity
	CEGUI::PushButton* pMoonGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::moonGravityCmd);
	pMoonGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::moonGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Mars Gravity
	CEGUI::PushButton* pMarsMercuryGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::marsMercuryGravityCmd);
	pMarsMercuryGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(
			&GUISheetHandler::marsMercuryGravityButtonClicked, this));

	//Settings->Physics->Gravity->Uranus Gravity
	CEGUI::PushButton* pUranusGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::uranusGravityCmd);
	pUranusGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::uranusGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Venus/Saturn Gravity
	CEGUI::PushButton* pVenusSaturnGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::venusSaturnGravityCmd);
	pVenusSaturnGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(
			&GUISheetHandler::venusSaturnGravityButtonClicked, this));

	//Settings->Physics->Gravity->Earth Gravity
	CEGUI::PushButton* pEarthGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::earthGravityCmd);
	pEarthGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::earthGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Neptune Gravity
	CEGUI::PushButton* pNeptuneGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::neptuneGravityCmd);
	pNeptuneGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::neptuneGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Jupiter Gravity
	CEGUI::PushButton* pJupiterGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::jupiterGravityCmd);
	pJupiterGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::jupiterGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Sun Gravity
	CEGUI::PushButton* pSunGravityButton =
		(CEGUI::PushButton *) mLayout->getChildRecursive(
			GUIConfiguration::sunGravityCmd);
	pSunGravityButton->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&GUISheetHandler::sunGravityButtonClicked,
			this));

	//Settings->Physics->Gravity->Custom Gravity

	//About->Help
}

//File->Quit
bool GUISheetHandler::quitButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SHUTDOWN);
	return true;
}

//Evaluation->Evolution Track
bool GUISheetHandler::evolutionTrackButtonClicked(
	const CEGUI::EventArgs& args) {
	return true;
}

//Evaluation->Learning Track
bool GUISheetHandler::learningTrackButtonClicked(const CEGUI::EventArgs& args) {
	return true;
}

//Planets->New Planet
bool GUISheetHandler::newPlanetButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setNewPlanetWindowVisibility(
		true);
	return true;
}

//Planets->Edit Planet
bool GUISheetHandler::editPlanetButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setEditPlanetWindowVisibility(
		true);
	return true;
}

//Planets->Load Planet
bool GUISheetHandler::loadPlanetButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setLoadPlanetWindowVisibility(
		true);
	return true;
}

//Evolution->New Evolution
bool GUISheetHandler::newEvolutionButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Evolution->Open Evolution
bool GUISheetHandler::openEvolutionButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Evolution->Save Evolution as...
bool GUISheetHandler::saveEvolutionAsButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Close Evolution
bool GUISheetHandler::closeEvolutionButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Run Evolution
bool GUISheetHandler::runEvolutionButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Pause Evolution
bool GUISheetHandler::pauseEvolutionButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Stop Evolution
bool GUISheetHandler::stopEvolutionButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Browse History
bool GUISheetHandler::browseHistoryButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Environment->Hills...
bool GUISheetHandler::hillsButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Environment->Open Sea
bool GUISheetHandler::openSeaButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Environment->Plane
bool GUISheetHandler::planeButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Population->New Population
bool GUISheetHandler::newPopulationButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setNewPopulationWindowVisibility(
		true);
	return true;
}

//Population->Edit Population
bool GUISheetHandler::editPopulationButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setEditPopulationWindowVisibility(
		true);
	return true;
}

//Population->Load Population
bool GUISheetHandler::loadPopulationButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setLoadPopulationWindowVisibility(
		true);
	return true;
}

//Population->perturb Population
bool GUISheetHandler::perturbPopulationButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->perturbPopulations();
	return true;
}

//Population->Save Population as...
bool GUISheetHandler::savePopulationAsButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Population->Close Population
bool GUISheetHandler::closePopulationButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Creature->New Random Creature
bool GUISheetHandler::newCreatureButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Creature->Open Creature...
bool GUISheetHandler::openCreatureButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Creature->Save Creature as...
bool GUISheetHandler::saveCreatureAsButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Creature->Close Creature
bool GUISheetHandler::closeCreatureButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Creature->Record frames
bool GUISheetHandler::recordFramesButtonClicked(const CEGUI::EventArgs &args) {
	switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
	case StateHandler::SIMULATION: {
		if (SimulationManager::getSingleton()->getVideoWriter().isInitialized()) {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Recording video stopped.";
			SimulationManager::getSingleton()->getVideoWriter().close();
		} else {
			// create video file name
			std::string videoName;
			videoName.append("Minemonics-");
			videoName.append(
				boost::lexical_cast<std::string>(
					SimulationManager::getSingleton()->getNow()));
			videoName.append(".mp4");

			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "Recording video started.";

			//This even works on if the screen gets resized
			SimulationManager::getSingleton()->getVideoWriter().setup(
				videoName.c_str(),
				SimulationManager::getSingleton()->getWindow()->getWidth(),
				SimulationManager::getSingleton()->getWindow()->getHeight());
		}
		break;
	}
	default: {
		break;
	}
}
return true;
}

//Spawn->Box
bool GUISheetHandler::spawnBoxButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Spawn->Sphere
bool GUISheetHandler::spawnSphereButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Spawn->Capsule
bool GUISheetHandler::spawnCapsuleButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Action->Return to Origin
bool GUISheetHandler::returnToOriginButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Population->Population Size...
bool GUISheetHandler::populationSizeButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Population->Selection Style...
bool GUISheetHandler::selectionStyleButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Shadows on/off
bool GUISheetHandler::shadowsButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getViewController().setShowShadows(
		!SimulationManager::getSingleton()->getViewController().doesShowShadows());
	return true;
}

//Settings->Rendering->Fog on/off
bool GUISheetHandler::fogButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Skybox on/off
bool GUISheetHandler::skyboxButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Greenscreen on/off
bool GUISheetHandler::greenscreenButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Status on/off
bool GUISheetHandler::statusButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Polygon mode->Solid mode
bool GUISheetHandler::solidButtonClicked(const CEGUI::EventArgs &args) {
	Ogre::PolygonMode pm = Ogre::PM_SOLID;

	SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera()->setPolygonMode(
		pm);

	return true;
}

//Settings->Rendering->Polygon mode->Wireframe mode
bool GUISheetHandler::wireframeButtonClicked(const CEGUI::EventArgs &args) {

	Ogre::PolygonMode pm = Ogre::PM_WIREFRAME;

	SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera()->setPolygonMode(
		pm);

	return true;
}

//Settings->Rendering->Ambient light->0 %
bool GUISheetHandler::ambientlight0ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0, 0, 0));
	return true;
}

//Settings->Rendering->Ambient light->10 %
bool GUISheetHandler::ambientlight10ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.1, 0.1, 0.05));
	return true;
}

//Settings->Rendering->Ambient light->20 %
bool GUISheetHandler::ambientlight20ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.2, 0.2, 0.15));
	return true;
}

//Settings->Rendering->Ambient light->30 %
bool GUISheetHandler::ambientlight30ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.3, 0.3, 0.25));
	return true;
}

//Settings->Rendering->Ambient light->40 %
bool GUISheetHandler::ambientlight40ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.4, 0.4, 0.35));
	return true;
}

//Settings->Rendering->Ambient light->50 %
bool GUISheetHandler::ambientlight50ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.5, 0.5, 0.45));
	return true;
}

//Settings->Rendering->Ambient light->60 %
bool GUISheetHandler::ambientlight60ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.6, 0.6, 0.55));
	return true;
}

//Settings->Rendering->Ambient light->70 %
bool GUISheetHandler::ambientlight70ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.7, 0.7, 0.65));
	return true;
}

//Settings->Rendering->Ambient light->80 %
bool GUISheetHandler::ambientlight80ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.8, 0.8, 0.75));
	return true;
}

//Settings->Rendering->Ambient light->90 %
bool GUISheetHandler::ambientlight90ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(0.9, 0.9, 0.85));
	return true;
}

//Settings->Rendering->Ambient light->100 %
bool GUISheetHandler::ambientlight100ButtonClicked(
	const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getSceneManager()->setAmbientLight(
		Ogre::ColourValue(1.0, 1.0, 0.95));
	return true;
}

//Settings->Rendering->Tune for Speed
bool GUISheetHandler::tuneForSpeedButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Rendering->Tune for Quality
bool GUISheetHandler::tuneForQualityButtonClicked(
	const CEGUI::EventArgs &args) {
	return true;
}

//Settings->Movement->Speed 1
bool GUISheetHandler::speed1ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_01);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_01]);
	return true;
}

//Settings->Movement->Speed 2
bool GUISheetHandler::speed2ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_02);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_02]);
	return true;
}

//Settings->Movement->Speed 3
bool GUISheetHandler::speed3ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_03);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_03]);
	return true;
}

//Settings->Movement->Speed 4
bool GUISheetHandler::speed4ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_04);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_04]);
	return true;
}

//Settings->Movement->Speed 5
bool GUISheetHandler::speed5ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_05);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_05]);
	return true;
}

//Settings->Movement->Speed 6
bool GUISheetHandler::speed6ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_06);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_06]);
	return true;
}

//Settings->Movement->Speed 7
bool GUISheetHandler::speed7ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_07);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_07]);
	return true;
}

//Settings->Movement->Speed 8
bool GUISheetHandler::speed8ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_08);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_08]);
	return true;
}

//Settings->Movement->Speed 9
bool GUISheetHandler::speed9ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_09);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_09]);
	return true;
}

//Settings->Movement->Speed 10
bool GUISheetHandler::speed10ButtonClicked(const CEGUI::EventArgs &args) {
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(
		StateHandler::SIMULATION);
	SimulationManager::getSingleton()->setCurrentSimulationSpeed(
		PhysicsConfiguration::SIMULATION_SPEED_10);
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Changed simulation speed to "
	<< pow(2,
		PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_10]);
	return true;
}

//Settings->Physics->Pause Simulation
bool GUISheetHandler::pauseSimulationButtonClicked(
	const CEGUI::EventArgs &args) {
	switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
	case StateHandler::SIMULATION: {
		SimulationManager::getSingleton()->getUniverse().getEvaluationController().setPaused(
			!SimulationManager::getSingleton()->getUniverse().getEvaluationController().isPaused());
		break;
	}
	default: {
		break;
	}
	}
	return true;
}

//Settings->Physics->Gravity->No Gravity
bool GUISheetHandler::noGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::NO_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Pluto Gravity
bool GUISheetHandler::plutoGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::PLUTO_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Moon Gravity
bool GUISheetHandler::moonGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::MOON_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Mars/Mercury Gravity
bool GUISheetHandler::marsMercuryGravityButtonClicked(
	const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::MARS_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Uranus Gravity
bool GUISheetHandler::uranusGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::URANUS_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Venus/Saturn Gravity
bool GUISheetHandler::venusSaturnGravityButtonClicked(
	const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::VENUS_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Earth Gravity
bool GUISheetHandler::earthGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::EARTH_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Neptune Gravity
bool GUISheetHandler::neptuneGravityButtonClicked(
	const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::NEPTUNE_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Jupiter Gravity
bool GUISheetHandler::jupiterGravityButtonClicked(
	const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::JUPITER_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Sun Gravity
bool GUISheetHandler::sunGravityButtonClicked(const CEGUI::EventArgs &args) {
	if (SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet() != NULL) {
		SimulationManager::getSingleton()->getStateHandler().getCurrentlySelectedPlanet()->getEnvironment()->getEnvironmentModel()->getPhysicsController()->setGravity(
			PhysicsConfiguration::SUN_GRAVITY);
	}
	return true;
}

//Settings->Physics->Gravity->Custom Gravity
bool GUISheetHandler::customGravityButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}

//About->Help
bool GUISheetHandler::helpButtonClicked(const CEGUI::EventArgs &args) {
	return true;
}
