#ifndef CONTROLCONFIGURATION_H_
#define CONTROLCONFIGURATION_H_

//# corresponding headers
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

/**
 * @brief		The configuration for the controllers of the creatures.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class ControlConfiguration {
public:
	/**
	 * The initial maximum amplitude of the sine wave controller
	 */
	static const double CPG_SINE_INITIAL_MAX_AMPLITUDE = 1;

	/**
	 * The initial maximum frequency of the sine wave controller
	 */
	static const double CPG_SINE_INITIAL_MAX_FREQUENCY = 1; // Hz
};

#endif /* CONTROLCONFIGURATION_H_ */
