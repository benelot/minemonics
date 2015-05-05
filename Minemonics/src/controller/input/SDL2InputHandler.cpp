//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/parameter/keyword.hpp>

//## view headers
//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/input/InputUtils.hpp>
#include <controller/input/SDL2InputHandler.hpp>

//## model headers
//## view headers
//## utils headers

BoostLogger SDL2InputHandler::mBoostLogger;  // initialize the static variables
SDL2InputHandler::_Init SDL2InputHandler::_initializer;
SDL2InputHandler::SDL2InputHandler() :
		CEGUIInputHandler(), mLastMouseX(0), mLastMouseY(0) {
}

SDL2InputHandler::~SDL2InputHandler() {
	destroy();
}

void SDL2InputHandler::initialize(StateHandler* stateHandler,
		SimulationManager* simulationMgr) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "initializing SDL2 input handler...";
	mSimulationMgr = simulationMgr;

	SDL_ShowCursor (SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void SDL2InputHandler::destroy() {

}

void SDL2InputHandler::injectInput() {
	injectTimePulse();

	SDL_Event e;
	/* go through all available events */
	while (SDL_PollEvent(&e)) {
		/* we use a switch to determine the event type */
		switch (e.type) {
		/* mouse motion handler */
		case SDL_MOUSEMOTION:
			/* we inject the mouse position directly. */
			CEGUIInputHandler::mouseMoved(
					static_cast<float>(e.motion.x) - mLastMouseX,
					static_cast<float>(e.motion.y) - mLastMouseY);

			CEGUIInputHandler::injectMousePosition(
					static_cast<float>(e.motion.x),
					static_cast<float>(e.motion.y));

			// keep last mouse position
			mLastMouseX = static_cast<float>(e.motion.x);
			mLastMouseY = static_cast<float>(e.motion.y);
			break;

			/* mouse down handler */
		case SDL_MOUSEBUTTONDOWN:
			/* let a special function handle the mouse button down event */
			//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Mouse button pressed" << e.button.button;
			CEGUIInputHandler::mousePressed(
					InputUtils::convertToOgre3D(e.button.button));
			break;

			/* mouse up handler */
		case SDL_MOUSEBUTTONUP:
			/* let a special function handle the mouse button up event */
			CEGUIInputHandler::mouseReleased(
					InputUtils::convertToOgre3D(e.button.button));
			break;

			/* key down */
		case SDL_KEYDOWN:
			CEGUIInputHandler::keyPressed(
					InputUtils::convertToOgre3D(e.key.keysym.sym));
			break;
			/* key up */
		case SDL_KEYUP:
			CEGUIInputHandler::keyReleased(
					InputUtils::convertToOgre3D(e.key.keysym.sym));
			break;
		case SDL_MOUSEWHEEL:
			CEGUIInputHandler::mouseWheelMoved(e.wheel.y);
			break;
			/* WM quit event occured */
		case SDL_QUIT:
			mSimulationMgr->quit();
			break;
		case SDL_WINDOWEVENT:
			mSimulationMgr->windowResized(mSimulationMgr->getWindow());
			//CEGUIInputHandler::windowResized(e.window.data1, e.window.data2);
			break;
		}
	}
}
void SDL2InputHandler::injectTimePulse() {
	/* get current "run-time" in seconds */
	double t = 0.001 * SDL_GetTicks();
	CEGUIInputHandler::injectTimeImpulse(t);

}

int SDL2InputHandler::getMousePositionX() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return x;
}

int SDL2InputHandler::getMousePositionY() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return y;
}
