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
#include "controller/input/KeyboardHandler.h"
#include "controller/input/MouseHandler.h"
#include "controller/camera/CameraHandler.h"

#include "BaseApplication.h"

// Logger
#include <utils/logging/Logger.h>


//#include <CEGUI/CEGUI.h>
//#include <Ogre/Renderer.h> //before 0.8 it's just  CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h

class SimulationManager: public BaseApplication {
private:
	OgreBites::Label* mInfoLabel;
	HillsO3D* mTerrain;

	// Game component handlers
	KeyboardHandler mKeyboardHandler;
	MouseHandler mMouseHandler;
	CameraHandler mCameraHandler;

	// Static logger
	static BoostLogger logger;

	static class _Init {
	public:
		_Init() {
			logger.add_attribute("ClassName",boost::log::attributes::constant < std::string > ("SimulationManager"));
		}
	} _initializer;
public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	// Accessor methods
	CameraHandler& getCameraHandler();
	KeyboardHandler& getKeyboardHandler();
	MouseHandler& getMouseHandler();
	void enableShutdown();
	Ogre::Camera* getCamera();

protected:
    //CEGUI::OgreRenderer* mRenderer;

	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

    //bool quit(const CEGUI::EventArgs &e);
};

#endif // #ifndef __SimulationManager_h_
