//# corresponding headers
#include <configuration/CameraConfiguration.hpp>

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

const double CameraConfiguration::CAMERA_MOVEMENT_SPEED = 50; /** The movement speed of the camera of the simulator. */

const double CameraConfiguration::CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR = 16; /** The movement speed increase of the camera if you press the shift button. */

const double CameraConfiguration::CAMERA_SHIFT_ROTATION_SPEED_FACTOR = 1.5; /**!< The rotation speed increase of the camera if you press the shift button. */

const double CameraConfiguration::CAMERA_ROTATION_SPEED = 0.13; /**!< The rotation speed of the camera of the simulator. */

const Ogre::Vector3 CameraConfiguration::CAMERA_ROOT_DISPLACEMENT = Ogre::Vector3(0, 5, 15);

