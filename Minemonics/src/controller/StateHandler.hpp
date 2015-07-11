#pragma once

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The state handler holds the application states.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class StateHandler {

public:

	/**
	 * Application states
	 */
	//TODO: Redefine application states according to the needs
	enum ApplicationState {
		STARTUP, //!< The application is starting up
		GUI, //!< The GUI is shown
		LOADING, //!< The simulation is loading
		CANCEL_LOADING, //!< The simulation loading is cancelled
		SIMULATION, //!< The simulation is running
		SHUTDOWN, //!< The simulation is shutting down
		NUM_APPLICATION_STATES
	};

	StateHandler();
	virtual ~StateHandler();

public:
	/**
	 * Request a state change.
	 * @param state The state to switch to.
	 * @return If it switched to the requested state.
	 */
	bool requestStateChange(ApplicationState state);

	/**
	 * Lock the current state.
	 * @return If the state has been locked.
	 */
	bool lockState();

	/**
	 * Unlock the current state.
	 * @return If the state has been unlocked.
	 */
	bool unlockState();

	//Accessor methods
	ApplicationState getCurrentState();

	void setFrameTime(float ms);

	inline float getFrameTime() {
		return mFrameTime;
	}

protected:
	/**
	 * The state of the application.
	 */
	ApplicationState mState;

	/**
	 * If the state is locked or not.
	 */
	bool mLocked;

	/**
	 * The frame time of the application.
	 */
	float mFrameTime;
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
					boost::log::attributes::constant<std::string>(
							"StateHandler"));
		}
	} _initializer;
};

