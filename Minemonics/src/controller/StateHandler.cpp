//# corresponding header
#include <controller/StateHandler.hpp>
#include <OgreStringConverter.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

BoostLogger StateHandler::mBoostLogger; /*<! initialize the boost logger*/
StateHandler::_Init StateHandler::_initializer;
StateHandler::StateHandler() :
		mFrameTime(0), mLocked(false), mState(STARTUP) {

}

StateHandler::~StateHandler() {
}

StateHandler::ApplicationState StateHandler::getCurrentState() {
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
	switch (newState) {
	case StateHandler::GUI:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to GUI";
		break;
	case StateHandler::STARTUP:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to STARTUP";
		break;
	case StateHandler::SIMULATION:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to SIMULATION";
		break;
	case StateHandler::SHUTDOWN:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to SHUTDOWN";
		break;
	case StateHandler::LOADING:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to LOADING";
		break;
	case StateHandler::CANCEL_LOADING:
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to CANCEL_LOADING";
		break;
	}

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

