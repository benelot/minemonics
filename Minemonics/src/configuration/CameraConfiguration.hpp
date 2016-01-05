#ifndef CONFIGURATION_CAMERACONFIGURATION_H_
#define CONFIGURATION_CAMERACONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
//## controller headers
//## model headers
#include <OgreVector3.h>

//## view headers
//# custom headers
//## base headers
//## configuration headers
//## controller headers
//## model headers
//## view headers
//## utils headers

/**
 * @brief		The configuration of the camera movement.
 * @details		The configuration of the camera movement.
 * @date		2015-02-13
 * @author		Benjamin Ellenberger
 */
class CameraConfiguration {
public:

	static const double CAMERA_MOVEMENT_SPEED; /** The movement speed of the camera of the simulator. */

	static const double CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR; /** The movement speed increase of the camera if you press the shift button. */

	static const double CAMERA_SHIFT_ROTATION_SPEED_FACTOR; /**!< The rotation speed increase of the camera if you press the shift button. */

	static const double CAMERA_ROTATION_SPEED; /**!< The rotation speed of the camera of the simulator. */

	static const Ogre::Vector3 CAMERA_ROOT_DISPLACEMENT; /**!< The position of the camera near the position where creatures are dropped */
};

#endif /* CONFIGURATION_CAMERACONFIGURATION_H_ */
