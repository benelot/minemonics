#ifndef APPLICATIONMOUSECODE_H_
#define APPLICATIONMOUSECODE_H_

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

/**
 * @brief		Application mouse code defines the mouse codes for the input handlers.
 * @details		Details
 * @date		2015-02-27
 * @author		Benjamin Ellenberger
 */
class ApplicationMouseCode {
public:
	/*!
	 \brief
	 Enumeration of mouse buttons
	 */
	enum MouseButton {
		//! The left mouse button.
		LeftButton,
		//! The right mouse button.
		RightButton,
		//! The middle mouse button.
		MiddleButton,
		//! The first 'extra' mouse button.
		X1Button,
		//! The second 'extra' mouse button.
		X2Button,
		//! Value that equals the number of mouse buttons supported by CEGUI.
		MouseButtonCount,
		//! Value set for no mouse button.  NB: This is not 0, do not assume!
		NoButton
	};
};

#endif /* APPLICATIONMOUSECODE_H_ */
