//# corresponding headers
#include <configuration/PhysicsConfiguration.hpp>

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

const double PhysicsConfiguration::NO_GRAVITY = 0; /**!< No gravity */

const double PhysicsConfiguration::PLUTO_GRAVITY = 0.059f * CONST_EARTH_GRAVITY; /**!< Pluto gravity 0.059 */

const double PhysicsConfiguration::MOON_GRAVITY = 0.166 * CONST_EARTH_GRAVITY; /**!< Moon gravity 0.166 */

const double PhysicsConfiguration::MARS_GRAVITY = 0.377f * CONST_EARTH_GRAVITY; /**!< Mars/Mercury gravity 0.377/0.378 */

const double PhysicsConfiguration::URANUS_GRAVITY = 0.889f * CONST_EARTH_GRAVITY; /**!< Uranus gravity 0.889 */

const double PhysicsConfiguration::VENUS_GRAVITY = 0.907f * CONST_EARTH_GRAVITY; /**!< Venus/Saturn gravity 0.907/0.916 */

const double PhysicsConfiguration::EARTH_GRAVITY = CONST_EARTH_GRAVITY; /**!< Earth gravity 1 */

const double PhysicsConfiguration::NEPTUNE_GRAVITY = 1.12f * CONST_EARTH_GRAVITY;/**!< Neptune gravity 1.12 */

const double PhysicsConfiguration::JUPITER_GRAVITY = 2.36f * CONST_EARTH_GRAVITY; /**!< Jupiter gravity 2.36 */

const double PhysicsConfiguration::SUN_GRAVITY = 27.030682877f * CONST_EARTH_GRAVITY; /**!< Sun gravity 27.930682977 */

/**
 * Step size of the bullet physics simulator (solverAccuracy). Accuracy versus speed.
 */
//#define FIXED_STEPS_PER_SEC 60.0f // Too low
//#define FIXED_STEPS_PER_SEC 120.0f // Might be too low
//#define FIXED_STEPS_PER_SEC 200.0f // Might be ok
#define FIXED_STEPS_PER_SEC 240.0f // Might be better
//#define FIXED_STEPS_PER_SEC 1000.0f // Best results
const double PhysicsConfiguration::SIMULATOR_PHYSICS_FIXED_STEPS_PER_SEC =
FIXED_STEPS_PER_SEC;
const double PhysicsConfiguration::FIXED_STEP_SIZE_SEC = 1.0f / FIXED_STEPS_PER_SEC;
const double PhysicsConfiguration::FIXED_STEP_SIZE_MILLI = 1.0f / FIXED_STEPS_PER_SEC
	* 1000.0f;

const double PhysicsConfiguration::BULLET_OGRE_BOX_SCALING_FACTOR = 0.01; /**!< A box of unit size in ogre has the size of 100 in bullet */

const double PhysicsConfiguration::BULLET_DEACTIVATION_TIME = 5; /**!< The deactivation time of a bullet object */
const double PhysicsConfiguration::BULLET_LINEAR_SLEEPING_TIME = 1.6; /**!< The time to sleep with linear movement */
const double PhysicsConfiguration::BULLET_ANGULAR_SLEEPING_TIME = 5; /**!< The time to sleep with angular movement */

const double PhysicsConfiguration::SIMULATION_SPEEDS[] = { /**!< The simulation speeds of the Bullet Physics simulation*/
-2,/**!<SIMULATION_SPEED_01*/-1,/**!<SIMULATION_SPEED_02*/
0,/**!<SIMULATION_SPEED_03*/1,/**!<SIMULATION_SPEED_04*/
2,/**!<SIMULATION_SPEED_05*/3,/**!<SIMULATION_SPEED_06*/
4, /**!<SIMULATION_SPEED_07*/5,/**!<SIMULATION_SPEED_08*/
0, /**!<SIMULATION_SPEED_09 run as fast as possible with graphics*/0 /**!<SIMULATION_SPEED_10 run as fast as possible headless*/
};

#define BIT(x) (1<<(x))
enum collisiontypes {
	COL_NOTHING = 0, //<Collide with nothing
	COL_CREATURE = BIT(0), //<Collide with ships
	COL_GROUND = BIT(1), //<Collide with walls
	COL_CREATURE_TESTRAY = BIT(2), //<Collide with creature test ray
	COL_GROUND_TESTRAY = BIT(3) //< Collide with ground test ray
};

const int PhysicsConfiguration::CREATURE_COLLIDES_WITH = COL_GROUND | COL_CREATURE_TESTRAY; /**!< Objects a creature collides with */
const int PhysicsConfiguration::GROUND_COLLIDES_WITH = COL_CREATURE | COL_GROUND_TESTRAY; /**!< Objects the ground collides with */
const int PhysicsConfiguration::CREATURE_TESTRAY_COLLIDES_WITH = COL_CREATURE; /**!< Objects a creature test ray collides with */
const int PhysicsConfiguration::GROUND_TESTRAY_COLLIDES_WITH = COL_GROUND; /**!< Objects a ground test ray collides with */

/** Attempts to detect interpenetrating shapes */
const double PhysicsConfiguration::PENETRATION_THRESHOLD = -40; //-15
const double PhysicsConfiguration::FORCE_THRESHOLD = 1e6;
const double PhysicsConfiguration::TORQUE_THRESHOLD = 1e6;
const double PhysicsConfiguration::DISCARDING_STARTS = 1.0f;

const double PhysicsConfiguration::BULLET_PICKER_FORCE = 100000;

const PhysicsConfiguration::SolverType PhysicsConfiguration::SOLVER_TYPE = PhysicsConfiguration::SEQUENTIALIMPULSESOLVER;

const double PhysicsConfiguration::UNIV_EPS = 0.01f;
