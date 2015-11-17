//# corresponding header
#include <controller/StateHandler.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreStringConverter.h>
//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/universe/Planet.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger StateHandler::mBoostLogger; /**<! initialize the boost logger*/
StateHandler::_Init StateHandler::_initializer;
StateHandler::StateHandler() :
	mFrameTime(0), mLocked(false), mState(STARTUP), mCurrentlySelectedPlanet(
	NULL) {

}

StateHandler::~StateHandler() {
//	mFrameTime
//	mLocked
//	mState
}

StateHandler::ApplicationState StateHandler::getCurrentState() {
	return mState;
}

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

bool StateHandler::requestStateChange(const ApplicationState newState) {
	if (mState == STARTUP) {
		mLocked = false;
		mState = newState;

		return true;
	}

	/** this state cannot be changed once initiated */
	if (mState == SHUTDOWN) {
		return false;
	}

	if ((mState == GUI || mState == HEADLESS_SIMULATION || mState == SIMULATION
		|| mState == LOADING || mState == CANCEL_LOADING)
		&& (newState != STARTUP) && (newState != mState)) {
		mState = newState;

		switch (newState) {
		case StateHandler::GUI: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "State changed to GUI";
			break;
		}
		case StateHandler::STARTUP: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to STARTUP";
			break;
		}
		case StateHandler::SIMULATION:
		{
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to SIMULATION";
			break;
		}
		case StateHandler::HEADLESS_SIMULATION: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to HEADLESS_SIMULATION";
			break;
		}
		case StateHandler::SHUTDOWN: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to SHUTDOWN";
			break;
		}
		case StateHandler::LOADING: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to LOADING";
			break;
		}
		case StateHandler::CANCEL_LOADING: {
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
			<< "State changed to CANCEL_LOADING";
		}
		break;
	}
		return true;
	} else {
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "No state change.";
	}
	return false;
}

void StateHandler::setFrameTime(const float ms) {
	mFrameTime = ms;
}

