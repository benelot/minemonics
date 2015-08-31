//# corresponding headers
//# forward declarations
//# system headers
#include <iterator>
#include <utility>
#include <vector>

//## controller headers
//## model headers
//## view headers
#include <CEGUI/GUIContext.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/NamedElement.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/System.h>
#include <CEGUI/Vector.h>
#include <CEGUI/widgets/FrameWindow.h>
#include <CEGUI/Window.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
//## controller headers
#include <controller/input/InputUtils.hpp>
#include <controller/input/CEGUIInputHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>
//## model headers
//## view headers
//## utils headers

BoostLogger CEGUIInputHandler::mBoostLogger; /*<! initialize the boost logger*/
CEGUIInputHandler::_Init CEGUIInputHandler::_initializer;
CEGUIInputHandler::CEGUIInputHandler() :
	OgreInputHandler(), mCEGUIlastTick(0) {

}

CEGUIInputHandler::~CEGUIInputHandler() {
	//OgreInputHandler is called automatically
}

void CEGUIInputHandler::initialize() {
	OgreInputHandler::initialize();
}

//-------------------------------------------------------------------------------------
bool CEGUIInputHandler::keyPressed(const ApplicationKeycode::Keycode key) {

	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "RawKey::" << key;

	//If CEGUI used the input, then return
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
		(CEGUI::Key::Scan) InputUtils::convertToCEGUI(key))) {
		return true;
	}

	switch (key) {
	case ApplicationKeycode::APPK_1:
		// return CEGUI::Key::One;
		break;
	case ApplicationKeycode::APPK_2:
		// return CEGUI::Key::Two;
		break;
	case ApplicationKeycode::APPK_3:
		// return CEGUI::Key::Three;
		break;
	case ApplicationKeycode::APPK_4:
		// return CEGUI::Key::Four;
		break;
	case ApplicationKeycode::APPK_5:
		// return CEGUI::Key::Five;
		break;
	case ApplicationKeycode::APPK_6:
		// return CEGUI::Key::Six;
		break;
	case ApplicationKeycode::APPK_7:
		// return CEGUI::Key::Seven;
		break;
	case ApplicationKeycode::APPK_8:
		// return CEGUI::Key::Eight;
		break;
	case ApplicationKeycode::APPK_9:
		// return CEGUI::Key::Nine;
		break;
	case ApplicationKeycode::APPK_0:
		// return CEGUI::Key::Zero;
		break;

	case ApplicationKeycode::APPK_q:
		// return CEGUI::Key::Q;
		break;
	case ApplicationKeycode::APPK_w:
		// return CEGUI::Key::W;
		break;
	case ApplicationKeycode::APPK_e:
		// return CEGUI::Key::E;
		break;
	case ApplicationKeycode::APPK_r:
		break;
	case ApplicationKeycode::APPK_t:
		break;
	case ApplicationKeycode::APPK_y:
		// return CEGUI::Key::Y;
		break;
	case ApplicationKeycode::APPK_u:
		// return CEGUI::Key::U;
		break;
	case ApplicationKeycode::APPK_i:
		// return CEGUI::Key::I;
		break;
	case ApplicationKeycode::APPK_o:
		// return CEGUI::Key::O;
		break;
	case ApplicationKeycode::APPK_p:
		// return CEGUI::Key::P;
		break;
	case ApplicationKeycode::APPK_a:
		// return CEGUI::Key::A;
		break;
	case ApplicationKeycode::APPK_s:
		// return CEGUI::Key::S;
		break;
	case ApplicationKeycode::APPK_d:
		// return CEGUI::Key::D;
		break;
	case ApplicationKeycode::APPK_f:
		break;
	case ApplicationKeycode::APPK_g:
		break;
	case ApplicationKeycode::APPK_h:
		// return CEGUI::Key::H;
		break;
	case ApplicationKeycode::APPK_j:
		// return CEGUI::Key::J;
		break;
	case ApplicationKeycode::APPK_k:
		// return CEGUI::Key::K;
		break;
	case ApplicationKeycode::APPK_l:
		// return CEGUI::Key::L;
		break;
	case ApplicationKeycode::APPK_z:
		// return CEGUI::Key::Z;
		break;
	case ApplicationKeycode::APPK_x:
		// return CEGUI::Key::X;
		break;
	case ApplicationKeycode::APPK_c:
		// return CEGUI::Key::C;
		break;
	case ApplicationKeycode::APPK_v:
		// return CEGUI::Key::V;
		break;
	case ApplicationKeycode::APPK_b:
		// return CEGUI::Key::B;
		break;
	case ApplicationKeycode::APPK_n:
		// return CEGUI::Key::N;
		break;
	case ApplicationKeycode::APPK_m:
		// return CEGUI::Key::M;
		break;

	case ApplicationKeycode::APPK_COMMA:
		// return CEGUI::Key::Comma;
		break;
	case ApplicationKeycode::APPK_PERIOD:
		// return CEGUI::Key::Period;
		break;
	case ApplicationKeycode::APPK_SLASH:
		// return CEGUI::Key::Slash;
		break;
	case ApplicationKeycode::APPK_BACKSLASH:
		// return CEGUI::Key::Backslash;
		break;
	case ApplicationKeycode::APPK_MINUS:
		// return CEGUI::Key::Minus;
		break;
	case ApplicationKeycode::APPK_EQUALS:
		// return CEGUI::Key::Equals;
		break;
	case ApplicationKeycode::APPK_SEMICOLON:
		// return CEGUI::Key::Semicolon;
		break;
	case ApplicationKeycode::APPK_LEFTBRACKET:
		// return CEGUI::Key::LeftBracket;
		break;
	case ApplicationKeycode::APPK_RIGHTBRACKET:
		// return CEGUI::Key::RightBracket;
		break;
	case ApplicationKeycode::APPK_QUOTE:
		// return CEGUI::Key::Apostrophe;
		break;
	case ApplicationKeycode::APPK_BACKQUOTE:
		// return CEGUI::Key::Grave;
		break;

	case ApplicationKeycode::APPK_RETURN:
		// return CEGUI::Key::Return;
		break;
	case ApplicationKeycode::APPK_SPACE:
		// return CEGUI::Key::Space;
		break;
	case ApplicationKeycode::APPK_BACKSPACE:
		// return CEGUI::Key::Backspace;
		break;
	case ApplicationKeycode::APPK_TAB:
		// return CEGUI::Key::Tab;
		break;

	case ApplicationKeycode::APPK_ESCAPE:
		// return CEGUI::Key::Escape;
		break;
	case ApplicationKeycode::APPK_PAUSE:
		// return CEGUI::Key::Pause;
		break;
	case ApplicationKeycode::APPK_SYSREQ:
		break;
	case ApplicationKeycode::APPK_POWER:
		// return CEGUI::Key::Power;
		break;

		//case ApplicationKeycode::APPK_NUMLOCK:
		// return CEGUI::Key::NumLock;
		break;
	case ApplicationKeycode::APPK_SCROLLLOCK:
		// return CEGUI::Key::ScrollLock;
		break;

	case ApplicationKeycode::APPK_F1:
		// return CEGUI::Key::F1;
		break;
	case ApplicationKeycode::APPK_F2:
		// return CEGUI::Key::F2;
		break;
	case ApplicationKeycode::APPK_F3:
		// return CEGUI::Key::F3;
		break;
	case ApplicationKeycode::APPK_F4:
		// return CEGUI::Key::F4;
		break;
	case ApplicationKeycode::APPK_F5:
		// return CEGUI::Key::F5;
		break;
	case ApplicationKeycode::APPK_F6:
		// return CEGUI::Key::F6;
		break;
	case ApplicationKeycode::APPK_F7:
		// return CEGUI::Key::F7;
		break;
	case ApplicationKeycode::APPK_F8:
		// return CEGUI::Key::F8;
		break;
	case ApplicationKeycode::APPK_F9:
		// return CEGUI::Key::F9;
		break;
	case ApplicationKeycode::APPK_F10:
		// return CEGUI::Key::F10;
		break;
	case ApplicationKeycode::APPK_F11:
		// return CEGUI::Key::F11;
		break;
	case ApplicationKeycode::APPK_F12:
		// return CEGUI::Key::F12;
		break;
	case ApplicationKeycode::APPK_F13:
		// return CEGUI::Key::F13;
		break;
	case ApplicationKeycode::APPK_F14:
		// return CEGUI::Key::F14;
		break;
	case ApplicationKeycode::APPK_F15:
		// return CEGUI::Key::F15;
		break;

	case ApplicationKeycode::APPK_LCTRL:
		for (std::vector<MovablePanel*>::iterator iit =
			SimulationManager::getSingleton()->getViewController().getMovablePanels().begin();
			iit
				!= SimulationManager::getSingleton()->getViewController().getMovablePanels().end();
			iit++) {
			(*iit)->showTitleBar();
		}
		break;
	case ApplicationKeycode::APPK_LALT:
		// return CEGUI::Key::LeftAlt;
		break;
	case ApplicationKeycode::APPK_LSHIFT:
		// return CEGUI::Key::LeftShift;
		break;
		//case ApplicationKeycode::APPK_LSUPER: // return CEGUI::Key::LeftWindows;
		break;
	case ApplicationKeycode::APPK_RCTRL:
		// return CEGUI::Key::RightControl;
		break;
	case ApplicationKeycode::APPK_RALT:
		// return CEGUI::Key::RightAlt;
		break;
	case ApplicationKeycode::APPK_RSHIFT:
		// return CEGUI::Key::RightShift;
		break;
		//case ApplicationKeycode::APPK_RSUPER: // return CEGUI::Key::RightWindows;
		break;
	case ApplicationKeycode::APPK_MENU:
		// return CEGUI::Key::AppMenu;
		break;

	case ApplicationKeycode::APPK_KP_0:
		// return CEGUI::Key::Numpad0;
		break;
	case ApplicationKeycode::APPK_KP_1:
		// return CEGUI::Key::Numpad1;
		break;
	case ApplicationKeycode::APPK_KP_2:
		// return CEGUI::Key::Numpad2;
		break;
	case ApplicationKeycode::APPK_KP_3:
		// return CEGUI::Key::Numpad3;
		break;
	case ApplicationKeycode::APPK_KP_4:
		// return CEGUI::Key::Numpad4;
		break;
	case ApplicationKeycode::APPK_KP_5:
		// return CEGUI::Key::Numpad5;
		break;
	case ApplicationKeycode::APPK_KP_6:
		// return CEGUI::Key::Numpad6;
		break;
	case ApplicationKeycode::APPK_KP_7:
		// return CEGUI::Key::Numpad7;
		break;
	case ApplicationKeycode::APPK_KP_8:
		// return CEGUI::Key::Numpad8;
		break;
	case ApplicationKeycode::APPK_KP_9:
		// return CEGUI::Key::Numpad9;
		break;
	case ApplicationKeycode::APPK_KP_PERIOD:
		// return CEGUI::Key::Decimal;
		break;
	case ApplicationKeycode::APPK_KP_PLUS:
		// return CEGUI::Key::Add;
		break;
	case ApplicationKeycode::APPK_KP_MINUS:
		// return CEGUI::Key::Subtract;
		break;
	case ApplicationKeycode::APPK_KP_MULTIPLY:
		// return CEGUI::Key::Multiply;
		break;
	case ApplicationKeycode::APPK_KP_DIVIDE:
		// return CEGUI::Key::Divide;
		break;
	case ApplicationKeycode::APPK_KP_ENTER:
		// return CEGUI::Key::NumpadEnter;
		break;

	case ApplicationKeycode::APPK_UP:
		// return CEGUI::Key::ArrowUp;
		break;
	case ApplicationKeycode::APPK_LEFT:
		// return CEGUI::Key::ArrowLeft;
		break;
	case ApplicationKeycode::APPK_RIGHT:
		// return CEGUI::Key::ArrowRight;
		break;
	case ApplicationKeycode::APPK_DOWN:
		// return CEGUI::Key::ArrowDown;
		break;

	case ApplicationKeycode::APPK_HOME:
		// return CEGUI::Key::Home;
		break;
	case ApplicationKeycode::APPK_END:
		// return CEGUI::Key::End;
		break;
	case ApplicationKeycode::APPK_PAGEUP:
		// return CEGUI::Key::PageUp;
		break;
	case ApplicationKeycode::APPK_PAGEDOWN:
		// return CEGUI::Key::PageDown;
		break;
	case ApplicationKeycode::APPK_INSERT:
		// return CEGUI::Key::Insert;
		break;
	case ApplicationKeycode::APPK_DELETE:
		// return CEGUI::Key::Delete;
		break;
	}
	//hand value down to Ogre
	return OgreInputHandler::keyPressed(key);
}

