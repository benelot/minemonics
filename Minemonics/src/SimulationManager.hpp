#ifndef __SimulationManager_h_
#define __SimulationManager_h_

//# corresponding header
#include <BaseApplication.hpp>

//# forward declarations
class Randomness;
struct SDL_Window;
class RagDoll;

//# system headers
//## controller headers
//## model headers
#include <OgreTimer.h>
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

//## view headers
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/SDL2InputHandler.hpp>
#include <controller/StateHandler.hpp>
#include <controller/universe/Universe.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
//## view headers
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers
#include <utils/Debugger.hpp>
#include <utils/logging/Logger.hpp>

/**
 * @brief		The Simulation manager holds the whole application together.
 * @details		The Simulation manager holds the whole application together.
 * It helps to set up the evolutionary runs.
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class SimulationManager: public BaseApplication {
public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	/**
	 * Quit the simulation.
	 * @return If the simulation could be quit.
	 */
	bool quit();

	/**
	 * Event triggered when the window is resized.
	 * @param rw The renderwindow's details.
	 */
	virtual void windowResized(Ogre::RenderWindow* rw);

	// Accessor methods

	static SimulationManager* getSingleton() {
		return mSimulationManager;
	}

	CameraHandler& getCameraHandler() {
		return mCameraHandler;
	}

	SDL2InputHandler& getInputHandler() {
		return mInputHandler;
	}

	StateHandler& getStateHandler() {
		return mStateHandler;
	}

	Ogre::Camera* getCamera() {
		return mCamera;
	}

	Ogre::SceneManager* getSceneManager() {
		return mSceneMgr;
	}

	Ogre::Root* getRoot() {
		return mRoot;
	}

	Ogre3DFFMPEGVideoWriter& getVideoWriter() {
		return mVideoWriter;
	}

	unsigned long int getRuntime() {
		return mRuntime;
	}

	unsigned long int getNow() {
		return mNow;
	}

	OgreBtDebugDrawer& getDebugDrawer() {
		return mDebugDrawer;
	}

	Universe& getUniverse() {
		return mUniverse;
	}

	ViewController& getViewController() {
		return mViewController;
	}

	double getSimulationSpeed() const {
		return mSimulationSpeed;
	}

	void setSimulationSpeed(double simulationSpeed) {
		mSimulationSpeed = simulationSpeed;
	}

	const Debugger& getDebugger() const {
		return mDebugger;
	}

protected:
	bool configure(void);

	/**
	 * Create the scene in the simulation manager.
	 */
	virtual void createScene(void);

	/**
	 * Create the frame listener to react to frame trigger events.
	 */
	virtual void createFrameListener(void);

	/**
	 * Called after all render targets have had their rendering commands
	 * issued, but before render windows have been asked to flip their
	 * buffers over.
	 * @param evt
	 * 		Information about the frame rendering.
	 * @remarks
	 * 		The usefulness of this event comes from the fact that rendering
	 * commands are queued for the GPU to process. These can take a little
	 * while to finish, and so while that is happening the CPU can be doing
	 * useful things. Once the request to 'flip buffers' happens, the thread
	 * requesting it will block until the GPU is ready, which can waste CPU
	 * cycles. Therefore, it is often a good idea to use this callback to
	 * perform per-frame processing. Of course because the frame's rendering
	 * commands have already been issued, any changes you make will only
	 * take effect from the next frame, but in most cases that's not noticeable.
	 * @return
	 * 		True to continue rendering, false to drop out of the rendering loop.
	 */
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/**
	 * Destroy the scene on shutdown.
	 */
	virtual void destroyScene(void);

	/**
	 * Update the information panels.
	 * @param timeSinceLastFrame
	 */
	void updatePanels(Ogre::Real timeSinceLastFrame);

	/**
	 * If the window focus changes.
	 * @param rw Information about the render window.
	 */
	virtual void windowFocusChange(Ogre::RenderWindow* rw);

private:
	//## controller components

	// State handler
	StateHandler mStateHandler;

	// Game component handlers
	SDL2InputHandler mInputHandler;
	SDL_Window *mSdlWindow;
	CameraHandler mCameraHandler;

	//The universe and everything
	Universe mUniverse;

	//## model components
	//## view components

	int mSimulationSpeed;

	ViewController mViewController;

	Ogre3DFFMPEGVideoWriter mVideoWriter;

	static SimulationManager* mSimulationManager;

	//randomness singleton
	Randomness* mRandomness;

	// timing component
	Ogre::Timer time;
	unsigned long int mStart;
	unsigned long int mFrameTime;
	unsigned long int mPrevious;
	unsigned long int mNow;
	unsigned long int mRuntime;
	long int mAccumulator;
	long int mApplicationDt;
	unsigned long int mApplicationClock;


	/**
	 * The time it took the graphics rendering last time
	 */
	long int mLastGraphicsTick;
	unsigned long int mGraphicsStart;

	/**
	 * The time it took the input to process last time
	 */
	long int mLastInputTick;
	unsigned long int mInputStart;

	/**
	 * The time it took the model to update last time
	 * This includes the bullet physics update
	 */
	long int mLastModelTick;
	long int mModelStart;
	long int mPhysicsTick;
	long int mPhysicsStepStart;
	long int mPhysicsStepEnd;

	//## Debug components

	//ogre bullet debug drawer
	OgreBtDebugDrawer mDebugDrawer;

	// simulation debugger
	Debugger mDebugger;

	// Logger
	static BoostLogger mBoostLogger;

	static class _Init {
	public:
		_Init() {
			mBoostLogger.add_attribute("ClassName",
					boost::log::attributes::constant<std::string>(
							"SimulationManager"));
		}
	} _initializer;
};

#endif // #ifndef __SimulationManager_h_
