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

class HillsO3D;
class CEGUIInputHandler;
class GUISheetHandler;
class Logger;

// base
#include "BaseApplication.h"

// model

// view
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "controller/StateHandler.h"

// controller
#include "controller/camera/CameraHandler.h"

//utils
#include <utils/logging/Logger.h>

class SimulationManager: public BaseApplication {
private:
	HillsO3D* mTerrain;

	// Game component handlers
	CEGUIInputHandler* mInputHandler;
	CameraHandler mCameraHandler;

	CEGUI::System* mSystem;
	CEGUI::Window* mLayout;

	// StateHandler
	StateHandler* mStateHandler;

	//SheetHandler
	GUISheetHandler* mGUISheetHandler;

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

public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	// Accessor methods
	CameraHandler& getCameraHandler();
	CEGUIInputHandler* getInputHandler();
	StateHandler* getStateHandler();

	Ogre::Camera* getCamera();
	ParamsPanel*& getDetailsPanel();
	ParamsPanel*& getFpsPanel();
	void setDetailsPanel(ParamsPanel*& detailsPanel);
	void setFpsPanel(ParamsPanel* fpsPanel);
	CEGUI::Window*& getLayout();

	bool quit();

protected:
	CEGUI::OgreRenderer* mRenderer;

	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowFocusChange(Ogre::RenderWindow* rw);
	CEGUI::Window* createMenu(CEGUI::Window* sheet, CEGUI::WindowManager& win);
	void createDebugPanels();
};

#endif // #ifndef __SimulationManager_h_