//-------------------------------------------------------------------------------------
bool CEGUIInputHandler::keyReleased(const ApplicationKeycode::Keycode key) {

	switch (key) {
	case ApplicationKeycode::APPK_1:
		// return CEGUI::Key::One;
		break;
	case ApplicationKeycode::APPK_2:
		// return CEGUI::Key::Two;
		break;
	case ApplicationKeycode::APPK_3:
		// return CEGUI::Key::Three;
		break;
	case ApplicationKeycode::APPK_4:
		// return CEGUI::Key::Four;
		break;
	case ApplicationKeycode::APPK_5:
		// return CEGUI::Key::Five;
		break;
	case ApplicationKeycode::APPK_6:
		// return CEGUI::Key::Six;
		break;
	case ApplicationKeycode::APPK_7:
		// return CEGUI::Key::Seven;
		break;
	case ApplicationKeycode::APPK_8:
		// return CEGUI::Key::Eight;
		break;
	case ApplicationKeycode::APPK_9:
		// return CEGUI::Key::Nine;
		break;
	case ApplicationKeycode::APPK_0:
		// return CEGUI::Key::Zero;
		break;

	case ApplicationKeycode::APPK_q:
		// return CEGUI::Key::Q;
		break;
	case ApplicationKeycode::APPK_w:
		// return CEGUI::Key::W;
		break;
	case ApplicationKeycode::APPK_e:
		// return CEGUI::Key::E;
		break;
	case ApplicationKeycode::APPK_r:
		break;
	case ApplicationKeycode::APPK_t:
		break;
	case ApplicationKeycode::APPK_y:
		// return CEGUI::Key::Y;
		break;
	case ApplicationKeycode::APPK_u:
		// return CEGUI::Key::U;
		break;
	case ApplicationKeycode::APPK_i:
		// return CEGUI::Key::I;
		break;
	case ApplicationKeycode::APPK_o:
		// return CEGUI::Key::O;
		break;
	case ApplicationKeycode::APPK_p:
		// return CEGUI::Key::P;
		break;
	case ApplicationKeycode::APPK_a:
		// return CEGUI::Key::A;
		break;
	case ApplicationKeycode::APPK_s:
		// return CEGUI::Key::S;
		break;
	case ApplicationKeycode::APPK_d:
		// return CEGUI::Key::D;
		break;
	case ApplicationKeycode::APPK_f:
		break;
	case ApplicationKeycode::APPK_g:
		break;
	case ApplicationKeycode::APPK_h:
		// return CEGUI::Key::H;
		break;
	case ApplicationKeycode::APPK_j:
		// return CEGUI::Key::J;
		break;
	case ApplicationKeycode::APPK_k:
		// return CEGUI::Key::K;
		break;
	case ApplicationKeycode::APPK_l:
		// return CEGUI::Key::L;
		break;
	case ApplicationKeycode::APPK_z:
		// return CEGUI::Key::Z;
		break;
	case ApplicationKeycode::APPK_x:
		// return CEGUI::Key::X;
		break;
	case ApplicationKeycode::APPK_c:
		// return CEGUI::Key::C;
		break;
	case ApplicationKeycode::APPK_v:
		// return CEGUI::Key::V;
		break;
	case ApplicationKeycode::APPK_b:
		// return CEGUI::Key::B;
		break;
	case ApplicationKeycode::APPK_n:
		// return CEGUI::Key::N;
		break;
	case ApplicationKeycode::APPK_m:
		// return CEGUI::Key::M;
		break;

	case ApplicationKeycode::APPK_COMMA:
		// return CEGUI::Key::Comma;
		break;
	case ApplicationKeycode::APPK_PERIOD:
		// return CEGUI::Key::Period;
		break;
	case ApplicationKeycode::APPK_SLASH:
		// return CEGUI::Key::Slash;
		break;
	case ApplicationKeycode::APPK_BACKSLASH:
		// return CEGUI::Key::Backslash;
		break;
	case ApplicationKeycode::APPK_MINUS:
		// return CEGUI::Key::Minus;
		break;
	case ApplicationKeycode::APPK_EQUALS:
		// return CEGUI::Key::Equals;
		break;
	case ApplicationKeycode::APPK_SEMICOLON:
		// return CEGUI::Key::Semicolon;
		break;
	case ApplicationKeycode::APPK_LEFTBRACKET:
		// return CEGUI::Key::LeftBracket;
		break;
	case ApplicationKeycode::APPK_RIGHTBRACKET:
		// return CEGUI::Key::RightBracket;
		break;
	case ApplicationKeycode::APPK_QUOTE:
		// return CEGUI::Key::Apostrophe;
		break;
	case ApplicationKeycode::APPK_BACKQUOTE:
		// return CEGUI::Key::Grave;
		break;

	case ApplicationKeycode::APPK_RETURN:
		// return CEGUI::Key::Return;
		break;
	case ApplicationKeycode::APPK_SPACE:
		// return CEGUI::Key::Space;
		break;
	case ApplicationKeycode::APPK_BACKSPACE:
		// return CEGUI::Key::Backspace;
		break;
	case ApplicationKeycode::APPK_TAB:
		// return CEGUI::Key::Tab;
		break;

	case ApplicationKeycode::APPK_ESCAPE:
		// return CEGUI::Key::Escape;
		break;
	case ApplicationKeycode::APPK_PAUSE:
		// return CEGUI::Key::Pause;
		break;
	case ApplicationKeycode::APPK_SYSREQ:
		break;
	case ApplicationKeycode::APPK_POWER:
		// return CEGUI::Key::Power;
		break;

		//case ApplicationKeycode::APPK_NUMLOCK:
		// return CEGUI::Key::NumLock;
		break;
	case ApplicationKeycode::APPK_SCROLLLOCK:
		// return CEGUI::Key::ScrollLock;
		break;

	case ApplicationKeycode::APPK_F1:
		// return CEGUI::Key::F1;
		break;
	case ApplicationKeycode::APPK_F2:
		// return CEGUI::Key::F2;
		break;
	case ApplicationKeycode::APPK_F3:
		// return CEGUI::Key::F3;
		break;
	case ApplicationKeycode::APPK_F4:
		// return CEGUI::Key::F4;
		break;
	case ApplicationKeycode::APPK_F5:
		// return CEGUI::Key::F5;
		break;
	case ApplicationKeycode::APPK_F6:
		// return CEGUI::Key::F6;
		break;
	case ApplicationKeycode::APPK_F7:
		// return CEGUI::Key::F7;
		break;
	case ApplicationKeycode::APPK_F8:
		// return CEGUI::Key::F8;
		break;
	case ApplicationKeycode::APPK_F9:
		// return CEGUI::Key::F9;
		break;
	case ApplicationKeycode::APPK_F10:
		// return CEGUI::Key::F10;
		break;
	case ApplicationKeycode::APPK_F11:
		// return CEGUI::Key::F11;
		break;
	case ApplicationKeycode::APPK_F12:
		// return CEGUI::Key::F12;
		break;
	case ApplicationKeycode::APPK_F13:
		// return CEGUI::Key::F13;
		break;
	case ApplicationKeycode::APPK_F14:
		// return CEGUI::Key::F14;
		break;
	case ApplicationKeycode::APPK_F15:
		// return CEGUI::Key::F15;
		break;

	case ApplicationKeycode::APPK_LCTRL:
		for (std::vector<MovablePanel*>::iterator iit =
			SimulationManager::getSingleton()->getViewController().getMovablePanels().begin();
			iit
				!= SimulationManager::getSingleton()->getViewController().getMovablePanels().end();
			iit++) {
			(*iit)->hideTitleBar();
		}
		break;
	case ApplicationKeycode::APPK_LALT:
		// return CEGUI::Key::LeftAlt;
		break;
	case ApplicationKeycode::APPK_LSHIFT:
		// return CEGUI::Key::LeftShift;
		break;
		//case ApplicationKeycode::APPK_LSUPER: // return CEGUI::Key::LeftWindows;
		break;
	case ApplicationKeycode::APPK_RCTRL:
		// return CEGUI::Key::RightControl;
		break;
	case ApplicationKeycode::APPK_RALT:
		// return CEGUI::Key::RightAlt;
		break;
	case ApplicationKeycode::APPK_RSHIFT:
		// return CEGUI::Key::RightShift;
		break;
		//case ApplicationKeycode::APPK_RSUPER: // return CEGUI::Key::RightWindows;
		break;
	case ApplicationKeycode::APPK_MENU:
		// return CEGUI::Key::AppMenu;
		break;

	case ApplicationKeycode::APPK_KP_0:
		// return CEGUI::Key::Numpad0;
		break;
	case ApplicationKeycode::APPK_KP_1:
		// return CEGUI::Key::Numpad1;
		break;
	case ApplicationKeycode::APPK_KP_2:
		// return CEGUI::Key::Numpad2;
		break;
	case ApplicationKeycode::APPK_KP_3:
		// return CEGUI::Key::Numpad3;
		break;
	case ApplicationKeycode::APPK_KP_4:
		// return CEGUI::Key::Numpad4;
		break;
	case ApplicationKeycode::APPK_KP_5:
		// return CEGUI::Key::Numpad5;
		break;
	case ApplicationKeycode::APPK_KP_6:
		// return CEGUI::Key::Numpad6;
		break;
	case ApplicationKeycode::APPK_KP_7:
		// return CEGUI::Key::Numpad7;
		break;
	case ApplicationKeycode::APPK_KP_8:
		// return CEGUI::Key::Numpad8;
		break;
	case ApplicationKeycode::APPK_KP_9:
		// return CEGUI::Key::Numpad9;
		break;
	case ApplicationKeycode::APPK_KP_PERIOD:
		// return CEGUI::Key::Decimal;
		break;
	case ApplicationKeycode::APPK_KP_PLUS:
		// return CEGUI::Key::Add;
		break;
	case ApplicationKeycode::APPK_KP_MINUS:
		// return CEGUI::Key::Subtract;
		break;
	case ApplicationKeycode::APPK_KP_MULTIPLY:
		// return CEGUI::Key::Multiply;
		break;
	case ApplicationKeycode::APPK_KP_DIVIDE:
		// return CEGUI::Key::Divide;
		break;
	case ApplicationKeycode::APPK_KP_ENTER:
		// return CEGUI::Key::NumpadEnter;
		break;

	case ApplicationKeycode::APPK_UP:
		// return CEGUI::Key::ArrowUp;
		break;
	case ApplicationKeycode::APPK_LEFT:
		// return CEGUI::Key::ArrowLeft;
		break;
	case ApplicationKeycode::APPK_RIGHT:
		// return CEGUI::Key::ArrowRight;
		break;
	case ApplicationKeycode::APPK_DOWN:
		// return CEGUI::Key::ArrowDown;
		break;

	case ApplicationKeycode::APPK_HOME:
		// return CEGUI::Key::Home;
		break;
	case ApplicationKeycode::APPK_END:
		// return CEGUI::Key::End;
		break;
	case ApplicationKeycode::APPK_PAGEUP:
		// return CEGUI::Key::PageUp;
		break;
	case ApplicationKeycode::APPK_PAGEDOWN:
		// return CEGUI::Key::PageDown;
		break;
	case ApplicationKeycode::APPK_INSERT:
		// return CEGUI::Key::Insert;
		break;
	case ApplicationKeycode::APPK_DELETE:
		// return CEGUI::Key::Delete;
		break;
	}

//If CEGUI used the input, then return
	if (CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(
		(CEGUI::Key::Scan) InputUtils::convertToCEGUI(key))) {
		return true;
	}

	//hand value down to Ogre
	return OgreInputHandler::keyReleased(key);
}

