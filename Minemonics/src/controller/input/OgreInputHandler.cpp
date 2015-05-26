//## model headers
//## view headers
//## utils headers

//# corresponding header
#include <string>

//## controller headers
//## model headers
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/parameter/keyword.hpp>

//## view headers
#include <boost/lexical_cast.hpp>
#include <configuration/CameraConfiguration.hpp>
#include <controller/camera/CameraHandler.hpp>
#include <controller/input/OgreInputHandler.hpp>
#include <controller/physics/PhysicsController.hpp>
#include <controller/StateHandler.hpp>
#include <OgreLogManager.h>
#include <OgreRenderWindow.h>
#include <SimulationManager.hpp>

//# custom headers
//## base headers
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>

//## utils headers

BoostLogger OgreInputHandler::mBoostLogger;  // initialize the static variables
OgreInputHandler::_Init OgreInputHandler::_initializer;
OgreInputHandler::OgreInputHandler() :
		mSimulationMgr(NULL), mRightMousePressed(false) {

}

OgreInputHandler::~OgreInputHandler() {

}

void OgreInputHandler::initialize(SimulationManager* simulationMgr) {
	mSimulationMgr = simulationMgr;
}

//-------------------------------------------------------------------------------------
bool OgreInputHandler::keyPressed(ApplicationKeycode::Keycode key) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "RawKey pressed::" << key;

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
		moveCameraUp();
		break;
	case ApplicationKeycode::APPK_w:
		moveCameraForward();
		break;
	case ApplicationKeycode::APPK_e:
		moveCameraDown();
		break;
	case ApplicationKeycode::APPK_r:
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
		mSimulationMgr->getPhysicsController().setPhysicsPaused(
				!mSimulationMgr->getPhysicsController().isPhysicsPaused());
		break;
	case ApplicationKeycode::APPK_a:
		moveCameraLeft();
		break;
	case ApplicationKeycode::APPK_s:
		moveCameraBackward();
		break;
	case ApplicationKeycode::APPK_d:
		moveCameraRight();
		break;
	case ApplicationKeycode::APPK_f:
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
		mSimulationMgr->getDebugDrawer()->setDebugDrawingEnabled(
				!mSimulationMgr->getDebugDrawer()->isDebugDrawingEnabled());
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Draw Bullet Debug output::" << (mSimulationMgr->getDebugDrawer()->isDebugDrawingEnabled())?"true":"false";
		break;
		case ApplicationKeycode::APPK_BACKSLASH:
		mSimulationMgr->getDebugDrawer()->setDrawTrajectory(!mSimulationMgr->getDebugDrawer()->isDrawTrajectory());
		break;
		case ApplicationKeycode::APPK_MINUS:
		if(mSimulationMgr->getVideoWriter().isInitialized())
		{
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Recording video stopped.";
			mSimulationMgr->getVideoWriter().close();
		}
		else
		{
			std::string videoName;
			videoName.append("Minemonics-");
			videoName.append(boost::posix_time::to_iso_string(mSimulationMgr->getNow()));
			videoName.append(".mp4");
			BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Recording video started.";
			//TODO What to do if screen gets resized?
			mSimulationMgr->getVideoWriter().setup(mSimulationMgr,videoName.c_str(),mSimulationMgr->getWindow()->getWidth(),mSimulationMgr->getWindow()->getHeight());
		}
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
		// take a screenshot
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Smile! Screenshot taken!";
		mSimulationMgr->getWindow()->writeContentsToTimestampedFile("Minemonics-", ".jpg");
		break;
		case ApplicationKeycode::APPK_POWER:
		// return CEGUI::Key::Power;
		break;
		//case ApplicationKeycode::APPK_NUMLOCK: return CEGUI::Key::NumLock;
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
		// return CEGUI::Key::LeftControl;
		break;
		case ApplicationKeycode::APPK_LALT:
		// return CEGUI::Key::LeftAlt;
		break;
		case ApplicationKeycode::APPK_LSHIFT:
		mSimulationMgr->getCameraHandler().setMove(CameraConfiguration::CAMERA_MOVEMENT_SPEED * CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
		break;
		//case ApplicationKeycode::APPK_LSUPER: // return CEGUI::Key::LeftWindows;
		break;
		case ApplicationKeycode::APPK_RCTRL:
		// return CEGUI::Key::RightControl;
		break;
		case ApplicationKeycode::APPK_RALT:
		//take screen shot
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Smile! Screenshot taken!";
		mSimulationMgr->getWindow()->writeContentsToTimestampedFile("Minemonics-", ".jpg");
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
		moveCameraForward();
		break;
		case ApplicationKeycode::APPK_LEFT:
		moveCameraLeft();
		break;
		case ApplicationKeycode::APPK_RIGHT:
		moveCameraRight();
		break;
		case ApplicationKeycode::APPK_DOWN:
		moveCameraBackward();
		break;

		case ApplicationKeycode::APPK_HOME:
		// return CEGUI::Key::Home;
		break;
		case ApplicationKeycode::APPK_END:
		// return CEGUI::Key::End;
		break;
		case ApplicationKeycode::APPK_PAGEUP:
		moveCameraUp();
		break;
		case ApplicationKeycode::APPK_PAGEDOWN:
		moveCameraDown();
		break;
		case ApplicationKeycode::APPK_INSERT:
		// return CEGUI::Key::Insert;
		break;
		case ApplicationKeycode::APPK_DELETE:
		// return CEGUI::Key::Delete;
		break;
	}

	return true;
}

