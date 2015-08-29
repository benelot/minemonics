#ifndef CONTROLLER_INPUT_INPUTUTILS_HPP_
#define CONTROLLER_INPUT_INPUTUTILS_HPP_

//# corresponding headers
//# forward declarations
//# system headers

//## controller headers
//## model headers
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <CEGUI/InputEvent.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
#include <controller/input/ApplicationKeycode.hpp>
#include <controller/input/ApplicationMousecode.hpp>

//## model headers
//## view headers
//## utils headers

/**
 * @brief		The InputUtils help to convert between the keyboard and mouse definitions of each sub system.
 * @details		Details
 * @date		2015-05-04
 * @author		Benjamin Ellenberger
 */
class InputUtils {
public:

	/**
	 * Convert an SDL2 mouse button into an Ogre3D mouse button.
	 * @param button The SDL2 mouse button.
	 * @return The Ogre3D mouse button.
	 */
	static ApplicationMouseCode::MouseButton convertToOgre3D(Uint8 button) {
		switch (button) {
		case SDL_BUTTON_LEFT:
			return ApplicationMouseCode::LeftButton;
			break;

		case SDL_BUTTON_RIGHT:
			return ApplicationMouseCode::RightButton;
			break;

		case SDL_BUTTON_MIDDLE:
			return ApplicationMouseCode::MiddleButton;
			break;

		default:
			return ApplicationMouseCode::NoButton;
			break;
		}
		return ApplicationMouseCode::NoButton;
	}

	/**
	 * Convert an Ogre3D mouse button to an SDL2 mouse button.
	 * @param button The Ogre3D mouse button.
	 * @return The SDL2 mouse button.
	 */
	static Uint8 convertToSDL2(ApplicationMouseCode::MouseButton button) {
		switch (button) {
		case ApplicationMouseCode::LeftButton:
			return SDL_BUTTON_LEFT;
			break;

		case ApplicationMouseCode::RightButton:
			return SDL_BUTTON_RIGHT;
			break;

		case ApplicationMouseCode::MiddleButton:
			return SDL_BUTTON_MIDDLE;
			break;

		default:
			return -1;
			break;
		}
		return -1;
	}

