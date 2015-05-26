#ifndef __SimulationManager_h_
#define __SimulationManager_h_

//# corresponding header
#include <SimulationManager.hpp>

//# forward declarations
class Environment;
class Logger;
class OgreBtDebugDrawer;
class ParamsPanel;

//# system headers
#include <string>
#include <vector>

//## controller headers
//## model headers
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>
//#include <EALib/PopulationT.h>

//## view headers
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <SDL_syswm.h>
#include <OgreOverlaySystem.h>
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
#include <BaseApplication.hpp>

//## configuration headers
#include <configuration/EvolutionConfiguration.hpp>

//## controller headers
#include <controller/StateHandler.hpp>
#include <controller/camera/CameraHandler.hpp>
#include <controller/input/SDL2InputHandler.hpp>
#include <controller/physics/PhysicsController.hpp>
#include <controller/physics/RagDoll.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/Universe.hpp>

//## model headers
#include <model/universe/evolution/juries/Ones.hpp>

//## view headers
#include <view/visualization/panels/MathGLPanel.hpp>
#include <view/visualization/CEGUI/GUISheetHandler.hpp>
#include <view/visualization/panels/ParamsPanel.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>
#include <view/visualization/overlay/InfoOverlay.hpp>
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>

//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The Simulation manager holds the whole application together.
 * @details		The Simulation manager holds the whole application together.
 * It helps to set up the evolutionary runs.
 * It is based on the source file which is part of the
 *    ___                 __    __ _ _    _
 *   /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 *  //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 * / \_// (_| | | |  __/  \  /\  /| |   <| |
 * \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 *       |___/
 *       Tutorial Framework
 *       http://www.ogre3d.org/tikiwiki/
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class SimulationManager: public BaseApplication {
private:

	void updatePhysics();

	void updateEvolution();

	//## controller components

	// State handler
	StateHandler mStateHandler;

	// Game component handlers
	SDL2InputHandler mInputHandler;
	SDL_Window *mSdlWindow;
	CameraHandler mCameraHandler;

	//SheetHandler
	GUISheetHandler mGUISheetHandler;

	//The universe and everything
	Universe mUniverse;

	// Physics controller
	PhysicsController mPhysicsController;

	// timing component
	boost::posix_time::ptime mStart;
	boost::posix_time::ptime mNow;
	boost::posix_time::time_duration mRuntime;

	//## model components
	//	int t;
	//	PopulationT<bool> parents;
	//	PopulationT<bool> offsprings;
	//	Ones jury;
	//
	//	 //scaling window
	//	std::vector<double> window;

	//## view components

	Environment* mTerrain;

	std::vector<RagDoll*> mRagdolls;
	Population population;

	// CEGUI components
	CEGUI::System* mSystem;
	CEGUI::Window* mLayout;

	//CEGUI
	ParamsPanel* mFpsPanel;
	ParamsPanel* mDetailsPanel;
	CEGUI::OgreRenderer* mRenderer;
	CEGUI::Window* mDragContainer;

	// Visualization components
	std::vector<MathGLPanel*> mGraphWindows;
	InfoOverlay mInfoOverlay;

	Ogre3DFFMPEGVideoWriter mVideoWriter;

	//## Debug components
	// Logger
	static BoostLogger mBoostLogger;

	OgreBtDebugDrawer* mDebugDrawer;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"SimulationManager"));
		}
	} _initializer;

protected:
	bool configure(void);
	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void updatePanels(Ogre::Real timeSinceLastFrame);
	virtual void windowFocusChange(Ogre::RenderWindow* rw);

public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	bool quit();
	virtual void windowResized(Ogre::RenderWindow* rw);

	// Accessor methods
	CEGUI::System*& getCEGUISystem() {
		return mSystem;
	}

	CameraHandler & getCameraHandler() {
		return mCameraHandler;
	}

	SDL2InputHandler getInputHandler() {
		return mInputHandler;
	}

	StateHandler getStateHandler() {
		return mStateHandler;
	}

	Ogre::Camera * getCamera() {
		return mCamera;
	}

	ParamsPanel * &getDetailsPanel() {
		return mDetailsPanel;
	}

	ParamsPanel * &getFpsPanel() {
		return mFpsPanel;
	}

	void setDetailsPanel(ParamsPanel* detailsPanel) {
		mDetailsPanel = detailsPanel;
	}

	void setFpsPanel(ParamsPanel* fpsPanel) {
		mFpsPanel = fpsPanel;
	}

	CEGUI::Window * &getLayout() {
		return mLayout;
	}

	Ogre::SceneManager* &getSceneManager() {
		return mSceneMgr;
	}

	CEGUI::OgreRenderer* & getRenderer() {
		return mRenderer;
	}

	Ogre::Root*& getRoot() {
		return mRoot;
	}

	std::vector<MathGLPanel*>& getGraphWindows() {
		return mGraphWindows;
	}

	PhysicsController& getPhysicsController() {
		return mPhysicsController;
	}

	Ogre3DFFMPEGVideoWriter& getVideoWriter() {
		return mVideoWriter;
	}

	boost::posix_time::time_duration& getRuntime() {
		return mRuntime;
	}

	boost::posix_time::ptime& getNow() {
		return mNow;
	}

	OgreBtDebugDrawer*& getDebugDrawer() {
		return mDebugDrawer;
	}

	InfoOverlay& getInfoOverlay() {
		return mInfoOverlay;
	}
};

#endif // #ifndef __SimulationManager_h_
