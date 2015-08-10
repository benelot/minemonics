#ifndef CONTROLLER_INPUT_KEYBOARDSTATEINPUTHANDLER_HPP_
#define CONTROLLER_INPUT_KEYBOARDSTATEINPUTHANDLER_HPP_

//# corresponding header
//# forward declarations
//# system headers
#include <string>

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
 * @brief		The Keyboard State Input handler handles the input coming from the lower hardware input layer and handles it in the context of the state. It should always be the last input handler as it keeps the keyboard states for the others.
 * @details		Details
 * @date		2015-07-21
 * @author		Benjamin Ellenberger
 */
class KeyboardStateInputHandler {
public:
	KeyboardStateInputHandler();
	virtual ~KeyboardStateInputHandler();

	bool isLeftControlPressed() const {
		return mLeftControlPressed;
	}

	void setLeftControlPressed(bool leftControlPressed) {
		mLeftControlPressed = leftControlPressed;
	}

	bool isLeftMousePressed() const {
		return mLeftMousePressed;
	}

	void setLeftMousePressed(bool leftMousePressed) {
		mLeftMousePressed = leftMousePressed;
	}

	bool isLeftShiftPressed() const {
		return mLeftShiftPressed;
	}

	void setLeftShiftPressed(bool leftShiftPressed) {
		mLeftShiftPressed = leftShiftPressed;
	}

	bool isRightControlPressed() const {
		return mRightControlPressed;
	}

	void setRightControlPressed(bool rightControlPressed) {
		mRightControlPressed = rightControlPressed;
	}

	bool isRightMousePressed() const {
		return mRightMousePressed;
	}

	void setRightMousePressed(bool rightMousePressed) {
		mRightMousePressed = rightMousePressed;
	}

	bool isRightShiftPressed() const {
		return mRightShiftPressed;
	}

	void setRightShiftPressed(bool rightShiftPressed) {
		mRightShiftPressed = rightShiftPressed;
	}

	bool isLeftAltPressed() const {
		return mLeftAltPressed;
	}

	void setLeftAltPressed(bool leftAltPressed) {
		mLeftAltPressed = leftAltPressed;
	}

	bool isRightAltPressed() const {
		return mRightAltPressed;
	}

	void setRightAltPressed(bool rightAltPressed) {
		mRightAltPressed = rightAltPressed;
	}

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
							"KeyboardStateInputHandler"));
		}
	} _initializer;

protected:

	bool mLeftMousePressed;
	/**
	 * If the right mouse button is pressed.
	 */
	bool mRightMousePressed;

	bool mLeftControlPressed;

	bool mRightControlPressed;

	bool mLeftAltPressed;

	bool mRightAltPressed;

	bool mLeftShiftPressed;

	bool mRightShiftPressed;

};

#endif /* CONTROLLER_INPUT_KEYBOARDSTATEINPUTHANDLER_HPP_ */