	/**
	 * Convert an SDL2 keycode to an Ogre3D keycode.
	 * @param key The SDL2 keycode.
	 * @return The Ogre3D keycode.
	 */
	static ApplicationKeycode::Keycode convertToOgre3D(SDL_Keycode key) {
		switch (key) {
		case SDLK_1:
			return ApplicationKeycode::APPK_1;
			break;
		case SDLK_2:
			return ApplicationKeycode::APPK_2;
			break;
		case SDLK_3:
			return ApplicationKeycode::APPK_3;
			break;
		case SDLK_4:
			return ApplicationKeycode::APPK_4;
			break;
		case SDLK_5:
			return ApplicationKeycode::APPK_5;
			break;
		case SDLK_6:
			return ApplicationKeycode::APPK_6;
			break;
		case SDLK_7:
			return ApplicationKeycode::APPK_7;
			break;
		case SDLK_8:
			return ApplicationKeycode::APPK_8;
			break;
		case SDLK_9:
			return ApplicationKeycode::APPK_9;
			break;
		case SDLK_0:
			return ApplicationKeycode::APPK_0;
			break;

		case SDLK_q:
			return ApplicationKeycode::APPK_q;
			break;
		case SDLK_w:
			return ApplicationKeycode::APPK_w;
			break;
		case SDLK_e:
			return ApplicationKeycode::APPK_e;
			break;
		case SDLK_r:
			return ApplicationKeycode::APPK_r;
			break;
		case SDLK_t:
			return ApplicationKeycode::APPK_t;
			break;
		case SDLK_y:
			return ApplicationKeycode::APPK_y;
			break;
		case SDLK_u:
			return ApplicationKeycode::APPK_u;
			break;
		case SDLK_i:
			return ApplicationKeycode::APPK_i;
			break;
		case SDLK_o:
			return ApplicationKeycode::APPK_o;
			break;
		case SDLK_p:
			return ApplicationKeycode::APPK_p;
			break;
		case SDLK_a:
			return ApplicationKeycode::APPK_a;
			break;
		case SDLK_s:
			return ApplicationKeycode::APPK_s;
			break;
		case SDLK_d:
			return ApplicationKeycode::APPK_d;
			break;
		case SDLK_f:
			return ApplicationKeycode::APPK_f;
			break;
		case SDLK_g:
			return ApplicationKeycode::APPK_g;
			break;
		case SDLK_h:
			return ApplicationKeycode::APPK_h;
			break;
		case SDLK_j:
			return ApplicationKeycode::APPK_j;
			break;
		case SDLK_k:
			return ApplicationKeycode::APPK_k;
			break;
		case SDLK_l:
			return ApplicationKeycode::APPK_l;
			break;
		case SDLK_z:
			return ApplicationKeycode::APPK_z;
			break;
		case SDLK_x:
			return ApplicationKeycode::APPK_x;
			break;
		case SDLK_c:
			return ApplicationKeycode::APPK_c;
			break;
		case SDLK_v:
			return ApplicationKeycode::APPK_v;
			break;
		case SDLK_b:
			return ApplicationKeycode::APPK_b;
			break;
		case SDLK_n:
			return ApplicationKeycode::APPK_n;
			break;
		case SDLK_m:
			return ApplicationKeycode::APPK_m;
			break;

		case SDLK_COMMA:
			return ApplicationKeycode::APPK_COMMA;
			break;
		case SDLK_PERIOD:
			return ApplicationKeycode::APPK_PERIOD;
			break;
		case SDLK_SLASH:
			return ApplicationKeycode::APPK_SLASH;
			break;
		case SDLK_BACKSLASH:
			return ApplicationKeycode::APPK_BACKSLASH;
			break;
		case SDLK_MINUS:
			return ApplicationKeycode::APPK_MINUS;
			break;
		case SDLK_EQUALS:
			return ApplicationKeycode::APPK_EQUALS;
			break;
		case SDLK_SEMICOLON:
			return ApplicationKeycode::APPK_SEMICOLON;
			break;
		case SDLK_LEFTBRACKET:
			return ApplicationKeycode::APPK_LEFTBRACKET;
			break;
		case SDLK_RIGHTBRACKET:
			return ApplicationKeycode::APPK_RIGHTBRACKET;
			break;
		case SDLK_QUOTE:
			return ApplicationKeycode::APPK_QUOTE;
			break;
		case SDLK_BACKQUOTE:
			return ApplicationKeycode::APPK_BACKQUOTE;
			break;

		case SDLK_RETURN:
			return ApplicationKeycode::APPK_RETURN;
			break;
		case SDLK_SPACE:
			return ApplicationKeycode::APPK_SPACE;
			break;
		case SDLK_BACKSPACE:
			return ApplicationKeycode::APPK_BACKSPACE;
			break;
		case SDLK_TAB:
			return ApplicationKeycode::APPK_TAB;
			break;

		case SDLK_ESCAPE:
			return ApplicationKeycode::APPK_ESCAPE;
			break;
		case SDLK_PAUSE:
			return ApplicationKeycode::APPK_PAUSE;
			break;
		case SDLK_SYSREQ:
			return ApplicationKeycode::APPK_SYSREQ;
			break;
		case SDLK_POWER:
			return ApplicationKeycode::APPK_POWER;
			break;

			//case SDLK_NUMLOCK: return ApplicationKeycode::APPK_NUMLOCK;
			break;
		case SDLK_SCROLLLOCK:
			return ApplicationKeycode::APPK_SCROLLLOCK;
			break;

		case SDLK_F1:
			return ApplicationKeycode::APPK_F1;
			break;
		case SDLK_F2:
			return ApplicationKeycode::APPK_F2;
			break;
		case SDLK_F3:
			return ApplicationKeycode::APPK_F3;
			break;
		case SDLK_F4:
			return ApplicationKeycode::APPK_F4;
			break;
		case SDLK_F5:
			return ApplicationKeycode::APPK_F5;
			break;
		case SDLK_F6:
			return ApplicationKeycode::APPK_F6;
			break;
		case SDLK_F7:
			return ApplicationKeycode::APPK_F7;
			break;
		case SDLK_F8:
			return ApplicationKeycode::APPK_F8;
			break;
		case SDLK_F9:
			return ApplicationKeycode::APPK_F9;
			break;
		case SDLK_F10:
			return ApplicationKeycode::APPK_F10;
			break;
		case SDLK_F11:
			return ApplicationKeycode::APPK_F11;
			break;
		case SDLK_F12:
			return ApplicationKeycode::APPK_F12;
			break;
		case SDLK_F13:
			return ApplicationKeycode::APPK_F13;
			break;
		case SDLK_F14:
			return ApplicationKeycode::APPK_F14;
			break;
		case SDLK_F15:
			return ApplicationKeycode::APPK_F15;
			break;

		case SDLK_LCTRL:
			return ApplicationKeycode::APPK_LCTRL;
			break;
		case SDLK_LALT:
			return ApplicationKeycode::APPK_LALT;
			break;
		case SDLK_LSHIFT:
			return ApplicationKeycode::APPK_LSHIFT;
			break;
			//case SDLK_LSUPER: return APPK_LeftWindows;
			break;
		case SDLK_RCTRL:
			return ApplicationKeycode::APPK_RCTRL;
			break;
		case SDLK_RALT:
			return ApplicationKeycode::APPK_RALT;
			break;
		case SDLK_RSHIFT:
			return ApplicationKeycode::APPK_RSHIFT;
			break;
			//case SDLK_RSUPER: return APPK_RightWindows;
			break;
		case SDLK_MENU:
			return ApplicationKeycode::APPK_MENU;
			break;

		case SDLK_KP_0:
			return ApplicationKeycode::APPK_KP_0;
			break;
		case SDLK_KP_1:
			return ApplicationKeycode::APPK_KP_1;
			break;
		case SDLK_KP_2:
			return ApplicationKeycode::APPK_KP_2;
			break;
		case SDLK_KP_3:
			return ApplicationKeycode::APPK_KP_3;
			break;
		case SDLK_KP_4:
			return ApplicationKeycode::APPK_KP_4;
			break;
		case SDLK_KP_5:
			return ApplicationKeycode::APPK_KP_5;
			break;
		case SDLK_KP_6:
			return ApplicationKeycode::APPK_KP_6;
			break;
		case SDLK_KP_7:
			return ApplicationKeycode::APPK_KP_7;
			break;
		case SDLK_KP_8:
			return ApplicationKeycode::APPK_KP_8;
			break;
		case SDLK_KP_9:
			return ApplicationKeycode::APPK_KP_9;
			break;
		case SDLK_KP_PERIOD:
			return ApplicationKeycode::APPK_KP_PERIOD;
			break;
		case SDLK_KP_PLUS:
			return ApplicationKeycode::APPK_KP_PLUS;
			break;
		case SDLK_KP_MINUS:
			return ApplicationKeycode::APPK_KP_MINUS;
			break;
		case SDLK_KP_MULTIPLY:
			return ApplicationKeycode::APPK_KP_MULTIPLY;
			break;
		case SDLK_KP_DIVIDE:
			return ApplicationKeycode::APPK_KP_DIVIDE;
			break;
		case SDLK_KP_ENTER:
			return ApplicationKeycode::APPK_KP_ENTER;
			break;

		case SDLK_UP:
			return ApplicationKeycode::APPK_UP;
			break;
		case SDLK_LEFT:
			return ApplicationKeycode::APPK_LEFT;
			break;
		case SDLK_RIGHT:
			return ApplicationKeycode::APPK_RIGHT;
			break;
		case SDLK_DOWN:
			return ApplicationKeycode::APPK_DOWN;
			break;

		case SDLK_HOME:
			return ApplicationKeycode::APPK_HOME;
			break;
		case SDLK_END:
			return ApplicationKeycode::APPK_END;
			break;
		case SDLK_PAGEUP:
			return ApplicationKeycode::APPK_PAGEUP;
			break;
		case SDLK_PAGEDOWN:
			return ApplicationKeycode::APPK_PAGEDOWN;
			break;
		case SDLK_INSERT:
			return ApplicationKeycode::APPK_INSERT;
			break;
		case SDLK_DELETE:
			return ApplicationKeycode::APPK_DELETE;
			break;
		}
		return ApplicationKeycode::APPK_UNKNOWN;
	}

