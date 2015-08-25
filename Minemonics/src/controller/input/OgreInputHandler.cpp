//# corresponding headers
#include <controller/input/OgreInputHandler.hpp>

//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <boost/log/core/record.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/formatting_ostream.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/time_formatters.hpp>
#include <boost/lexical_cast.hpp>

//## view headers
#include <OgreRenderWindow.h>
#include <OgreLogManager.h>
#include <OgreCamera.h>
#include <OgreCommon.h>
#include <OgreMaterialManager.h>
#include <OgrePrerequisites.h>

//# custom headers
//## base headers
#include <SimulationManager.hpp>

//## configuration headers
#include <configuration/CameraConfiguration.hpp>

//## controller headers
#include <controller/StateHandler.hpp>
#include <controller/universe/Universe.hpp>
#include <controller/viewcontroller/camera/CameraHandler.hpp>
#include <controller/viewcontroller/ViewController.hpp>

//## model headers
#include <model/universe/environments/physics/PhysicsController.hpp>

//## view headers
#include <view/videocapture/Ogre3DFFMPEGVideoWriter.hpp>
#include <view/visualization/bulletphysics/OgreBtDebugDrawer.hpp>
#include <view/visualization/panels/MathGLPanel.hpp>
#include <view/visualization/panels/ParamsPanel.hpp>

//## utils headers

BoostLogger OgreInputHandler::mBoostLogger; /*<! initialize the boost logger*/
OgreInputHandler::_Init OgreInputHandler::_initializer;
OgreInputHandler::OgreInputHandler() {

}

OgreInputHandler::~OgreInputHandler() {
//	mBoostLogger
}

void OgreInputHandler::initialize() {
}

