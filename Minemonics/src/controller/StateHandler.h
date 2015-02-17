#pragma once

#include <vector>
#include <map>

typedef enum {
	STARTUP,
	GUI,
	LOADING,
	CANCEL_LOADING,
	SIMULATION,
	SHUTDOWN
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
	inline float getFrameTime() { return mFrameTime; }

protected:
	ApplicationState mState;
	bool mLocked;
	float mFrameTime;
};

