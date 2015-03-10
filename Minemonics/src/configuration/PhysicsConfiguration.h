/*
 * PhysicsConfiguration.h
 *
 *  Created on: Nov 17, 2014
 *      Author: leviathan
 */

#ifndef PHYSICSCONFIGURATION_H_
#define PHYSICSCONFIGURATION_H_

class PhysicsConfiguration {
public:
	static const double WORLD_GRAVITY = 100;
	static const double SIMULATOR_STEP_SIZE = 0.001;
	// solverAccuracy

	static const bool BODY_SEGMENT_INTERPENETRATION_FLAG = false;
};

#endif /* PHYSICSCONFIGURATION_H_ */