//-------------------------------------------------------------------------------------
bool OgreInputHandler::keyPressed(const ApplicationKeycode::Keycode key) {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)<< "RawKey pressed::" << key;

	switch (key) {
		case ApplicationKeycode::APPK_1: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_01);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_01]);
		}
		break;
		case ApplicationKeycode::APPK_2: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_02);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_02]);
		}
		break;
		case ApplicationKeycode::APPK_3: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_03);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_03]);
		}
		break;
		case ApplicationKeycode::APPK_4: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_04);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_04]);
		}
		break;
		case ApplicationKeycode::APPK_5: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_05);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_05]);
		}
		break;
		case ApplicationKeycode::APPK_6: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_06);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_06]);
		}
		break;
		case ApplicationKeycode::APPK_7: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_07);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_07]);
		}
		break;
		case ApplicationKeycode::APPK_8: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_08);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to " << pow(2,PhysicsConfiguration::SIMULATION_SPEEDS[PhysicsConfiguration::SIMULATION_SPEED_08]);
		}
		break;
		case ApplicationKeycode::APPK_9: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_09);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to as fast as possible";
		}
		break;
		case ApplicationKeycode::APPK_0: {
			SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::HEADLESS_SIMULATION);
			SimulationManager::getSingleton()->setSimulationSpeed(PhysicsConfiguration::SIMULATION_SPEED_10);
			BOOST_LOG_SEV(
					mBoostLogger, boost::log::trivial::info)
			<< "Changed simulation speed to as fast as possible";
		}
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
		case ApplicationKeycode::APPK_r: {
			// cycle polygon rendering mode
			Ogre::String newVal;
			Ogre::PolygonMode pm;

			switch (SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera()->getPolygonMode()) {
				case Ogre::PM_SOLID:
				newVal = "Wireframe";
				pm = Ogre::PM_WIREFRAME;
				break;
				case Ogre::PM_WIREFRAME:
				newVal = "Points";
				pm = Ogre::PM_POINTS;
				break;
				default:
				newVal = "Solid";
				pm = Ogre::PM_SOLID;
			}

			SimulationManager::getSingleton()->getViewController().getCameraHandler().getCamera()->setPolygonMode(pm);
			SimulationManager::getSingleton()->getViewController().getDetailsPanel()->setParamValue(10,
					newVal);
			break;
		}
		case ApplicationKeycode::APPK_t: // cycle polygon rendering mode
		{
			Ogre::String newVal;
			Ogre::TextureFilterOptions tfo;
			unsigned int aniso;

			switch (SimulationManager::getSingleton()->getViewController().getDetailsPanel()->getParamValue(
							9)[0]) {
				case 'B':
				newVal = "Trilinear";
				tfo = Ogre::TFO_TRILINEAR;
				aniso = 1;
				break;
				case 'T':
				newVal = "Anisotropic";
				tfo = Ogre::TFO_ANISOTROPIC;
				aniso = 8;
				break;
				case 'A':
				newVal = "None";
				tfo = Ogre::TFO_NONE;
				aniso = 1;
				break;
				default:
				newVal = "Bilinear";
				tfo = Ogre::TFO_BILINEAR;
				aniso = 1;
			}

			Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
			Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
			SimulationManager::getSingleton()->getViewController().getDetailsPanel()->setParamValue(9,
					newVal);
			break;
		}
		case ApplicationKeycode::APPK_y:
		SimulationManager::getSingleton()->getViewController().setShowShadows(!SimulationManager::getSingleton()->getViewController().doesShowShadows());
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
		switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
			case StateHandler::SIMULATION: {
				SimulationManager::getSingleton()->getUniverse().getEvaluationController().setPaused(
						!SimulationManager::getSingleton()->getUniverse().getEvaluationController().isPaused());
				break;
			}
			default: {
				break;
			}
		}
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
		case ApplicationKeycode::APPK_f: // toggle visibility of advanced frame stats
		if (!SimulationManager::getSingleton()->getViewController().getFpsPanel()->getWidgetPanel()->isVisible()) {
			ParamsPanel::VectorStringPairs items;
			items.push_back(ParamsPanel::PairString("Last FPS", "0"));		// 0
			SimulationManager::getSingleton()->getViewController().getFpsPanel()->getWidgetPanel()->setVisible(
					false);
		} else {
			bool simple =
			SimulationManager::getSingleton()->getViewController().getFpsPanel()->size()
			== 1;
			SimulationManager::getSingleton()->getViewController().getFpsPanel()->getWidgetPanel()->setVisible(
					true);
		}
		break;
		case ApplicationKeycode::APPK_g: // toggle visibility of even rarer debugging details

		if (SimulationManager::getSingleton()->getViewController().getDetailsPanel()->isVisible()) {
			SimulationManager::getSingleton()->getViewController().getDetailsPanel()->hide();
		} else {
			SimulationManager::getSingleton()->getViewController().getDetailsPanel()->show();
		}
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
		switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
			case StateHandler::SIMULATION: {
				SimulationManager::getSingleton()->getDebugDrawer().setDebugDrawingEnabled(
						!SimulationManager::getSingleton()->getDebugDrawer().isDebugDrawingEnabled());
				BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)
				<< "Draw Bullet Debug output::" << (SimulationManager::getSingleton()->getDebugDrawer().isDebugDrawingEnabled())?"true":"false";
				break;
			}
			default: {
				break;
			}
			break;
		}
		break;
		case ApplicationKeycode::APPK_BACKSLASH:
		switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
			case StateHandler::SIMULATION: {
				SimulationManager::getSingleton()->getDebugDrawer().setDrawTrajectory(
						!SimulationManager::getSingleton()->getDebugDrawer().isDrawTrajectory());
				break;
			}
			default: {
				break;
			}
		}
		break;
		case ApplicationKeycode::APPK_MINUS:
		switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
			case StateHandler::SIMULATION: {
				if (SimulationManager::getSingleton()->getVideoWriter().isInitialized()) {
					BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Recording video stopped.";
					SimulationManager::getSingleton()->getVideoWriter().close();
				}
				else
				{
					// create video file name
					std::string videoName;
					videoName.append("Minemonics-");
					videoName.append(boost::lexical_cast<std::string>(SimulationManager::getSingleton()->getNow()));
					videoName.append(".mp4");

					BOOST_LOG_SEV(
							mBoostLogger, boost::log::trivial::info)
					<< "Recording video started.";

					//This even works on if the screen gets resized
					SimulationManager::getSingleton()->getVideoWriter().setup(videoName.c_str(),SimulationManager::getSingleton()->getWindow()->getWidth(),SimulationManager::getSingleton()->getWindow()->getHeight());
				}
				break;
			}
			default: {
				break;
			}
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
		switch (SimulationManager::getSingleton()->getStateHandler().getCurrentState()) {
			case StateHandler::SIMULATION: {
				if(SimulationManager::getSingleton()->getViewController().getEvaluationInView() != NULL) {
					SimulationManager::getSingleton()->getViewController().getEvaluationInView()->teardown();
				}
				SimulationManager::getSingleton()->getUniverse().proceedEvaluation();
				break;
			}
			default: {
				break;
			}
		}
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
		SimulationManager::getSingleton()->getWindow()->writeContentsToTimestampedFile("Minemonics-", ".jpg");
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
		setLeftControlPressed(true);
		break;
		case ApplicationKeycode::APPK_LALT:
		setLeftAltPressed(true);
		break;
		case ApplicationKeycode::APPK_LSHIFT:
		setLeftShiftPressed(true);
		break;
//case ApplicationKeycode::APPK_LSUPER: // return CEGUI::Key::LeftWindows;
		break;
		case ApplicationKeycode::APPK_RCTRL:
		setRightControlPressed(true);
		break;
		case ApplicationKeycode::APPK_RALT:
		setRightAltPressed(true);
