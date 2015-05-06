#pragma once

//# corresponding header
//# forward declarations
//# system headers
//## controller headers
//## model headers
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

enum ApplicationState{
	STARTUP, GUI, LOADING, CANCEL_LOADING, SIMULATION, SHUTDOWN
};

/**
 * @brief		Brief
 * @details		Details
 * @date		2015-11-17
 * @author		Benjamin Ellenberger
 */
class StateHandler {

public:
	StateHandler();
	virtual ~StateHandler();

public:
	bool requestStateChange(ApplicationState state);
	bool lockState();
	bool unlockState();
	ApplicationState getCurrentState();

	void setFrameTime(float ms);
	inline float getFrameTime() {
		return mFrameTime;
	}

protected:
	ApplicationState mState;
	bool mLocked;
	float mFrameTime;
};

