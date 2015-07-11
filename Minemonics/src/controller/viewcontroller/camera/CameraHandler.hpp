#ifndef CONTROLLER_VIEWCONTROLLER_CAMERAHANDLER_H_
#define CONTROLLER_VIEWCONTROLLER_CAMERAHANDLER_H_

//# corresponding header
//# forward declarations
class SimulationManager;

//# system headers
//## controller headers
//## model headers
#include <boost/log/attributes/constant.hpp>
#include <boost/log/sources/basic_logger.hpp>

//## view headers
#include <OgreRoot.h>
#include <OgrePrerequisites.h>
#include <OgreVector3.h>

//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers
#include <utils/logging/Logger.hpp>

/**
 * @brief		The handler of the Ogre3D camera. Helps to position it in the graphics space
 *  so that creatures are depicted appropriately.
 * @details		Details
 * @date		2015-02-13
 * @author		Benjamin Ellenberger
 */
class CameraHandler {
public:
	CameraHandler(SimulationManager* simulationMgr);
	virtual ~CameraHandler();

	void reposition(float timeSinceLastFrame);
	void rotate(int pitch, int yaw, int roll);
	void move(double x, double y, double z);
	void moveX(double x);
	void moveY(double y);
	void moveZ(double z);

	//Accessor methods
	const Ogre::SceneNode* getCamNode() const;
	void setCamNode(Ogre::SceneNode* camNode);

	Ogre::Real getMove() const {
		return mMove;
	}

	void setMove(Ogre::Real move) {
		mMove = move;
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
							"CameraHandler"));
		}
	} _initializer;

	SimulationManager* mSimulationMgr;

	/**
	 * The rotation constant
	 */
	Ogre::Real mRotate;

	/**
	 * The movement constant
	 */
	Ogre::Real mMove;

	/**
	 * The SceneNode the camera is currently attached to
	 */
	Ogre::SceneNode *mCamNode;

	/**
	 *  Value to move in the correct direction
	 */
	Ogre::Vector3 mDirection;
};

#endif /* CONTROLLER_VIEWCONTROLLER_CAMERAHANDLER_H_ */