	/**
	 * Not implemented yet! Convert an Ogre3D keycode to an SDL2 keycode.
	 * @param key The Ogre3D keycode.
	 * @return The SDL2 keycode.
	 *
	 */
	static SDL_Keycode convertToSDL2(ApplicationKeycode::Keycode key) {
		//TODO: Implement if necessary.
		switch (key) {
		case ApplicationKeycode::APPK_1:
			//return CEGUI::Key::One;
			break;
		case ApplicationKeycode::APPK_2:
			//return CEGUI::Key::Two;
			break;
		case ApplicationKeycode::APPK_3:
			//return CEGUI::Key::Three;
			break;
		case ApplicationKeycode::APPK_4:
			//return CEGUI::Key::Four;
			break;
		case ApplicationKeycode::APPK_5:
			//return CEGUI::Key::Five;
			break;
		case ApplicationKeycode::APPK_6:
			//return CEGUI::Key::Six;
			break;
		case ApplicationKeycode::APPK_7:
			//return CEGUI::Key::Seven;
			break;
		case ApplicationKeycode::APPK_8:
			//return CEGUI::Key::Eight;
			break;
		case ApplicationKeycode::APPK_9:
			//return CEGUI::Key::Nine;
			break;
		case ApplicationKeycode::APPK_0:
			//return CEGUI::Key::Zero;
			break;

		case ApplicationKeycode::APPK_q:
			//return CEGUI::Key::Q;
			break;
		case ApplicationKeycode::APPK_w:
			//return CEGUI::Key::W;
			break;
		case ApplicationKeycode::APPK_e:
			//return CEGUI::Key::E;
			break;
		case ApplicationKeycode::APPK_r:
			//return CEGUI::Key::R;
			break;
		case ApplicationKeycode::APPK_t:
			//return CEGUI::Key::T;
			break;
		case ApplicationKeycode::APPK_y:
			//return CEGUI::Key::Y;
			break;
		case ApplicationKeycode::APPK_u:
			//return CEGUI::Key::U;
			break;
		case ApplicationKeycode::APPK_i:
			//return CEGUI::Key::I;
			break;
		case ApplicationKeycode::APPK_o:
			//return CEGUI::Key::O;
			break;
		case ApplicationKeycode::APPK_p:
			//return CEGUI::Key::P;
			break;
		case ApplicationKeycode::APPK_a:
			//return CEGUI::Key::A;
			break;
		case ApplicationKeycode::APPK_s:
			//return CEGUI::Key::S;
			break;
		case ApplicationKeycode::APPK_d:
			//return CEGUI::Key::D;
			break;
		case ApplicationKeycode::APPK_f:
			//return CEGUI::Key::F;
			break;
		case ApplicationKeycode::APPK_g:
			//return CEGUI::Key::G;
			break;
		case ApplicationKeycode::APPK_h:
			//return CEGUI::Key::H;
			break;
		case ApplicationKeycode::APPK_j:
			//return CEGUI::Key::J;
			break;
		case ApplicationKeycode::APPK_k:
			//return CEGUI::Key::K;
			break;
		case ApplicationKeycode::APPK_l:
			//return CEGUI::Key::L;
			break;
		case ApplicationKeycode::APPK_z:
			//return CEGUI::Key::Z;
			break;
		case ApplicationKeycode::APPK_x:
			//return CEGUI::Key::X;
			break;
		case ApplicationKeycode::APPK_c:
			//return CEGUI::Key::C;
			break;
		case ApplicationKeycode::APPK_v:
			//return CEGUI::Key::V;
			break;
		case ApplicationKeycode::APPK_b:
			//return CEGUI::Key::B;
			break;
		case ApplicationKeycode::APPK_n:
			//return CEGUI::Key::N;
			break;
		case ApplicationKeycode::APPK_m:
			//return CEGUI::Key::M;
			break;

		case ApplicationKeycode::APPK_COMMA:
			//return CEGUI::Key::Comma;
			break;
		case ApplicationKeycode::APPK_PERIOD:
			//return CEGUI::Key::Period;
			break;
		case ApplicationKeycode::APPK_SLASH:
			//return CEGUI::Key::Slash;
			break;
		case ApplicationKeycode::APPK_BACKSLASH:
			//return CEGUI::Key::Backslash;
			break;
		case ApplicationKeycode::APPK_MINUS:
			//return CEGUI::Key::Minus;
			break;
		case ApplicationKeycode::APPK_EQUALS:
			//return CEGUI::Key::Equals;
			break;
		case ApplicationKeycode::APPK_SEMICOLON:
			//return CEGUI::Key::Semicolon;
			break;
		case ApplicationKeycode::APPK_LEFTBRACKET:
			//return CEGUI::Key::LeftBracket;
			break;
		case ApplicationKeycode::APPK_RIGHTBRACKET:
			//return CEGUI::Key::RightBracket;
			break;
		case ApplicationKeycode::APPK_QUOTE:
			//return CEGUI::Key::Apostrophe;
			break;
		case ApplicationKeycode::APPK_BACKQUOTE:
			//return CEGUI::Key::Grave;
			break;

		case ApplicationKeycode::APPK_RETURN:
			//return CEGUI::Key:://return;
			break;
		case ApplicationKeycode::APPK_SPACE:
			//return CEGUI::Key::Space;
			break;
		case ApplicationKeycode::APPK_BACKSPACE:
			//return CEGUI::Key::Backspace;
			break;
		case ApplicationKeycode::APPK_TAB:
			//return CEGUI::Key::Tab;
			break;

		case ApplicationKeycode::APPK_ESCAPE:
			//return CEGUI::Key::Escape;
			break;
		case ApplicationKeycode::APPK_PAUSE:
			//return CEGUI::Key::Pause;
			break;
		case ApplicationKeycode::APPK_SYSREQ:
			//return CEGUI::Key::SysRq;
			break;
		case ApplicationKeycode::APPK_POWER:
			//return CEGUI::Key::Power;
			break;

			//case ApplicationKeycode::APPK_NUMLOCK:
			//return CEGUI::Key::NumLock;
			break;
		case ApplicationKeycode::APPK_SCROLLLOCK:
			//return CEGUI::Key::ScrollLock;
			break;

		case ApplicationKeycode::APPK_F1:
			//return CEGUI::Key::F1;
			break;
		case ApplicationKeycode::APPK_F2:
			//return CEGUI::Key::F2;
			break;
		case ApplicationKeycode::APPK_F3:
			//return CEGUI::Key::F3;
			break;
		case ApplicationKeycode::APPK_F4:
			//return CEGUI::Key::F4;
			break;
		case ApplicationKeycode::APPK_F5:
			//return CEGUI::Key::F5;
			break;
		case ApplicationKeycode::APPK_F6:
			//return CEGUI::Key::F6;
			break;
		case ApplicationKeycode::APPK_F7:
			//return CEGUI::Key::F7;
			break;
		case ApplicationKeycode::APPK_F8:
			//return CEGUI::Key::F8;
			break;
		case ApplicationKeycode::APPK_F9:
			//return CEGUI::Key::F9;
			break;
		case ApplicationKeycode::APPK_F10:
			//return CEGUI::Key::F10;
			break;
		case ApplicationKeycode::APPK_F11:
			//return CEGUI::Key::F11;
			break;
		case ApplicationKeycode::APPK_F12:
			//return CEGUI::Key::F12;
			break;
		case ApplicationKeycode::APPK_F13:
			//return CEGUI::Key::F13;
			break;
		case ApplicationKeycode::APPK_F14:
			//return CEGUI::Key::F14;
			break;
		case ApplicationKeycode::APPK_F15:
			//return CEGUI::Key::F15;
			break;

		case ApplicationKeycode::APPK_LCTRL:
			//return CEGUI::Key::LeftControl;
			break;
		case ApplicationKeycode::APPK_LALT:
			//return CEGUI::Key::LeftAlt;
			break;
		case ApplicationKeycode::APPK_LSHIFT:
			//return CEGUI::Key::LeftShift;
			break;
			//case ApplicationKeycode::APPK_LSUPER: //return CEGUI::Key::LeftWindows;
			break;
		case ApplicationKeycode::APPK_RCTRL:
			//return CEGUI::Key::RightControl;
			break;
		case ApplicationKeycode::APPK_RALT:
			//return CEGUI::Key::RightAlt;
			break;
		case ApplicationKeycode::APPK_RSHIFT:
			//return CEGUI::Key::RightShift;
			break;
			//case ApplicationKeycode::APPK_RSUPER: //return CEGUI::Key::RightWindows;
			break;
		case ApplicationKeycode::APPK_MENU:
			//return CEGUI::Key::AppMenu;
			break;

		case ApplicationKeycode::APPK_KP_0:
			//return CEGUI::Key::Numpad0;
			break;
		case ApplicationKeycode::APPK_KP_1:
			//return CEGUI::Key::Numpad1;
			break;
		case ApplicationKeycode::APPK_KP_2:
			//return CEGUI::Key::Numpad2;
			break;
		case ApplicationKeycode::APPK_KP_3:
			//return CEGUI::Key::Numpad3;
			break;
		case ApplicationKeycode::APPK_KP_4:
			//return CEGUI::Key::Numpad4;
			break;
		case ApplicationKeycode::APPK_KP_5:
			//return CEGUI::Key::Numpad5;
			break;
		case ApplicationKeycode::APPK_KP_6:
			//return CEGUI::Key::Numpad6;
			break;
		case ApplicationKeycode::APPK_KP_7:
			//return CEGUI::Key::Numpad7;
			break;
		case ApplicationKeycode::APPK_KP_8:
			//return CEGUI::Key::Numpad8;
			break;
		case ApplicationKeycode::APPK_KP_9:
			//return CEGUI::Key::Numpad9;
			break;
		case ApplicationKeycode::APPK_KP_PERIOD:
			//return CEGUI::Key::Decimal;
			break;
		case ApplicationKeycode::APPK_KP_PLUS:
			//return CEGUI::Key::Add;
			break;
		case ApplicationKeycode::APPK_KP_MINUS:
			//return CEGUI::Key::Subtract;
			break;
		case ApplicationKeycode::APPK_KP_MULTIPLY:
			//return CEGUI::Key::Multiply;
			break;
		case ApplicationKeycode::APPK_KP_DIVIDE:
			//return CEGUI::Key::Divide;
			break;
		case ApplicationKeycode::APPK_KP_ENTER:
			//return CEGUI::Key::NumpadEnter;
			break;

		case ApplicationKeycode::APPK_UP:
			//return CEGUI::Key::ArrowUp;
			break;
		case ApplicationKeycode::APPK_LEFT:
			//return CEGUI::Key::ArrowLeft;
			break;
		case ApplicationKeycode::APPK_RIGHT:
			//return CEGUI::Key::ArrowRight;
			break;
		case ApplicationKeycode::APPK_DOWN:
			//return CEGUI::Key::ArrowDown;
			break;

		case ApplicationKeycode::APPK_HOME:
			//return CEGUI::Key::Home;
			break;
		case ApplicationKeycode::APPK_END:
			//return CEGUI::Key::End;
			break;
		case ApplicationKeycode::APPK_PAGEUP:
			//return CEGUI::Key::PageUp;
			break;
		case ApplicationKeycode::APPK_PAGEDOWN:
			//return CEGUI::Key::PageDown;
			break;
		case ApplicationKeycode::APPK_INSERT:
			//return CEGUI::Key::Insert;
			break;
		case ApplicationKeycode::APPK_DELETE:
			//return CEGUI::Key::Delete;
			break;
		}
		//TODO: Find SDL2 key unknown.
		return -1;
	}

