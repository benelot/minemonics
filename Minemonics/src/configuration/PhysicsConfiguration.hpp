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

#define CONST_EARTH_GRAVITY 9.81f

/**
 * @brief		The configuration of the physics environment used in the simulator.
 * @details		Details
 * @date		2014-11-17
 * @author		Benjamin Ellenberger
 */
class PhysicsConfiguration {
public:

	static const double NO_GRAVITY; /**!< No gravity */

	static const double PLUTO_GRAVITY; /**!< Pluto gravity 0.059 */

	static const double MOON_GRAVITY; /**!< Moon gravity 0.166 */

	static const double MARS_GRAVITY; /**!< Mars/Mercury gravity 0.377/0.378 */

	static const double URANUS_GRAVITY; /**!< Uranus gravity 0.889 */

	static const double VENUS_GRAVITY; /**!< Venus/Saturn gravity 0.907/0.916 */

	static const double EARTH_GRAVITY; /**!< Earth gravity 1 */

	static const double NEPTUNE_GRAVITY;/**!< Neptune gravity 1.12 */

	static const double JUPITER_GRAVITY; /**!< Jupiter gravity 2.36 */

	static const double SUN_GRAVITY; /**!< Sun gravity 27.930682977 */

	/**
	 * Step size of the bullet physics simulator (solverAccuracy). Accuracy versus speed.
	 */
	static const double SIMULATOR_PHYSICS_FIXED_STEPS_PER_SEC;
	static const double FIXED_STEP_SIZE_SEC;
	static const double FIXED_STEP_SIZE_MILLI;

	static const double BULLET_OGRE_BOX_SCALING_FACTOR; /**!< A box of unit size in ogre has the size of 100 in bullet */

	static const double BULLET_DEACTIVATION_TIME; /**!< The deactivation time of a bullet object */
	static const double BULLET_LINEAR_SLEEPING_TIME; /**!< The time to sleep with linear movement */
	static const double BULLET_ANGULAR_SLEEPING_TIME; /**!< The time to sleep with angular movement */

	/**The speed is calculated as 2^SIMULATION_SPEED constant */
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

	static const double SIMULATION_SPEEDS[];

#define BIT(x) (1<<(x))
	enum collisiontypes {
		COL_NOTHING = 0, //<Collide with nothing
		COL_CREATURE = BIT(0), //<Collide with ships
		COL_GROUND = BIT(1), //<Collide with walls
		COL_CREATURE_TESTRAY = BIT(2), //<Collide with creature test ray
		COL_GROUND_TESTRAY = BIT(3) //< Collide with ground test ray
	};

	static const int CREATURE_COLLIDES_WITH; /**!< Objects a creature collides with */
	static const int GROUND_COLLIDES_WITH; /**!< Objects the ground collides with */
	static const int CREATURE_TESTRAY_COLLIDES_WITH; /**!< Objects a creature test ray collides with */
	static const int GROUND_TESTRAY_COLLIDES_WITH; /**!< Objects a ground test ray collides with */

	/** Attempts to detect interpenetrating shapes */
	static const double PENETRATION_THRESHOLD; //-15
	static const double FORCE_THRESHOLD;
	static const double TORQUE_THRESHOLD;
	static const double DISCARDING_STARTS;

	static const double BULLET_PICKER_FORCE;

	enum SolverType{NNCGSOLVER,DANZIGSOLVER,GAUSSSEIDELSOLVER,SEQUENTIALIMPULSESOLVER,LEMKESOLVER};
	static const SolverType SOLVER_TYPE;
};

#endif /* CONFIGURATION_PHYSICSCONFIGURATION_H_ */
