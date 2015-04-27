#ifndef PHYSICSCONFIGURATION_H_
#define PHYSICSCONFIGURATION_H_

//# corresponding header
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

#define CONST_EARTH_GRAVITY 9.81

/**
 * @brief		The configuration of the physics environment used in the simulator.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class PhysicsConfiguration {
public:

	static const double REALITY_BULLET_GRAVITY_SCALING_FACTOR = 102;

	/**
	 * No gravity
	 */
	static const double NO_GRAVITY = 0;

	/**
	 * Pluto gravity 0.059
	 */
	static const double PLUTO_GRAVITY = 0.059 * CONST_EARTH_GRAVITY;

	/**
	 * Moon gravity 0.166
	 */
	static const double MOON_GRAVITY = 0.166 * CONST_EARTH_GRAVITY;

	/**
	 * Mars/Mercury gravity 0.377/0.378
	 */
	static const double MARS_GRAVITY = 0.377 * CONST_EARTH_GRAVITY;

	/**
	 * Uranus gravity 0.889
	 */
	static const double URANUS_GRAVITY = 0.889 * CONST_EARTH_GRAVITY;

	/**
	 * Venus/Saturn gravity 0.907/0.916
	 */
	static const double VENUS_GRAVITY = 0.907 * CONST_EARTH_GRAVITY;

	/**
	 * Earth gravity 1
	 */
	static const double EARTH_GRAVITY = CONST_EARTH_GRAVITY;

	/**
	 * Neptune gravity 1.12
	 */
	static const double NEPTUNE_GRAVITY = 1.12 * CONST_EARTH_GRAVITY;

	/**
	 * Jupiter gravity 2.36
	 */
	static const double JUPITER_GRAVITY = 2.36 * CONST_EARTH_GRAVITY;

	/**
	 * Sun gravity 27.930682977
	 */
	static const double SUN_GRAVITY = 27.030682877 * CONST_EARTH_GRAVITY;

	/**
	 * Step size of the bullet physics simulator (solverAccuracy). Accuracy versus speed.
	 */
	static const double SIMULATOR_STEP_SIZE = 0.001;

	/**
	 * Are the body boxes allowed to interpenetrate each other?
	 */
	static const bool BODY_SEGMENT_INTERPENETRATION_FLAG = false;

	/**
	 * A box of unit size in ogre has the size of 96.9 in bullet
	 */
	static const double BULLET_OGRE_BOX_SCALING_FACTOR = 0.013;

	/**
	 * Bullet box to capsule scaling factor
	 */
	static const double BULLET_CAPSULE_BOX_SCALING_FACTOR = 0.015;
};

#endif /* PHYSICSCONFIGURATION_H_ */
