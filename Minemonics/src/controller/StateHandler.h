/*
 * StateHandler.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */
#pragma once

//# corresponding header
//# forward declarations
//# system headers
#include <vector>
#include <map>

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

typedef enum {
	STARTUP, GUI, LOADING, CANCEL_LOADING, SIMULATION, SHUTDOWN
} ApplicationState;

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

