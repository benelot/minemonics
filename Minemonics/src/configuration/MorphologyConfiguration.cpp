//# corresponding headers
#include <configuration/MorphologyConfiguration.hpp>

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

const double MorphologyConfiguration::LIMB_MIN_SIZE = 0.05f; /**!< (in meters) The limb minimum dimension size*/

const double MorphologyConfiguration::LIMB_MAX_SIZE = 1.0f; /**!< (in meters) The limb maximum dimension size*/

const double MorphologyConfiguration::LIMB_MIN_DENSITY = 1.0f
	/ pow(MorphologyConfiguration::LIMB_MIN_SIZE, 3); /**!<The limb minimum density is defined as the smallest dimension cubed to be unit weight */

//TODO: Optimize with bullet physics engine
//TODO: Not used yet in this simulator
const double MorphologyConfiguration::LIMB_MAX_DENSITY = 1; /**!<The limb maximum density */

const double MorphologyConfiguration::LIMB_INITIAL_RESTITUTION = 0.2;/**!< The limb initial restitution/elasticity. */

const double MorphologyConfiguration::LIMB_INITIAL_FRICTION = 10; /**!< The limb initial friction */

const double MorphologyConfiguration::JOINT_MAX_VELOCITY = 80; /**!<This limit is intended to help the system avoid the numerical explosions that can arise from time to time during creature evolution. This is done to discourage the evolution of undesirable creatures that exploit the weaknesses in the physics engine.*/

const double MorphologyConfiguration::LIMB_SCALE_MIN = -0.66; /**!< The limb scale min constant determines how much the subtree of this body segment should be scaled at least.*/

const double MorphologyConfiguration::LIMB_SCALE_MAX = 2.0; /**!< The limb scale max constant determines how much the subtree of this body segment should be scaled at most.*/

const double MorphologyConfiguration::LIMB_INITIAL_TYPE_REPEATS = 3; /**!< The initial maximum limb type repeats*/

const double MorphologyConfiguration::LIMB_DEPTH_INITIAL_MEAN = 3; /**!< Initial limbs depth mean*/

const double MorphologyConfiguration::LIMB_DEPTH_INITIAL_VAR = 2; /**!< Initial segments depth variance */

const double MorphologyConfiguration::LIMB_TOTAL_INITIAL_MEAN = 10; /**!< Initial total segments mean*/

const double MorphologyConfiguration::LIMB_TOTAL_INITIAL_VAR = 5; /**!< Initial total segments variance*/

/**
 * The density of fat in kg per cubic meter
 *  https://en.wikipedia.org/wiki/Muscle#cite_ref-Urbancheka_2001_6-0
 */
//TODO: Not used yet in this simulator
const double MorphologyConfiguration::FAT_DENSITY = 900; // kg/m^3

/**
 * The density of muscle in kg per cubic meter
 * https://en.wikipedia.org/wiki/Muscle#cite_ref-Urbancheka_2001_6-0
 */
//TODO: Not used yet in this simulator
const double MorphologyConfiguration::MUSCLE_DENSITY = 1060; // kg/m^3

/**
 * For every 1 square centimeter of cross sectional area, muscle fibres can exert a maximum force of approximately 30–40 newtons (the weight of a 3–4 kg mass).
 * http://sciencelearn.org.nz/Contexts/Sporting-Edge/Science-Ideas-and-Concepts/Muscle-performance
 */
//TODO: Not used yet in this simulator
const double MorphologyConfiguration::MUSCLE_STRENGTH_PER_CSA = 400000; // N/m^2

/**
 * The maximum allowable torque that can be exerted by a motor is computed as
 * [MOTOR_MAX_TORQUE_LINEAR_CONSTANT * (mass1 * mass2) + MOTOR_MAX_TORQUE_SQUARE_CONSTANT * (mass1 * mass2)^2]
 */
const double MorphologyConfiguration::MOTOR_FS_MAX_TORQUE_LINEAR_CONSTANT =
	0.02f;

const double MorphologyConfiguration::MOTOR_SRB_MAX_TORQUE_LINEAR_CONSTANT =
	0.05f;

/**
 * The maximum allowable torque that can be exerted by a motor is computed as
 * [MOTOR_MAX_TORQUE_LINEAR_CONSTANT * (mass1 * mass2) + MOTOR_MAX_TORQUE_SQUARE_CONSTANT * (mass1 * mass2)^2]
 */
const double MorphologyConfiguration::MOTOR_FS_MAX_TORQUE_SQUARE_CONSTANT = 0.0000000003f;

const double MorphologyConfiguration::MOTOR_SRB_MAX_TORQUE_SQUARE_CONSTANT = 0;

/**
 * The joints between body segments are set to break if they experience torques beyond
 * a given threshold. The breaking threshold value for a given joint is computed as
 * BODY_JOINT_MAX_TORQUE_CONSTANT*(mass1+ mass2) (2.0x10^6 in 3DVCE) where mass1 and mass2
 * are the masses of the two limbs connected by the joint. This formula allows joints between
 *  larger segments to sustain correspondingly larger torques.
 */
//TODO: Not used yet in this simulator
const double MorphologyConfiguration::JOINT_MAX_TORQUE_CONSTANT = 1;

const double MorphologyConfiguration::LINK_LENGTH = 1; /**!< The length of an object between the parent joint and the child joint, 1 meaning its correct length. This is basically how much the creature is rayman. */

const double MorphologyConfiguration::JOINT_MIN_SPRING_STIFFNESS = 0; /**!< The minimum spring stiffness of the joint */

const double MorphologyConfiguration::JOINT_MAX_SPRING_STIFFNESS = 0; /**!< The maximum spring stiffness of the joint */

const double MorphologyConfiguration::JOINT_MIN_DAMPING_COEFFICIENT = 0.001f; //0.05f;//0.005f; /**!< The minimum damping coefficient of the joint */

const double MorphologyConfiguration::JOINT_MAX_DAMPING_COEFFICIENT = 1.0f; //5.0f; //0.5f; /**!< The maximum damping coefficient of the joint */

const bool MorphologyConfiguration::BODY_INTRACOLLISION_EVOLUTION = false; /**!< Is evolution allowed to change the intracollision for a limb? False means no, true means yes. */

const bool MorphologyConfiguration::BODY_INTRACOLLISION = false; /**!< Are the body segments allowed to collide with each other?*/

const bool MorphologyConfiguration::BODY_CONNECTED_LIMB_COLLISION = false; /**!< Are the limbs directly connected allowed to collide with each other? */

const bool MorphologyConfiguration::BODY_MOTORS_ENABLED = true; /**!< Globally turn motors on or off*/

