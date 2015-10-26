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

	static const double REALITY_BULLET_GRAVITY_SCALING_FACTOR = 50;

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
//#define FIXED_STEPS_PER_SEC 60.0f // Too low
//#define FIXED_STEPS_PER_SEC 120.0f // Might be too low
//#define FIXED_STEPS_PER_SEC 200.0f // Might be ok
#define FIXED_STEPS_PER_SEC 240.0f // Might be better
//#define FIXED_STEPS_PER_SEC 1000.0f // Best results
	static const double SIMULATOR_PHYSICS_FIXED_STEPS_PER_SEC = FIXED_STEPS_PER_SEC;
	static const double FIXED_STEP_SIZE_SEC = 1.0f/FIXED_STEPS_PER_SEC;
	static const double FIXED_STEP_SIZE_MILLI = 1.0f/FIXED_STEPS_PER_SEC
		* 1000.0f;

	/**
	 * Joint error and the Error Reduction Parameter (ERP)
	 * The ERP specifies what proportion of the joint error will be fixed during the next simulation step.
	 * @link http://ode-wiki.org/wiki/index.php?title=Manual:_All&printable=yes#How_To_Use_ERP_and_CFM
	 */
	static const double SIMULATOR_PHYSICS_FS_ERP = 0.15f;
	static const double SIMULATOR_PHYSICS_SRB_ERP = 0; // [0.1;0.8] ODE default 0.2

	/**
	 * A nonzero (positive) value of CFM allows the original constraint equation to be violated by an amount proportional
	 * to CFM times the restoring force \lambda that is needed to enforce the constraint.
	 * @link http://ode-wiki.org/wiki/index.php?title=Manual:_All&printable=yes#How_To_Use_ERP_and_CFM
	 */
	static const double SIMULATOR_PHYSICS_FS_CFM = 0.1f;
	static const double SIMULATOR_PHYSICS_SRB_CFM = 0;

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

	static const double PENETRATION_THRESHOLD = -40; //-15

	static const double FORCE_THRESHOLD = 1e6;
	static const double TORQUE_THRESHOLD = 1e6;

	static const double DISCARDING_STARTS = 1.0f;

	static const double BULLET_PICKER_FORCE = 100000;

	static const double WEIGHT_SCALE_SHRINK_LOGBASE = 2.0f;
};

#endif /* CONFIGURATION_PHYSICSCONFIGURATION_H_ */
