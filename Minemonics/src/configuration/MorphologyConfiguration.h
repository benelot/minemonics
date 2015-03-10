/*
 * MorphologyConfiguration.h
 *
 *  Created on: Feb 26, 2015
 *      Author: leviathan
 */

#ifndef MORPHOLOGYCONFIGURATION_H_
#define MORPHOLOGYCONFIGURATION_H_

class MorphologyConfiguration {
public:
	static const double BODY_CUBOID_MIN_SIZE = 0.4;
	static const double BODY_CUBOID_MAX_SIZE = 10;
	static const double BODY_CUBOID_MIN_DENSITY = 0.01;
	static const double BODY_CUBOID_MAX_DENSITY = 1;

	// https://en.wikipedia.org/wiki/Muscle#cite_ref-Urbancheka_2001_6-0
	static const double BODY_MUSCLE_DENSITY = 1060; // kg/m^3
	static const double BODY_FAT_DENSITY = 900; // kg/m^3

	//For every 1 square centimeter of cross sectional area, muscle fibres can exert a maximum force of approximately 30–40 newtons (the weight of a 3–4 kg mass).
	//http://sciencelearn.org.nz/Contexts/Sporting-Edge/Science-Ideas-and-Concepts/Muscle-performance
	static const double BODY_MUSCLE_STRENGTH_PER_CSA = 400000; // N/m^2

	/**
	 * This limit is intended to help the system avoid the numerical explosions that can arise from time to time during creature evolution. This is done to discourage the evolution of undesirable creatures that exploit the weaknesses in the physics engine.
	 */
	static const double BODY_SEGMENT_MAX_VELOCITY = 80000;

	/**
	 * The body segment scale min constant
	 */
	static const double BODY_SEGMENT_SCALE_MIN = -1.5;

	/**
	 * The body segment scale max constant
	 */

	static const double BODY_SEGMENT_SCALE_MAX = 1.5;

	/**
	 * The joints between body segments are set to break if they experience torques beyond
	 * a given threshold. The breaking threshold value for a given joint is computed as
	 * BODY_JOINT_MAX_TORQUE_CONSTANT*(m_1+ m_2) (2.0x10^6 in 3DVCE) where m_1 and m_2 are the masses of the two segments connected by the joint. This
	 * formula allows joints between larger segments to sustain correspondingly larger
	 * torques.
	 */
	static const double BODY_JOINT_MAX_TORQUE_CONSTANT = 1;

	/**
	 * The maximum allowable torque that can be exerted by a servo motor in its effort to
	 * reach its desired angle is computed as [BODY_MUSCLE_MAX_TORQUE_LINEAR_CONSTANT*(m_1 +m_2)+BODY_MUSCLE_MAX_TORQUE_SQUARE_CONSTANT * (m_1 + m_2)^2](1 + t)
	 */
	static const double BODY_MUSCLE_MAX_TORQUE_LINEAR_CONSTANT = 1;

	/**
	 * The maximum allowable torque that can be exerted by a servo motor in its effort to
	 * reach its desired angle is computed as [BODY_MUSCLE_MAX_TORQUE_LINEAR_CONSTANT*(m_1 +m_2)+BODY_MUSCLE_MAX_TORQUE_SQUARE_CONSTANT * (m_1 + m_2)^2](1 + t)
	 */
	static const double BODY_MUSCLE_MAX_TORQUE_SQUARE_CONSTANT = 1;

	/**
	 * The initial max segment type repeats
	 */
	static const double BODY_SEGMENT_INITIAL_TYPE_REPEATS = 12;

	/**
	 * The initial max branch number
	 */
	static const double BODY_BRANCH_INITIAL_MAX = 5;
};

#endif /* MORPHOLOGYCONFIGURATION_H_ */
