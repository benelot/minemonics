#ifndef __BaseApplication_h_
#define __BaseApplication_h_

//# corresponding header
//# forward declarations
namespace Ogre {
class OverlaySystem;
} /* namespace Ogre */


//# system headers
//## controller headers
//## model headers
//## view headers
#include <OgreFrameListener.h>
#include <OgrePrerequisites.h>
#include <OgreWindowEventUtilities.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

/**
 * @brief		The Base application manager holds the whole application together.
 * @details		The Base application manager holds the whole application together.
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
class BaseApplication: public Ogre::FrameListener,
		public Ogre::WindowEventListener {
public:
	BaseApplication(void);
	virtual ~BaseApplication(void);

	virtual void go(void);
	Ogre::RenderWindow*& getWindow();
	void setWindow(Ogre::RenderWindow*& window);

protected:
	virtual bool setup();
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void setupView(void) = 0;
	virtual void createFrameListener(void);
	virtual void createScene(void) = 0; // Override me!
	virtual void destroyScene(void);
	virtual void setupResources(void);
	virtual void createResourceListener(void);
	virtual void loadResources(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Ogre::WindowEventListener
	//Adjust mouse clipping area
	virtual void windowResized(Ogre::RenderWindow* rw) = 0;
	//Unattach OIS before window shutdown (very important under Linux)
	virtual void windowClosed(Ogre::RenderWindow* rw);

	Ogre::Root* mRoot;
//	Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
	Ogre::RenderWindow* mWindow;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::OverlaySystem* mOverlaySystem;

	bool mCursorWasVisible;	// Was cursor visible before dialog appeared?
	bool mShutDown;

	// Added for Mac compatibility
	Ogre::String m_ResourcePath;

#ifdef OGRE_STATIC_LIB
	Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};

#endif // #ifndef __BaseApplication_h_