void CEGUIInputHandler::injectTimeImpulse(const double tick) {
	/* inject the time that passed since the last call */
	CEGUI::System::getSingleton().injectTimePulse(float(tick - mCEGUIlastTick));
	mCEGUIlastTick = tick;
}

// CEGUI::MouseListener
bool CEGUIInputHandler::mouseMoved(const float x, const float y) {
	CEGUI::GUIContext& context =
		CEGUI::System::getSingleton().getDefaultGUIContext();

	context.injectMouseMove(x, y);

	return OgreInputHandler::mouseMoved(x, y);
}

// CEGUI:MouseWheelListener
bool CEGUIInputHandler::mouseWheelMoved(const float rel) {
	CEGUI::GUIContext& context =
		CEGUI::System::getSingleton().getDefaultGUIContext();
	// Scroll wheel.
	context.injectMouseWheelChange(rel / 120.0f);
	return OgreInputHandler::mouseWheelMoved(rel);
}

bool CEGUIInputHandler::mousePressed(
	const ApplicationMouseCode::MouseButton button) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "MOUSE BUTTON PRESSED" << button;
	CEGUI::GUIContext& context =
		CEGUI::System::getSingleton().getDefaultGUIContext();

	// Saving a mathgl graph to a file on right click
	CEGUI::Window* window = context.getWindowContainingMouse();
