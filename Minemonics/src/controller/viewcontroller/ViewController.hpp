#ifndef CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_
#define CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_

//# corresponding header
//# forward declarations
class MovablePanel;
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
#include <controller/viewcontroller/camera/CameraHandler.hpp>

//## model headers
//## view headers
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/visualization/CEGUI/MenuBar.hpp>
#include <view/visualization/CEGUI/infopanels/FPSPanel.hpp>
#include <view/visualization/CEGUI/infopanels/DetailsPanel.hpp>

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

	/**
	 * Initialize the view controller.
	 * @param renderTarget The render target.
	 * @param stateHandler The state handler of the simulation.
	 */
	void initialize(Ogre::RenderTarget* const renderTarget,
	StateHandler* const stateHandler);

	/**
	 * Update the view controller.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void update(const double timeSinceLastFrame);

	/**
	 * Update the panels.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void updatePanels(const Ogre::Real timeSinceLastFrame);

	/**
	 * Notify CEGUI that the display size has changed.
	 * @param width The new width.
	 * @param height The new height.
	 */
	void notifyDisplaySizeChanged(const float width, const float height);

	/**
	 * Update the mouse position.
	 * @param mousePositionX The new mouse position X.
	 * @param mousePositionY The new mouse position Y.
	 */
	void updateMousePosition(const float mousePositionX,
	const float mousePositionY);

	void addPlanetToView(Planet* planet);

	void removePlanetFromView(Planet* const planet);

	//Accessor methods
	DetailsPanel* const getDetailsPanel() const {
		return mDetailsPanel;
	}

	FPSPanel* const getFpsPanel() const {
		return mFpsPanel;
	}

	const InfoOverlay& getInfoOverlay() const {
		return mInfoOverlay;
	}

	CEGUI::OgreRenderer* const getRenderer() const {
		return mRenderer;
	}

	CEGUI::System* const getSystem() const {
		return mSystem;
	}

	Evaluation* const getEvaluationInView() const {
		return mEvaluationInView;
	}

	void setEvaluationInView(Evaluation* const evaluationInView) {
		mEvaluationInView = evaluationInView;
	}

	const std::vector<Planet*>& getPlanetsInView() const {
		return mPlanetsInView;
	}

	CameraHandler& getCameraHandler() {
		return mCameraHandler;
	}

	bool doesShowShadows() const {
		return mShowShadows;
	}

	void setShowShadows(bool showShadows) {
		mShowShadows = showShadows;
	}

	Planet* getSelectedPlanet() const {
		return mSelectedPlanet;
	}

	void setSelectedPlanet(Planet* selectedPlanet) {
		mSelectedPlanet = selectedPlanet;
	}

	std::vector<MovablePanel*>& getMovablePanels() {
		return mMovablePanels;
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
			boost::log::attributes::constant < std::string
			> ("ViewController"));
		}
	} _initializer;

	// CEGUI components
	CEGUI::System* mSystem;
	CEGUI::Window* mLayout;

	//SheetHandler
	GUISheetHandler mGUISheetHandler;

	//Camera Handler
	CameraHandler mCameraHandler;

	//CEGUI
	MenuBar* mMenuBar;
	FPSPanel* mFpsPanel;
	DetailsPanel* mDetailsPanel;
	CEGUI::OgreRenderer* mRenderer;
	CEGUI::Window* mDragContainer;

	// Visualization components
	std::vector<MovablePanel*> mMovablePanels;
	InfoOverlay mInfoOverlay;

	std::vector<Planet*> mPlanetsInView;
	Planet* mSelectedPlanet;
	Evaluation* mEvaluationInView;
	bool mShowShadows;
};

#endif /* CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_ */
