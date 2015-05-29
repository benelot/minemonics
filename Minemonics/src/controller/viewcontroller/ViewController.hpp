/*
 * ViewController.hpp
 *
 *  Created on: May 27, 2015
 *      Author: leviathan
 */

#ifndef CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_
#define CONTROLLER_VIEWCONTROLLER_VIEWCONTROLLER_HPP_

#include <controller/universe/Planet.hpp>
#include <OgrePrerequisites.h>
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/visualization/panels/MathGLPanel.hpp>
#include <vector>

class ParamsPanel;
namespace CEGUI {
class OgreRenderer;
} /* namespace CEGUI */


/*
 *
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

	void addPlanet(Planet* planet);

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
