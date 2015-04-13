/*
 -----------------------------------------------------------------------------
 Filename:    SimulationManager.h
 -----------------------------------------------------------------------------

 based on the source file which is part of the
 ___                 __    __ _ _    _
 /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
 / \_// (_| | | |  __/  \  /\  /| |   <| |
 \___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
 |___/
 Tutorial Framework
 http://www.ogre3d.org/tikiwiki/
 -----------------------------------------------------------------------------
 */
#ifndef __SimulationManager_h_
#define __SimulationManager_h_

//# corresponding header
#include "SimulationManager.h"

//# forward declarations
class Environment;
class Logger;

//# system headers
//## controller headers

//## model headers
#include <EALib/PopulationT.h>

//## view headers
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <SDL_syswm.h>
#include <OgreOverlaySystem.h>

//# custom headers
//## base headers
#include "BaseApplication.h"

//## configuration headers
#include "configuration/EvolutionConfiguration.h"

//## controller headers
#include "controller/StateHandler.h"
#include "controller/camera/CameraHandler.h"
#include "controller/input/SDL2InputHandler.h"
#include "controller/physics/PhysicsController.h"
#include "controller/physics/RagDoll.h"

#include "controller/evolution/population/creature/Creature.h"

//## model headers
#include "model/evolution/juries/Ones.h"

//## view headers
#include "view/MathGL/MathGLWindow.h"
#include "view/CEGUI/GUISheetHandler.h"
#include "view/CEGUI/ParamsPanel.h"
#include "view/ogre3D/bullet/OgreDebugDrawer.h"
#include "view/ogre3D/overlay/InfoOverlay.h"
#include "view/ogre3D/videocapture/Ogre3DFFMPEGVideoWriter.h"

//## utils headers
#include "utils/logging/Logger.h"

class SimulationManager: public BaseApplication {
private:

	// StateHandler
	StateHandler mStateHandler;

	Environment* mTerrain;

	PhysicsController mPhysicsController;

	// Game component handlers
	SDL2InputHandler mInputHandler;
	SDL_Window *mSdlWindow;
	CameraHandler mCameraHandler;

	CEGUI::System* mSystem;
	CEGUI::Window* mLayout;


	//SheetHandler
	GUISheetHandler mGUISheetHandler;

	//CEGUI
	ParamsPanel* mFpsPanel;
	ParamsPanel* mDetailsPanel;

	// Logger
	static BoostLogger mBoostLogger;

	boost::posix_time::ptime mStart;
	boost::posix_time::ptime mNow;
	boost::posix_time::time_duration mRuntime;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>("SimulationManager"));
		}
	} _initializer;

	std::vector<Ogre::SceneNode*> cubes;

	std::vector<RagDoll*> mRagdolls;

	std::vector<Creature*> mCreatures;
	void updatePhysics();
public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	// Accessor methods
	// Accessor methods
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

	ParamsPanel*& getDetailsPanel();
	ParamsPanel*& getFpsPanel();
	void setDetailsPanel(ParamsPanel* detailsPanel);
	void setFpsPanel(ParamsPanel* fpsPanel);
	CEGUI::Window*& getLayout();
    Ogre::SceneManager*& getSceneManager();
    CEGUI::OgreRenderer*& getRenderer();
    Ogre::Root*& getRoot();
    bool configure(void);

	bool quit();
	CEGUI::System*& getCEGUISystem();
	virtual void windowResized(Ogre::RenderWindow* rw);

	std::vector<MathGLWindow*>& getGraphWindows() {
		return mGraphWindows;
	}

	bool isDrawBulletDebug() const {
		return mDrawBulletDebug;
	}

	void setDrawBulletDebug(bool drawBulletDebug) {
		mDrawBulletDebug = drawBulletDebug;
	}

	PhysicsController& getPhysicsController() {
		return mPhysicsController;
	}

	Ogre3DFFMPEGVideoWriter& getVideoWriter() {
		return videoWriter;
	}

	boost::posix_time::time_duration& getRuntime() {
		return mRuntime;
	}

	int t;
	PopulationT<bool> parents;
	PopulationT<bool> offsprings;
	Ones jury;
	//
	// scaling window
	//
	std::vector<double> window;

protected:
	CEGUI::OgreRenderer* mRenderer;
	CEGUI::Window* mDragContainer;

	OgreDebugDrawer* mDebugDrawer;
	bool mDrawBulletDebug;

	std::vector<MathGLWindow*> mGraphWindows;

	InfoOverlay mInfoOverlay;

	Ogre3DFFMPEGVideoWriter videoWriter;

	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void updatePanels();
	void updateEvolution();
	virtual void windowFocusChange(Ogre::RenderWindow* rw);
};

#endif // #ifndef __SimulationManager_h_