	/**
	 * Convert an Ogre3D mouse button to a CEGUI mouse button.
	 * @param button The Ogre3D mouse button.
	 * @return The CEGUI mouse button.
	 */
	static CEGUI::MouseButton convertToCEGUI(
		ApplicationMouseCode::MouseButton button) {
		switch (button) {
		case ApplicationMouseCode::LeftButton:
			return CEGUI::LeftButton;
			break;

		case ApplicationMouseCode::RightButton:
			return CEGUI::RightButton;
			break;

		case ApplicationMouseCode::MiddleButton:
			return CEGUI::MiddleButton;
			break;

		default:
			return CEGUI::NoButton;
			break;
		}
		return CEGUI::NoButton;
	}
	/**
	 * Convert an Ogre3D keycode into a CEGUI keycode.
	 * @param key The Ogre3D keycode.
	 * @return The CEGUI keycode.
	 */
	static CEGUI::Key::Scan convertToCEGUI(ApplicationKeycode::Keycode key) {
		switch (key) {
		case ApplicationKeycode::APPK_1:
			return CEGUI::Key::One;
			break;
		case ApplicationKeycode::APPK_2:
			return CEGUI::Key::Two;
			break;
		case ApplicationKeycode::APPK_3:
			return CEGUI::Key::Three;
			break;
		case ApplicationKeycode::APPK_4:
			return CEGUI::Key::Four;
			break;
		case ApplicationKeycode::APPK_5:
			return CEGUI::Key::Five;
			break;
		case ApplicationKeycode::APPK_6:
			return CEGUI::Key::Six;
			break;
		case ApplicationKeycode::APPK_7:
			return CEGUI::Key::Seven;
			break;
		case ApplicationKeycode::APPK_8:
			return CEGUI::Key::Eight;
			break;
		case ApplicationKeycode::APPK_9:
			return CEGUI::Key::Nine;
			break;
		case ApplicationKeycode::APPK_0:
			return CEGUI::Key::Zero;
			break;

		case ApplicationKeycode::APPK_q:
			return CEGUI::Key::Q;
			break;
		case ApplicationKeycode::APPK_w:
			return CEGUI::Key::W;
			break;
		case ApplicationKeycode::APPK_e:
			return CEGUI::Key::E;
			break;
		case ApplicationKeycode::APPK_r:
			return CEGUI::Key::R;
			break;
		case ApplicationKeycode::APPK_t:
			return CEGUI::Key::T;
			break;
		case ApplicationKeycode::APPK_y:
			return CEGUI::Key::Y;
			break;
		case ApplicationKeycode::APPK_u:
			return CEGUI::Key::U;
			break;
		case ApplicationKeycode::APPK_i:
			return CEGUI::Key::I;
			break;
		case ApplicationKeycode::APPK_o:
			return CEGUI::Key::O;
			break;
		case ApplicationKeycode::APPK_p:
			return CEGUI::Key::P;
			break;
		case ApplicationKeycode::APPK_a:
			return CEGUI::Key::A;
			break;
		case ApplicationKeycode::APPK_s:
			return CEGUI::Key::S;
			break;
		case ApplicationKeycode::APPK_d:
			return CEGUI::Key::D;
			break;
		case ApplicationKeycode::APPK_f:
			return CEGUI::Key::F;
			break;
		case ApplicationKeycode::APPK_g:
			return CEGUI::Key::G;
			break;
		case ApplicationKeycode::APPK_h:
			return CEGUI::Key::H;
			break;
		case ApplicationKeycode::APPK_j:
			return CEGUI::Key::J;
			break;
		case ApplicationKeycode::APPK_k:
			return CEGUI::Key::K;
			break;
		case ApplicationKeycode::APPK_l:
			return CEGUI::Key::L;
			break;
		case ApplicationKeycode::APPK_z:
			return CEGUI::Key::Z;
			break;
		case ApplicationKeycode::APPK_x:
			return CEGUI::Key::X;
			break;
		case ApplicationKeycode::APPK_c:
			return CEGUI::Key::C;
			break;
		case ApplicationKeycode::APPK_v:
			return CEGUI::Key::V;
			break;
		case ApplicationKeycode::APPK_b:
			return CEGUI::Key::B;
			break;
		case ApplicationKeycode::APPK_n:
			return CEGUI::Key::N;
			break;
		case ApplicationKeycode::APPK_m:
			return CEGUI::Key::M;
			break;

		case ApplicationKeycode::APPK_COMMA:
			return CEGUI::Key::Comma;
			break;
		case ApplicationKeycode::APPK_PERIOD:
			return CEGUI::Key::Period;
			break;
		case ApplicationKeycode::APPK_SLASH:
			return CEGUI::Key::Slash;
			break;
		case ApplicationKeycode::APPK_BACKSLASH:
			return CEGUI::Key::Backslash;
			break;
		case ApplicationKeycode::APPK_MINUS:
			return CEGUI::Key::Minus;
			break;
		case ApplicationKeycode::APPK_EQUALS:
			return CEGUI::Key::Equals;
			break;
		case ApplicationKeycode::APPK_SEMICOLON:
			return CEGUI::Key::Semicolon;
			break;
		case ApplicationKeycode::APPK_LEFTBRACKET:
			return CEGUI::Key::LeftBracket;
			break;
		case ApplicationKeycode::APPK_RIGHTBRACKET:
			return CEGUI::Key::RightBracket;
			break;
		case ApplicationKeycode::APPK_QUOTE:
			return CEGUI::Key::Apostrophe;
			break;
		case ApplicationKeycode::APPK_BACKQUOTE:
			return CEGUI::Key::Grave;
			break;

		case ApplicationKeycode::APPK_RETURN:
			return CEGUI::Key::Return;
			break;
		case ApplicationKeycode::APPK_SPACE:
			return CEGUI::Key::Space;
			break;
		case ApplicationKeycode::APPK_BACKSPACE:
			return CEGUI::Key::Backspace;
			break;
		case ApplicationKeycode::APPK_TAB:
			return CEGUI::Key::Tab;
			break;

		case ApplicationKeycode::APPK_ESCAPE:
			return CEGUI::Key::Escape;
			break;
		case ApplicationKeycode::APPK_PAUSE:
			return CEGUI::Key::Pause;
			break;
		case ApplicationKeycode::APPK_SYSREQ:
			return CEGUI::Key::SysRq;
			break;
		case ApplicationKeycode::APPK_POWER:
			return CEGUI::Key::Power;
			break;

			//case ApplicationKeycode::APPK_NUMLOCK:
			return CEGUI::Key::NumLock;
			break;
		case ApplicationKeycode::APPK_SCROLLLOCK:
			return CEGUI::Key::ScrollLock;
			break;

		case ApplicationKeycode::APPK_F1:
			return CEGUI::Key::F1;
			break;
		case ApplicationKeycode::APPK_F2:
			return CEGUI::Key::F2;
			break;
		case ApplicationKeycode::APPK_F3:
			return CEGUI::Key::F3;
			break;
		case ApplicationKeycode::APPK_F4:
			return CEGUI::Key::F4;
			break;
		case ApplicationKeycode::APPK_F5:
			return CEGUI::Key::F5;
			break;
		case ApplicationKeycode::APPK_F6:
			return CEGUI::Key::F6;
			break;
		case ApplicationKeycode::APPK_F7:
			return CEGUI::Key::F7;
			break;
		case ApplicationKeycode::APPK_F8:
			return CEGUI::Key::F8;
			break;
		case ApplicationKeycode::APPK_F9:
			return CEGUI::Key::F9;
			break;
		case ApplicationKeycode::APPK_F10:
			return CEGUI::Key::F10;
			break;
		case ApplicationKeycode::APPK_F11:
			return CEGUI::Key::F11;
			break;
		case ApplicationKeycode::APPK_F12:
			return CEGUI::Key::F12;
			break;
		case ApplicationKeycode::APPK_F13:
			return CEGUI::Key::F13;
			break;
		case ApplicationKeycode::APPK_F14:
			return CEGUI::Key::F14;
			break;
		case ApplicationKeycode::APPK_F15:
			return CEGUI::Key::F15;
			break;

		case ApplicationKeycode::APPK_LCTRL:
			return CEGUI::Key::LeftControl;
			break;
		case ApplicationKeycode::APPK_LALT:
			return CEGUI::Key::LeftAlt;
			break;
		case ApplicationKeycode::APPK_LSHIFT:
			return CEGUI::Key::LeftShift;
			break;
			//case ApplicationKeycode::APPK_LSUPER: return CEGUI::Key::LeftWindows;
			break;
		case ApplicationKeycode::APPK_RCTRL:
			return CEGUI::Key::RightControl;
			break;
		case ApplicationKeycode::APPK_RALT:
			return CEGUI::Key::RightAlt;
			break;
		case ApplicationKeycode::APPK_RSHIFT:
			return CEGUI::Key::RightShift;
			break;
			//case ApplicationKeycode::APPK_RSUPER: return CEGUI::Key::RightWindows;
			break;
		case ApplicationKeycode::APPK_MENU:
			return CEGUI::Key::AppMenu;
			break;

		case ApplicationKeycode::APPK_KP_0:
			return CEGUI::Key::Numpad0;
			break;
		case ApplicationKeycode::APPK_KP_1:
			return CEGUI::Key::Numpad1;
			break;
		case ApplicationKeycode::APPK_KP_2:
			return CEGUI::Key::Numpad2;
			break;
		case ApplicationKeycode::APPK_KP_3:
			return CEGUI::Key::Numpad3;
			break;
		case ApplicationKeycode::APPK_KP_4:
			return CEGUI::Key::Numpad4;
			break;
		case ApplicationKeycode::APPK_KP_5:
			return CEGUI::Key::Numpad5;
			break;
		case ApplicationKeycode::APPK_KP_6:
			return CEGUI::Key::Numpad6;
			break;
		case ApplicationKeycode::APPK_KP_7:
			return CEGUI::Key::Numpad7;
			break;
		case ApplicationKeycode::APPK_KP_8:
			return CEGUI::Key::Numpad8;
			break;
		case ApplicationKeycode::APPK_KP_9:
			return CEGUI::Key::Numpad9;
			break;
		case ApplicationKeycode::APPK_KP_PERIOD:
			return CEGUI::Key::Decimal;
			break;
		case ApplicationKeycode::APPK_KP_PLUS:
			return CEGUI::Key::Add;
			break;
		case ApplicationKeycode::APPK_KP_MINUS:
			return CEGUI::Key::Subtract;
			break;
		case ApplicationKeycode::APPK_KP_MULTIPLY:
			return CEGUI::Key::Multiply;
			break;
		case ApplicationKeycode::APPK_KP_DIVIDE:
			return CEGUI::Key::Divide;
			break;
		case ApplicationKeycode::APPK_KP_ENTER:
			return CEGUI::Key::NumpadEnter;
			break;

		case ApplicationKeycode::APPK_UP:
			return CEGUI::Key::ArrowUp;
			break;
		case ApplicationKeycode::APPK_LEFT:
			return CEGUI::Key::ArrowLeft;
			break;
		case ApplicationKeycode::APPK_RIGHT:
			return CEGUI::Key::ArrowRight;
			break;
		case ApplicationKeycode::APPK_DOWN:
			return CEGUI::Key::ArrowDown;
			break;

		case ApplicationKeycode::APPK_HOME:
			return CEGUI::Key::Home;
			break;
		case ApplicationKeycode::APPK_END:
			return CEGUI::Key::End;
			break;
		case ApplicationKeycode::APPK_PAGEUP:
			return CEGUI::Key::PageUp;
			break;
		case ApplicationKeycode::APPK_PAGEDOWN:
			return CEGUI::Key::PageDown;
			break;
		case ApplicationKeycode::APPK_INSERT:
			return CEGUI::Key::Insert;
			break;
		case ApplicationKeycode::APPK_DELETE:
			return CEGUI::Key::Delete;
			break;
		}
		return CEGUI::Key::Unlabeled;
	}
};

#endif /* CONTROLLER_INPUT_INPUTUTILS_HPP_ */