//	if (window != NULL
//			&& (window->getName() == "MathGLWindow"
//					|| window->getName() == "MathGLRTTWindow")
//			&& button == ApplicationMouseCode::RightButton) {
//		std::vector<MathGLPanel*>::iterator it =
//				SimulationManager::getSingleton()->getViewController().getGraphWindows().begin();
//		for (;
//				it
//						!= SimulationManager::getSingleton()->getViewController().getGraphWindows().end();
//				it++) {
//			if ((*it)->getMathGlWindow() == window
//					|| (*it)->getMathGlWindow()->getChild("MathGLRTTWindow")
//							== window) {
//				(*it)->makePrint();
//			}
//		}
//	}

	context.injectMouseButtonDown(InputUtils::convertToCEGUI(button));
	return OgreInputHandler::mousePressed(button);

}

bool CEGUIInputHandler::mouseReleased(
	const ApplicationMouseCode::MouseButton button) {
	CEGUI::GUIContext& context =
		CEGUI::System::getSingleton().getDefaultGUIContext();
	context.injectMouseButtonUp(InputUtils::convertToCEGUI(button));
	return OgreInputHandler::mouseReleased(button);
}

void CEGUIInputHandler::windowResized(int width, int height) const {
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(
		CEGUI::Sizef(width, height));
}

