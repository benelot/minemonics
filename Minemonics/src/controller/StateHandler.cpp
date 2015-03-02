/*
 * StateHandler.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

//# corresponding header
#include "StateHandler.h"
//# forward declarations

//# system headers
//## controller headers

//## model headers

//## view headers
#include <OgreStringConverter.h>

//# custom headers
//## base headers

//## configuration headers

//## controller headers

//## model headers

//## view headers

//## utils headers

StateHandler::StateHandler() :
		mFrameTime(0), mLocked(0), mState(STARTUP) {

}

StateHandler::~StateHandler() {
}

ApplicationState StateHandler::getCurrentState() {
	return mState;
}

// for the sake of clarity, I am not using actual thread synchronization 
// objects to serialize access to this resource. You would want to protect
// this block with a mutex or critical section, etc.
bool StateHandler::lockState() {
	if (mLocked == false) {

		mLocked = true;
		return true;
	} else
		return false;
}

bool StateHandler::unlockState() {
	if (mLocked == true) {
		mLocked = false;
		return true;
	} else
		return false;
}

bool StateHandler::requestStateChange(ApplicationState newState) {
	if (mState == STARTUP) {
		mLocked = false;
		mState = newState;

		return true;
	}

	// this state cannot be changed once initiated
	if (mState == SHUTDOWN) {
		return false;
	}

	if ((mState == GUI || mState == SIMULATION || mState == LOADING
			|| mState == CANCEL_LOADING) && (newState != STARTUP)
			&& (newState != mState)) {
		mState = newState;
		return true;
	} else
		return false;
}

void StateHandler::setFrameTime(float ms) {
	mFrameTime = ms;
}

