#ifndef CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_
#define CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <vector>

//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/visualization/panels/MathGLPanel.hpp>

//## utils headers

class ParamsPanel;
namespace CEGUI {
class OgreRenderer;
} /* namespace CEGUI */


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

	void initialize(SimulationManager* simulationManager,Ogre::RenderTarget* renderTarget,StateHandler* stateHandler);

	void update(double timeSinceLastFrame);

	void updatePanels(Ogre::Real timeSinceLastFrame);

	void notifyDisplaySizeChanged(float width, float height);

	void updateMousePosition(float mousePositionX,float mousePositionY);

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

private:
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
};

#endif /* CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_ */
