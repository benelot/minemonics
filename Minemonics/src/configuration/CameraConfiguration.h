/*
 * CameraConfiguration.h
 *
 *  Created on: Feb 13, 2015
 *      Author: leviathan
 */

#ifndef CAMERACONFIGURATION_H_
#define CAMERACONFIGURATION_H_

class CameraConfiguration {
public:
	/**
	 * The movment speed of the camera of the simulator.
	 */
	static const double CAMERA_MOVEMENT_SPEED = 500;

	/**
	 * The movement speed increase of the camera if you press the shift button.
	 */
	static const double CAMERA_SHIFT_MOVEMENT_SPEED_FACTOR = 8;

	/**
	 * The rotation speed of the camera of the simulator.
	 */
	static const double CAMERA_ROTATION_SPEED = 0.13;

};

#endif /* CAMERACONFIGURATION_H_ */
