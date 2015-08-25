#ifndef CONFIGURATION_PHYSICSCONFIGURATION_H_
#define CONFIGURATION_PHYSICSCONFIGURATION_H_

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

#define CONST_EARTH_GRAVITY 9.81

/**
 * @brief		The configuration of the physics environment used in the simulator.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class PhysicsConfiguration {
public:

	static const double REALITY_BULLET_GRAVITY_SCALING_FACTOR = 30;

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
	static const double SIMULATOR_PHYSICS_FIXED_STEP_SIZE_SEC = 0.001f;
	static const double SIMULATOR_PHYSICS_FIXED_STEP_SIZE_MILLI = 0.001f
			* 1000.0f;

	static const int SIMULATOR_SECURITY_MARGIN = 2;

	/**
	 * Are the body boxes allowed to interpenetrate each other?
	 */
	static const bool BODY_SEGMENT_INTERPENETRATION_FLAG = false;

	/**
	 * A box of unit size in ogre has the size of 96.9 in bullet
	 */
	static const double BULLET_OGRE_BOX_SCALING_FACTOR = 0.01;

	static const double BULLET_DEACTIVATION_TIME = 5;

	static const double BULLET_LINEAR_SLEEPING_TIME = 1.6;
	static const double BULLET_ANGULAR_SLEEPING_TIME = 5;

	/**
	 * Bullet box to capsule scaling factor
	 * static const double BULLET_OGRE_CAPSULE_SCALING_FACTOR = 0.5;
	 * static const double BULLET_OGRE_CAPSULE_HEIGHT_SCALING_FACTOR = 1;
	 */

	// the speed will be 2^SPEED
	enum SIMULATION_SPEED {
		SIMULATION_SPEED_01,
		SIMULATION_SPEED_02,
		SIMULATION_SPEED_03,
		SIMULATION_SPEED_04,
		SIMULATION_SPEED_05,
		SIMULATION_SPEED_06,
		SIMULATION_SPEED_07,
		SIMULATION_SPEED_08,
		//9 and 10 run as fast as they can
		SIMULATION_SPEED_09, // with graphics
		SIMULATION_SPEED_10 //headless
	};

	static const int SIMULATION_SPEEDS[];

#define BIT(x) (1<<(x))
	enum collisiontypes {
		COL_NOTHING = 0, //<Collide with nothing
		COL_CREATURE = BIT(0), //<Collide with ships
		COL_GROUND = BIT(1), //<Collide with walls
		COL_CREATURE_TESTRAY = BIT(2), //<Collide with creature test ray
		COL_GROUND_TESTRAY = BIT(3) //< Collide with ground test ray
	};

	static const int CREATURE_COLLIDES_WITH = COL_GROUND | COL_CREATURE_TESTRAY;
	static const int GROUND_COLLIDES_WITH = COL_CREATURE | COL_GROUND_TESTRAY;
	static const int CREATURE_TESTRAY_COLLIDES_WITH = COL_CREATURE;
	static const int GROUND_TESTRAY_COLLIDES_WITH = COL_GROUND;

	static const double PENETRATION_THRESHOLD = -10;//-7

	static const double FORCE_THRESHOLD = 1e6;
	static const double TORQUE_THRESHOLD = 1e6;

	static const double DISCARDING_STARTS = 1.0f;

	static const bool SELF_COLLISION = true;
};

#endif /* CONFIGURATION_PHYSICSCONFIGURATION_H_ */