//-------------------------------------------------------------------------------------
bool OgreInputHandler::keyReleased(ApplicationKeycode::Keycode key) {

	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "RawKey released::" << key;
	Ogre::String newVal;

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
		stopCameraYDimensionMovement();
		break;
	case ApplicationKeycode::APPK_w:
		stopCameraZDimensionMovement();
		break;
	case ApplicationKeycode::APPK_e:
		stopCameraYDimensionMovement();
		break;
	case ApplicationKeycode::APPK_r:
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
		stopCameraXDimensionMovement();
		break;
	case ApplicationKeycode::APPK_s:
		stopCameraZDimensionMovement();
		break;
	case ApplicationKeycode::APPK_d:
		stopCameraXDimensionMovement();
		break;
	case ApplicationKeycode::APPK_f:
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
		mSimulationMgr->quit();
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
		// return CEGUI::Key::LeftControl;
		break;
	case ApplicationKeycode::APPK_LALT:
		// return CEGUI::Key::LeftAlt;
		break;
	case ApplicationKeycode::APPK_LSHIFT:
		mSimulationMgr->getCameraHandler().setMove(
				CameraConfiguration::CAMERA_MOVEMENT_SPEED);
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
		stopCameraZDimensionMovement();
		break;
	case ApplicationKeycode::APPK_LEFT:
		stopCameraXDimensionMovement();
		break;
	case ApplicationKeycode::APPK_RIGHT:
		stopCameraXDimensionMovement();
		break;
	case ApplicationKeycode::APPK_DOWN:
		stopCameraZDimensionMovement();
		break;

	case ApplicationKeycode::APPK_HOME:
		// return CEGUI::Key::Home;
		break;
	case ApplicationKeycode::APPK_END:
		// return CEGUI::Key::End;
		break;
	case ApplicationKeycode::APPK_PAGEUP:
		stopCameraYDimensionMovement();
		break;
	case ApplicationKeycode::APPK_PAGEDOWN:
		stopCameraYDimensionMovement();
		break;
	case ApplicationKeycode::APPK_INSERT:
		// return CEGUI::Key::Insert;
		break;
	case ApplicationKeycode::APPK_DELETE:
		// return CEGUI::Key::Delete;
		break;
	}
	return true;
}

// CEGUI::MouseListener
bool OgreInputHandler::mouseMoved(float x, float y) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse moved by " << x << "," << y;
	if (mRightMousePressed) {
		mSimulationMgr->getCameraHandler().rotate(y, x, 0);
	}

	return true;
}

// CEGUI:MouseWheelListener
bool OgreInputHandler::mouseWheelMoved(float rel) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse wheel moved by " << rel;
	return true;
}

bool OgreInputHandler::mousePressed(ApplicationMouseCode::MouseButton button) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse button " << button << " pressed";

	switch (button) {
	case ApplicationMouseCode::LeftButton: {
		//Ogre::LogManager::getSingleton().logMessage("Mouse left-click");
		break;
	}
	case ApplicationMouseCode::RightButton: {
		//Ogre::LogManager::getSingleton().logMessage("Mouse right-click");
		mRightMousePressed = true;
		break;
	}
	default:
		break;
	}
	return true;
}

bool OgreInputHandler::mouseReleased(ApplicationMouseCode::MouseButton button) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse button " << button << " released";

	switch (button) {
	case ApplicationMouseCode::LeftButton: {
		//Ogre::LogManager::getSingleton().logMessage("Mouse left-release");
		break;
	}
	case ApplicationMouseCode::RightButton: {
		//Ogre::LogManager::getSingleton().logMessage("Mouse right-release");
		mRightMousePressed = false;
		break;
	}
	default:
		break;
	}
	return true;
}

void OgreInputHandler::stopCameraXDimensionMovement() {
	mSimulationMgr->getCameraHandler().moveX(0);
}

void OgreInputHandler::stopCameraYDimensionMovement() {
	mSimulationMgr->getCameraHandler().moveY(0);
}

void OgreInputHandler::stopCameraZDimensionMovement() {
	mSimulationMgr->getCameraHandler().moveZ(0);
}

void OgreInputHandler::moveCameraLeft() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move left!";
	mSimulationMgr->getCameraHandler().moveX(-1);
}

void OgreInputHandler::moveCameraUp() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move up!";
	mSimulationMgr->getCameraHandler().moveY(1);
}

void OgreInputHandler::moveCameraBackward() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move backward!";
	mSimulationMgr->getCameraHandler().moveZ(1);
}

void OgreInputHandler::moveCameraRight() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move right!";
	mSimulationMgr->getCameraHandler().moveX(1);
}

void OgreInputHandler::moveCameraDown() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move down!";
	mSimulationMgr->getCameraHandler().moveY(-1);
}

void OgreInputHandler::moveCameraForward() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move forward!";
	mSimulationMgr->getCameraHandler().moveZ(-1);
}

void OgreInputHandler::quitApplication() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Shutdown application!";
	mSimulationMgr->getStateHandler().requestStateChange(SHUTDOWN);
}