//take screen shot
		BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info) << "Smile! Screenshot taken!";
		SimulationManager::getSingleton()->getWindow()->writeContentsToTimestampedFile("Minemonics-", ".jpg");
		break;
		case ApplicationKeycode::APPK_RSHIFT:
		setRightShiftPressed(true);
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
bool OgreInputHandler::keyReleased(const ApplicationKeycode::Keycode key) {

	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::trace)<< "RawKey released::" << key;
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
		SimulationManager::getSingleton()->quit();
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
		setLeftControlPressed(false);
		break;
		case ApplicationKeycode::APPK_LALT:
		setLeftAltPressed(false);
		break;
		case ApplicationKeycode::APPK_LSHIFT:
		setLeftShiftPressed(false);
		break;
//case ApplicationKeycode::APPK_LSUPER:
// return CEGUI::Key::LeftWindows;
		break;
		case ApplicationKeycode::APPK_RCTRL:
		setRightControlPressed(false);
		break;
		case ApplicationKeycode::APPK_RALT:
		setRightAltPressed(false);
		break;
		case ApplicationKeycode::APPK_RSHIFT:
		setLeftShiftPressed(false);
		break;
//case ApplicationKeycode::APPK_RSUPER:
// return CEGUI::Key::RightWindows;
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
bool OgreInputHandler::mouseMoved(const float x, const float y) const {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse moved by " << x << "," << y;
	if (isRightMousePressed()) {
		if (isLeftShiftPressed() || isRightShiftPressed()) {
			SimulationManager::getSingleton()->getViewController().getCameraHandler().rotate(
					CameraConfiguration::CAMERA_SHIFT_ROTATION_SPEED_FACTOR * y,
					CameraConfiguration::CAMERA_SHIFT_ROTATION_SPEED_FACTOR * x,
					0);
		} else {
			SimulationManager::getSingleton()->getViewController().getCameraHandler().rotate(
					y, x, 0);
		}
	}

	return true;
}

// CEGUI:MouseWheelListener
bool OgreInputHandler::mouseWheelMoved(float rel) {
	//BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse wheel moved by " << rel;
	return true;
}

bool OgreInputHandler::mousePressed(ApplicationMouseCode::MouseButton button) {
//	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::debug)<< "Mouse button " << button << " pressed";

	switch (button) {
	case ApplicationMouseCode::LeftButton: {
//		Ogre::LogManager::getSingleton().logMessage("Mouse left-click");
		if (isLeftControlPressed()) {
			SimulationManager::getSingleton()->getMousePicker().pickBody();
		}
		mLeftMousePressed = true;
		break;
	}
	case ApplicationMouseCode::RightButton: {
		//Ogre::LogManager::getSingleton().logMessage("Mouse right-click");
		if (isLeftControlPressed()) {
			SimulationManager::getSingleton()->getMousePicker().setPicking(
					false);
		}
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
		mLeftMousePressed = false;
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
	SimulationManager::getSingleton()->getViewController().getCameraHandler().moveX(
			0);
}

void OgreInputHandler::stopCameraYDimensionMovement() {
	SimulationManager::getSingleton()->getViewController().getCameraHandler().moveY(
			0);
}

void OgreInputHandler::stopCameraZDimensionMovement() {
	SimulationManager::getSingleton()->getViewController().getCameraHandler().moveZ(
			0);
}

void OgreInputHandler::moveCameraLeft() const {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move left!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveX(-CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveX(-1);
	}
}

void OgreInputHandler::moveCameraUp() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move up!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveY(CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveY(1);
	}
}

void OgreInputHandler::moveCameraBackward() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move backward!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveZ(CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveZ(1);
	}
}

void OgreInputHandler::moveCameraRight() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move right!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveX(CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveX(1);
	}
}

void OgreInputHandler::moveCameraDown() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move down!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveY(-CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveY(-1);
	}
}

void OgreInputHandler::moveCameraForward() {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Camera move forward!";
	if(mLeftShiftPressed || mRightShiftPressed) {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveZ(-CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR);
	}
	else {
		SimulationManager::getSingleton()->getViewController().getCameraHandler().moveZ(-1);
	}
}

void OgreInputHandler::quitApplication() const {
	BOOST_LOG_SEV(mBoostLogger, boost::log::trivial::info)<< "Key::Shutdown application!";
	SimulationManager::getSingleton()->getStateHandler().requestStateChange(StateHandler::SHUTDOWN);
}

void OgreInputHandler::update(double timeSinceLastUpdate) {
	if (mLeftControlPressed) {
		if (mLeftMousePressed) {
			if (SimulationManager::getSingleton()->getMousePicker().isPicking()) {
				SimulationManager::getSingleton()->getMousePicker().moveBody();
			}
		}
	}
}
