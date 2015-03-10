/*
 * ControlConfiguration.h
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

#ifndef CONTROLCONFIGURATION_H_
#define CONTROLCONFIGURATION_H_

class ControlConfiguration {
public:
	// for the sine CPG
	static const double CPG_SINE_INITIAL_MAX_AMPLITUDE = 10;
	static const double CPG_SINE_INITIAL_MAX_FREQUENCY = 1; // Hz
};

#endif /* CONTROLCONFIGURATION_H_ */
