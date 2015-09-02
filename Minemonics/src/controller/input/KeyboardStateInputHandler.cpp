//# corresponding header
#include <controller/input/KeyboardStateInputHandler.hpp>

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

BoostLogger KeyboardStateInputHandler::mBoostLogger; /*<! initialize the boost logger*/
KeyboardStateInputHandler::_Init KeyboardStateInputHandler::_initializer;
KeyboardStateInputHandler::KeyboardStateInputHandler() :
	mLeftAltPressed(false), mLeftControlPressed(false), mLeftMousePressed(
		false), mLeftShiftPressed(false), mRightAltPressed(false), mRightControlPressed(
		false), mRightMousePressed(false), mRightShiftPressed(false) {
}

KeyboardStateInputHandler::~KeyboardStateInputHandler() {

}

