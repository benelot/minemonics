#ifndef CONFIGURATION_MORPHOLOGYCONFIGURATION_H_
#define CONFIGURATION_MORPHOLOGYCONFIGURATION_H_

//# corresponding headers
//# forward declarations
//# system headers
#include <math.h>

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
 * @brief		The configuration of the creature morphology.
 * It defines limits of size and weight that are usually given by nature.
 * @details		Details
 * @date		2015-02-26
 * @author		Benjamin Ellenberger
 */
class MorphologyConfiguration {
public:

	static const double LIMB_MIN_SIZE; /**!<The limb minimum dimension size*/

	static const double LIMB_MAX_SIZE; /**!<The limb maximum dimension size*/

	//TODO: Optimize with bullet physics engine
	//TODO: Not used yet in this simulator
	static const double LIMB_MIN_DENSITY; /**!<The limb minimum density*/

	//TODO: Optimize with bullet physics engine
	//TODO: Not used yet in this simulator
	static const double LIMB_MAX_DENSITY; /**!<The limb maximum density */

	static const double LIMB_INITIAL_RESTITUTION;/**!< The limb initial restitution/elasticity. */

	static const double LIMB_INITIAL_FRICTION; /**!< The limb initial friction */

	//TODO: Not used yet in this simulator
	static const double LIMB_MAX_VELOCITY; /**!<This limit is intended to help the system avoid the numerical explosions that can arise from time to time during creature evolution. This is done to discourage the evolution of undesirable creatures that exploit the weaknesses in the physics engine.*/

	static const double LIMB_SCALE_MIN; /**!< The limb scale min constant determines how much the subtree of this body segment should be scaled at least.*/

	static const double LIMB_SCALE_MAX; /**!< The limb scale max constant determines how much the subtree of this body segment should be scaled at most.*/

	static const double LIMB_INITIAL_TYPE_REPEATS; /**!< The initial maximum limb type repeats*/

	static const double LIMB_DEPTH_INITIAL_MEAN; /**!< Initial limbs depth mean*/

	static const double LIMB_DEPTH_INITIAL_VAR; /**!< Initial segments depth variance */

	static const double LIMB_TOTAL_INITIAL_MEAN; /**!< Initial total segments mean*/

	static const double LIMB_TOTAL_INITIAL_VAR; /**!< Initial total segments variance*/

	/**
	 * The density of fat in kg per cubic meter
	 *  https://en.wikipedia.org/wiki/Muscle#cite_ref-Urbancheka_2001_6-0
	 */
	//TODO: Not used yet in this simulator
	static const double FAT_DENSITY; // kg/m^3

	/**
	 * The density of muscle in kg per cubic meter
	 * https://en.wikipedia.org/wiki/Muscle#cite_ref-Urbancheka_2001_6-0
	 */
	//TODO: Not used yet in this simulator
	static const double MUSCLE_DENSITY; // kg/m^3

	/**
	 * For every 1 square centimeter of cross sectional area, muscle fibres can exert a maximum force of approximately 30–40 newtons (the weight of a 3–4 kg mass).
	 * http://sciencelearn.org.nz/Contexts/Sporting-Edge/Science-Ideas-and-Concepts/Muscle-performance
	 */
	//TODO: Not used yet in this simulator
	static const double MUSCLE_STRENGTH_PER_CSA; // N/m^2

	/**
	 * The maximum allowable torque that can be exerted by a servo motor in its effort to
	 * reach its desired angle is computed as [BODY_MUSCLE_MAX_TORQUE_LINEAR_CONSTANT*(mass1 +mass2)+BODY_MUSCLE_MAX_TORQUE_SQUARE_CONSTANT * (mass1 + mass2)^2]
	 */
	static const double MUSCLE_MAX_TORQUE_LINEAR_CONSTANT;

	/**
	 * The maximum allowable torque that can be exerted by a servo motor in its effort to
	 * reach its desired angle is computed as [BODY_MUSCLE_MAX_TORQUE_LINEAR_CONSTANT*(mass1 +mass2)+BODY_MUSCLE_MAX_TORQUE_SQUARE_CONSTANT * (mass1 + mass2)^2]
	 */
	static const double MUSCLE_MAX_TORQUE_SQUARE_CONSTANT;

	/**
	 * The joints between body segments are set to break if they experience torques beyond
	 * a given threshold. The breaking threshold value for a given joint is computed as
	 * BODY_JOINT_MAX_TORQUE_CONSTANT*(mass1+ mass2) (2.0x10^6 in 3DVCE) where mass1 and mass2
	 * are the masses of the two limbs connected by the joint. This formula allows joints between
	 *  larger segments to sustain correspondingly larger torques.
	 */
	//TODO: Not used yet in this simulator
	static const double JOINT_MAX_TORQUE_CONSTANT;

	static const double LINK_LENGTH; /**!< The length of an object between the parent joint and the child joint, 1 meaning its correct length. This is basically how much the creature is rayman. */

	static const double JOINT_MIN_SPRING_STIFFNESS; /**!< The minimum spring stiffness of the joint */

	static const double JOINT_MAX_SPRING_STIFFNESS; /**!< The maximum spring stiffness of the joint */

	static const double JOINT_MIN_DAMPING_COEFFICIENT; /**!< The minimum damping coefficient of the joint */

	static const double JOINT_MAX_DAMPING_COEFFICIENT; /**!< The maximum damping coefficient of the joint */

	static const bool BODY_INTRACOLLISION; /**!< Are the body segments allowed to interpenetrate each other? False means never, True means it can decide by itself*/

	static const bool BODY_MOTORS_ENABLED; /**!< Globally turn motors on or off*/
};

#endif /* CONFIGURATION_MORPHOLOGYCONFIGURATION_H_ */