void CEGUIInputHandler::injectMousePosition(const float x,
	const float y) const {
	// Align CEGUI mouse with SDL2 mouse
	CEGUI::Vector2f mousePos =
		CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition();
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(
		x - mousePos.d_x, y - mousePos.d_y);
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Current mouse position SDL:" << x << "," << y;
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Current mouse position CEGUI:" << mousePos.d_x << "," << mousePos.d_y;
}

void CEGUIInputHandler::update(double timeSinceLastTick) {
	OgreInputHandler::update(timeSinceLastTick);
}

bool CEGUIInputHandler::acceptsInput() {
	bool acceptsInput =
		CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(34);
	if (acceptsInput) {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(
			CEGUI::Key::Backspace);
	}
	return acceptsInput;
}

bool CEGUIInputHandler::injectCharacter(char* character) const {
	return CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(
		character[0]);
}

bool CEGUIInputHandler::isCharacter(const ApplicationKeycode::Keycode key) {
	switch (key) {
	case ApplicationKeycode::APPK_1:
		// return CEGUI::Key::One;
	case ApplicationKeycode::APPK_2:
		// return CEGUI::Key::Two;
	case ApplicationKeycode::APPK_3:
		// return CEGUI::Key::Three;
	case ApplicationKeycode::APPK_4:
		// return CEGUI::Key::Four;
	case ApplicationKeycode::APPK_5:
		// return CEGUI::Key::Five;
	case ApplicationKeycode::APPK_6:
		// return CEGUI::Key::Six;
	case ApplicationKeycode::APPK_7:
		// return CEGUI::Key::Seven;
	case ApplicationKeycode::APPK_8:
		// return CEGUI::Key::Eight;
	case ApplicationKeycode::APPK_9:
		// return CEGUI::Key::Nine;
	case ApplicationKeycode::APPK_0:
		// return CEGUI::Key::Zero;
	case ApplicationKeycode::APPK_q:
		// return CEGUI::Key::Q;
	case ApplicationKeycode::APPK_w:
		// return CEGUI::Key::W;
	case ApplicationKeycode::APPK_e:
		// return CEGUI::Key::E;
	case ApplicationKeycode::APPK_r:
	case ApplicationKeycode::APPK_t:
	case ApplicationKeycode::APPK_y:
		// return CEGUI::Key::Y;
	case ApplicationKeycode::APPK_u:
		// return CEGUI::Key::U;
	case ApplicationKeycode::APPK_i:
		// return CEGUI::Key::I;
	case ApplicationKeycode::APPK_o:
		// return CEGUI::Key::O;
	case ApplicationKeycode::APPK_p:
		// return CEGUI::Key::P;
	case ApplicationKeycode::APPK_a:
		// return CEGUI::Key::A;
	case ApplicationKeycode::APPK_s:
		// return CEGUI::Key::S;
	case ApplicationKeycode::APPK_d:
		// return CEGUI::Key::D;
	case ApplicationKeycode::APPK_f:
	case ApplicationKeycode::APPK_g:
	case ApplicationKeycode::APPK_h:
		// return CEGUI::Key::H;
	case ApplicationKeycode::APPK_j:
		// return CEGUI::Key::J;
	case ApplicationKeycode::APPK_k:
		// return CEGUI::Key::K;
	case ApplicationKeycode::APPK_l:
		// return CEGUI::Key::L;
	case ApplicationKeycode::APPK_z:
		// return CEGUI::Key::Z;
	case ApplicationKeycode::APPK_x:
		// return CEGUI::Key::X;
	case ApplicationKeycode::APPK_c:
		// return CEGUI::Key::C;
	case ApplicationKeycode::APPK_v:
		// return CEGUI::Key::V;
	case ApplicationKeycode::APPK_b:
		// return CEGUI::Key::B;
	case ApplicationKeycode::APPK_n:
		// return CEGUI::Key::N;
	case ApplicationKeycode::APPK_m:
		// return CEGUI::Key::M;
	case ApplicationKeycode::APPK_COMMA:
		// return CEGUI::Key::Comma;
	case ApplicationKeycode::APPK_PERIOD:
		// return CEGUI::Key::Period;
	case ApplicationKeycode::APPK_SLASH:
		// return CEGUI::Key::Slash;
	case ApplicationKeycode::APPK_BACKSLASH:
		// return CEGUI::Key::Backslash;
	case ApplicationKeycode::APPK_MINUS:
		// return CEGUI::Key::Minus;
	case ApplicationKeycode::APPK_EQUALS:
		// return CEGUI::Key::Equals;
	case ApplicationKeycode::APPK_SEMICOLON:
		// return CEGUI::Key::Semicolon;
	case ApplicationKeycode::APPK_LEFTBRACKET:
		// return CEGUI::Key::LeftBracket;
	case ApplicationKeycode::APPK_RIGHTBRACKET:
		// return CEGUI::Key::RightBracket;
	case ApplicationKeycode::APPK_QUOTE:
		// return CEGUI::Key::Apostrophe;
	case ApplicationKeycode::APPK_BACKQUOTE:
		// return CEGUI::Key::Grave;
	case ApplicationKeycode::APPK_KP_0:
		// return CEGUI::Key::Numpad0;
	case ApplicationKeycode::APPK_KP_1:
		// return CEGUI::Key::Numpad1;
	case ApplicationKeycode::APPK_KP_2:
		// return CEGUI::Key::Numpad2;
	case ApplicationKeycode::APPK_KP_3:
		// return CEGUI::Key::Numpad3;
	case ApplicationKeycode::APPK_KP_4:
		// return CEGUI::Key::Numpad4;
	case ApplicationKeycode::APPK_KP_5:
		// return CEGUI::Key::Numpad5;
	case ApplicationKeycode::APPK_KP_6:
		// return CEGUI::Key::Numpad6;
	case ApplicationKeycode::APPK_KP_7:
		// return CEGUI::Key::Numpad7;
	case ApplicationKeycode::APPK_KP_8:
		// return CEGUI::Key::Numpad8;
	case ApplicationKeycode::APPK_KP_9:
		// return CEGUI::Key::Numpad9;
	case ApplicationKeycode::APPK_KP_PERIOD:
		// return CEGUI::Key::Decimal;
	case ApplicationKeycode::APPK_KP_PLUS:
		// return CEGUI::Key::Add;
	case ApplicationKeycode::APPK_KP_MINUS:
		// return CEGUI::Key::Subtract;
	case ApplicationKeycode::APPK_KP_MULTIPLY:
		// return CEGUI::Key::Multiply;
	case ApplicationKeycode::APPK_KP_DIVIDE:
		return true;
		break;
	default:
		return false;
		break;
	}
}
