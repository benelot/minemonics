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
#include <controller/viewcontroller/ViewController.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/input/SDL2InputHandler.hpp>
#include <controller/ragdoll/RagDoll.hpp>
#include <controller/universe/evolution/population/creature/Creature.hpp>
#include <controller/universe/evolution/population/Population.hpp>
#include <controller/universe/Universe.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>
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
 * @date		2015-04-27
 * @author		Benjamin Ellenberger
 */
class SimulationManager: public BaseApplication {
public:
	SimulationManager(void);
	virtual ~SimulationManager(void);

	bool quit();
	virtual void windowResized(Ogre::RenderWindow* rw);

	static bool detectError(PopulationModel* populationModel, int numberOfRuns,
			int identifier, int additionalCounter,
			bool showNothingFound = true) {
		bool nothingFound = true;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		for (int j = 0; j < numberOfRuns; j++) {
			int i = 0;
			for (std::vector<CreatureModel*>::const_iterator cit =
					populationModel->getCreatureModels().begin();
					cit != populationModel->getCreatureModels().end()
							&& i <= populationModel->getCreatureModels().size();
					cit++) {
				i++;
			}
			if (i != populationModel->getCreatureModels().size()) {
				nothingFound = false;
				std::cout << "Block " << identifier << "::..."
						<< additionalCounter << "/" << j;
				std::cout << "\nsize: "
						<< populationModel->getCreatureModels().size() << "\t";
				std::cout << "size2: >" << i << std::endl;
				return true;
			}
		}

		if (showNothingFound && nothingFound) {
			std::cout << "Block " << identifier << "::..." << additionalCounter;
			std::cout << "\nNothing found\n\n";
			return false;
		}
		return false;

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}

	// Accessor methods

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

	boost::posix_time::time_duration& getRuntime() {
		return mRuntime;
	}

	boost::posix_time::ptime& getNow() {
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

protected:
	bool configure(void);

	/**
	 * Create the scene in the simulation manager.
	 */
	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual void destroyScene(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void updatePanels(Ogre::Real timeSinceLastFrame);
	virtual void windowFocusChange(Ogre::RenderWindow* rw);

private:

	void updatePhysics(double timeSinceLastFrame);

//	void updateEvolution();

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
	//	int t;
	//	PopulationT<bool> parents;
	//	PopulationT<bool> offsprings;
	//	Ones jury;
	//
	//	 //scaling window
	//	std::vector<double> window;

	//	std::vector<RagDoll*> mRagdolls;

	//## view components

	// timing component
	boost::posix_time::ptime mStart;
	boost::posix_time::ptime mNow;
	boost::posix_time::time_duration mRuntime;

	ViewController mViewController;

	Ogre3DFFMPEGVideoWriter mVideoWriter;

	OgreBtDebugDrawer mDebugDrawer;

	//## Debug components
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
