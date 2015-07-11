#ifndef CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_
#define CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_

//# corresponding header
//# forward declarations
class ParamsPanel;
namespace CEGUI {
class OgreRenderer;
} /* namespace CEGUI */

//# system headers
#include <vector>

//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>
#include <controller/Evaluation.hpp>

//## model headers
//## view headers
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/visualization/panels/MathGLPanel.hpp>

//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The view controller handles the information panels of the application and what is currently in view..
 * @details		Details
 * @date		2015-05-27
 * @author		Benjamin Ellenberger
 */
class ViewController {
public:
	ViewController();
	virtual ~ViewController();

	void initialize(SimulationManager* simulationManager,
			Ogre::RenderTarget* renderTarget, StateHandler* stateHandler);

	void update(double timeSinceLastFrame);

	void updatePanels(Ogre::Real timeSinceLastFrame);

	void notifyDisplaySizeChanged(float width, float height);

	void updateMousePosition(float mousePositionX, float mousePositionY);

	//TODO: Implement the view controller to handle what planets are shown.
	void addPlanet(Planet* planet);

	//Accessor methods
	ParamsPanel* getDetailsPanel() {
		return mDetailsPanel;
	}

	ParamsPanel* getFpsPanel() {
		return mFpsPanel;
	}

	std::vector<MathGLPanel*>& getGraphWindows() {
		return mGraphWindows;
	}

	const InfoOverlay& getInfoOverlay() const {
		return mInfoOverlay;
	}

	CEGUI::OgreRenderer* getRenderer() {
		return mRenderer;
	}

	CEGUI::System* getSystem() {
		return mSystem;
	}

	Evaluation* getEvaluationInView() const {
		return mEvaluationInView;
	}

	void setEvaluationInView(Evaluation* evaluationInView) {
		mEvaluationInView = evaluationInView;
	}

private:
	/**
	 * The boost logger.
	 */
	static BoostLogger mBoostLogger;

	/**
	 * Initializer of the boost logger to include the class name into the logging messages.
	 */
	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"ViewController"));
		}
	} _initializer;

	// CEGUI components
	CEGUI::System* mSystem;
	CEGUI::Window* mLayout;

	//SheetHandler
	GUISheetHandler mGUISheetHandler;

	//CEGUI
	ParamsPanel* mFpsPanel;
	ParamsPanel* mDetailsPanel;
	CEGUI::OgreRenderer* mRenderer;
	CEGUI::Window* mDragContainer;

	// Visualization components
	std::vector<MathGLPanel*> mGraphWindows;
	InfoOverlay mInfoOverlay;

	std::vector<Planet*> mPlanetsInView;
	Evaluation* mEvaluationInView;
};

#endif /* CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_ */
