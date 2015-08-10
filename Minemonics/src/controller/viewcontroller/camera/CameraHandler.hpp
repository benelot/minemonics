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
	CameraHandler();
	virtual ~CameraHandler();

	void initialize();

	/**
	 * Reposition the camera.
	 * @param timeSinceLastFrame The time since the last frame.
	 */
	void reposition(const float timeSinceLastFrame);

	/**
	 * Rotate the camera.
	 * @param pitch Pitch rotation.
	 * @param yaw Yaw rotation.
	 * @param roll Roll rotation.
	 */
	void rotate(int pitch, int yaw, int roll);

	/**
	 * Move the camera.
	 * @param x X movement.
	 * @param y Y movement.
	 * @param z z movement.
	 */
	void move(double x, double y, double z);

	/**
	 * Move the camera in x direction.
	 * @param x X movement.
	 */
	void moveX(double x);

	/**
	 * Move the camera in y direction.
	 * @param y Y movement.
	 */
	void moveY(double y);

	/**
	 * Move the camera in z direction.
	 * @param z Z movement.
	 */
	void moveZ(double z);

	//Accessor methods
	Ogre::SceneNode* getCamNode() {
		return mCamNode;
	}

	const Ogre::SceneNode* getCamNode() const {
		return mCamNode;
	}

	void setCamNode(Ogre::SceneNode* camNode) {
		mCamNode = camNode;
	}

	Ogre::Camera* getCamera() const {
		return mCamera;
	}

	void setCamera(Ogre::Camera* camera) {
		mCamera = camera;
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

	/**
	 * The SceneNode the camera is currently attached to
	 */
	Ogre::SceneNode *mCamNode;

	Ogre::Camera* mCamera;

	/**
	 *  Value to move in the correct direction
	 */
	Ogre::Vector3 mDirection;
};

#endif /* CONTROLLER_VIEWCONTROLLER_CAMERAHANDLER_H_ */
